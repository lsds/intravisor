/* SWIOTLB implementation for LKL.  */

#include <asm/dma.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/swiotlb.h>
#include <linux/dma-direct.h>

/* Host provides a memory pool for virt queue handling. This memory will
 be used as a bounce buffer to share the data between host & guest.
    +--------------------------------+
    |                                |
    |       Bounce Buffer            |
    |                                |
    +--------------------------------+
    | Queue 1 VirtIO desc buffer     |
    +--------------------------------+
    | Queue 2 VirtIO desc buffer     |
    +--------------------------------+
    | Queue 3 VirtIO desc buffer     |
    +--------------------------------+
    |                                |
    +--------------------------------+
    |                                |
    +--------------------------------+
    | Queue n VirtIO desc buffer     |
    +--------------------------------+
 */

#define SWIOTLB_BOUNCE_BUFFER_SIZE (64UL << 20)

const struct dma_map_ops *dma_ops = NULL;

static char *_lkl_io_tlb_start, *_lkl_io_tlb_end;
static unsigned long _lkl_io_tlb_nslabs;

/* Variable to hold the user memory & its usage for bounce buffer */
static void *_user_mem = NULL;
static size_t _user_mem_size = 0;
static size_t _user_mem_used = 0;
static int _lkl_swiotlb_initialized = 0;

static u64 _start_dma_addr;

static int _lkl_initialize_swiotlb(size_t size);

/* Function to serve the memory request from LKL SWIOTLB module */
static void *lkl_swiotlb_mem_allocator(size_t size)
{
	void *ptr = NULL;
	if (size <= (_user_mem_size - _user_mem_used)) {
		ptr = _user_mem + _user_mem_used;
		_user_mem_used += size;
	}
	BUG_ON(!ptr);

	return ptr;
}

/* Function to allocate the chunck of memory from the user supplied memory, LKL
 * SWIOTBL module manages user memory and returns allocate memory as requested*/
static void *lkl_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		       gfp_t gfp, unsigned long attrs)
{
	size_t alloc_size = PAGE_ALIGN(size);
	void *lkl_alloc_p = lkl_swiotlb_mem_allocator(alloc_size);

	memset(lkl_alloc_p, 0, alloc_size);
	*dma_handle = (dma_addr_t)lkl_alloc_p;

	return lkl_alloc_p;
}

/* Function to free the memory. This function does not perform
 * any operation and user memory pool is deallocated by host */
static void lkl_free(struct device *dev, size_t size, void *vaddr,
		     dma_addr_t dma_addr, unsigned long attrs)
{
	/* Memory should be freed by host */
	return;
}

/* Function to map the single page of indicated size bounce buffer operations.
 * Once the device is given a dma address, the device owns the memory until 
 * lkl_unmap_page is called */
static dma_addr_t lkl_map_page(struct device *dev, struct page *page,
			       unsigned long offset, size_t size,
			       enum dma_data_direction dir, unsigned long attrs)
{
	dma_addr_t dev_addr;
	phys_addr_t map, phys = page_to_phys(page) + offset;

	if (!_lkl_swiotlb_initialized) {
		_lkl_initialize_swiotlb(SWIOTLB_BOUNCE_BUFFER_SIZE);
		_lkl_swiotlb_initialized = !_lkl_swiotlb_initialized;
	}

	_start_dma_addr = __phys_to_dma(dev, (phys_addr_t)_lkl_io_tlb_start);
	map = swiotlb_tbl_map_single(dev, _start_dma_addr, phys, size, size,
				     dir, attrs);
	if (map == (phys_addr_t)DMA_MAPPING_ERROR) {
		printk("LKL SWIOTLB: swiotlb_tbl_map_single map error\n");
		return map;
	}
	dev_addr = __phys_to_dma(dev, map);

	return dev_addr;
}

/* Function to unmap the pages allocated using lkl_map_page */
static void lkl_unmap_single(struct device *dev, dma_addr_t dev_addr,
			     size_t size, enum dma_data_direction dir,
			     unsigned long attrs)
{
	phys_addr_t phys = __dma_to_phys(dev, dev_addr);

	if (is_swiotlb_buffer(phys))
		swiotlb_tbl_unmap_single(dev, phys, size, size, dir, attrs);

	return;
}

/* Function to unmap the pages allocated using lkl_map_page */
static void lkl_unmap_page(struct device *dev, dma_addr_t dev_addr, size_t size,
			   enum dma_data_direction dir, unsigned long attrs)
{
	lkl_unmap_single(dev, dev_addr, size, dir, attrs);

	return;
}

/* LKL dma operation to support bounce buffer */
static const struct dma_map_ops lkl_dma_ops = {
	.alloc = lkl_alloc,
	.free = lkl_free,
	.sync_single_for_cpu = NULL,
	.sync_single_for_device = NULL,
	.sync_sg_for_cpu = NULL,
	.sync_sg_for_device = NULL,
	.map_sg = NULL,
	.unmap_sg = NULL,
	.map_page = lkl_map_page,
	.unmap_page = lkl_unmap_page,
	.dma_supported = dma_direct_supported,
	.max_mapping_size = swiotlb_max_mapping_size,
};

/* Function to initialize the bounce buffer in LKL */
static int _lkl_initialize_swiotlb(size_t size)
{
	int ret;
	size_t bytes;

	_lkl_io_tlb_nslabs = (size >> IO_TLB_SHIFT);
	_lkl_io_tlb_nslabs = ALIGN(_lkl_io_tlb_nslabs, IO_TLB_SEGSIZE);
	bytes = _lkl_io_tlb_nslabs << IO_TLB_SHIFT;

	if ((size < bytes)) {
		printk("LKL SWIOTLB: Failed to allocate memory\n");
		return -ENOMEM;
	}

	_lkl_io_tlb_start = lkl_swiotlb_mem_allocator(bytes);
	_lkl_io_tlb_end = _lkl_io_tlb_start + bytes;

	ret = swiotlb_late_init_with_tbl(_lkl_io_tlb_start, _lkl_io_tlb_nslabs);

	return ret;
}

/* Function called by external component to pass statically allocated user 
 * memory for bounce buffer and configures it to be used as bounce buffer */
int lkl_initialize_swiotlb(void *ptr, unsigned long size)
{
	_user_mem = ptr;
	_user_mem_size = size;
	dma_ops = &lkl_dma_ops;

	return 0;
}
