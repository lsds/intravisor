#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/poll.h>

#define CAP_GADGET_MAJOR       50
#define CAP_GADGET_MAX_MINORS  1024


#define CAP_TYPE 0xE2
#define CAP_SETCAP _IOW(CAP_TYPE, 0x00, int)
#define CAP_SETSIZE _IOW(CAP_TYPE, 0x01, int)
#define CAP_ADV _IOW(CAP_TYPE, 0x02, int)
#define CAP_PRB _IOW(CAP_TYPE, 0x03, int)
#define CAP_SETMODE _IOW(CAP_TYPE, 0x04, int)
#define CAP_REG_BUF _IOW(CAP_TYPE, 0x05, int)

#define MODE_GADGET	0
#define MODE_STREAM	1
#define MODE_MAX	MODE_STREAM

extern copy_from_cap(void *dst, void *src_cap_location, int len);
extern copy_to_cap(void *src_cap_location, void *src, int len);

extern int wrap_host_cap_adv(void *ptr, long size, char *key);
extern int wrap_host_cap_prb(char *key, void *location, void *size);

struct cap_gadget_device_data {
	struct cdev cdev;
//
	int size;
 	char key[10];
	void *ptr;
	char cap[16];
};

static int cap_gadget_open(struct inode *inode, struct file *file)
{
	lkl_printf("device is open: CAPGADGET\n");
	struct cap_gadget_device_data *cap_gadget_data = container_of(inode->i_cdev, struct cap_gadget_device_data, cdev);

	/* validate access to device */
	file->private_data = cap_gadget_data;

	return 0;
}

static ssize_t cap_gadget_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset) {
	volatile struct cap_gadget_device_data *cap_gadget_data = (struct cap_gadget_device_data *) file->private_data;
	ssize_t len = min(cap_gadget_data->size - *offset, size);

	if (len <= 0)
		return 0;

//if you see bad numbers, you should use aligned buffers

	copy_from_cap(user_buffer, (void *) cap_gadget_data->cap, len);

	*offset += len;

	return len;
}

static ssize_t cap_gadget_write(struct file *file, const char __user *user_buffer, size_t size, loff_t * offset) {
	struct cap_gadget_device_data *cap_gadget_data = (struct cap_gadget_device_data *) file->private_data;
	ssize_t len = min(cap_gadget_data->size - *offset, size);

	if (len <= 0)
		return 0;

	copy_to_cap((void *) cap_gadget_data->cap, (void *) user_buffer, len);
//	write_cap((void *)user_buffer, 0, len);

	*offset += len;

	return len;
}

static long cap_gadget_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;

	struct tmp_struct {
		void *a;
		void *b;
	};

	struct tmp_struct *tt = (struct tmp_struct *) arg;

	struct cap_gadget_device_data *cap_gadget_data = (struct cap_gadget_device_data *) file->private_data;
	switch ( cmd ) {
		case CAP_SETCAP:
			cap_gadget_data->ptr = (void *)arg;
			return 0;
		case CAP_SETSIZE:
			cap_gadget_data->size = (int) arg;
			return 0;
		case CAP_ADV:
			memcpy(cap_gadget_data->key, (void *) arg, 10);
			wrap_host_cap_adv(cap_gadget_data->ptr, cap_gadget_data->size, cap_gadget_data->key);
  			return 0;
		case CAP_PRB:
			lkl_printf("%s, args: %p %p die\n", __func__, tt->a, tt->b); while(1);
//			memcpy(cap_gadget_data->key, (void *) arg, 10);
//			wrap_host_cap_prb(cap_gadget_data->key, (void *) cap_gadget_data->cap, &cap_gadget_data->size);
			return 0;
		default:
	        return -ENOTTY;
	}
}

static loff_t cap_gadget_llseek(struct file *file, loff_t offset, int orig)
{
	loff_t ret;
	struct cap_gadget_device_data *cap_gadget_data = (struct cap_gadget_device_data *) file->private_data;

	ret = no_seek_end_llseek_size(file, offset, orig, cap_gadget_data->size);
	return ret;
}

static struct cap_gadget_device_data devs[CAP_GADGET_MAX_MINORS];

static const struct file_operations cap_gadget_fops = {
    .owner = THIS_MODULE,
    .open = cap_gadget_open,
    .read = cap_gadget_read,
    .write = cap_gadget_write,
    .unlocked_ioctl = cap_gadget_ioctl,
	.llseek		= cap_gadget_llseek,
};

static int cap_gadget_init_module(void)
{
    int i, err;

    lkl_printf("CAP_GADGET INIT %d %x\n", CAP_GADGET_MAJOR, CAP_SETSIZE);

    err = register_chrdev_region(MKDEV(CAP_GADGET_MAJOR, 0), CAP_GADGET_MAX_MINORS,
                                 "cap_gadget");
    if (err != 0) {
        /* report error */
	lkl_printf("register chrdev returned %d\n", err);
        return err;
    }

    for(i = 0; i < CAP_GADGET_MAX_MINORS; i++) {
        /* initialize devs[i] fields */
        cdev_init(&devs[i].cdev, &cap_gadget_fops);
        cdev_add(&devs[i].cdev, MKDEV(CAP_GADGET_MAJOR, i), 1);
    }

    return 0;
}

static void cap_gadget_cleanup_module(void)
{
    int i;

    for(i = 0; i < CAP_GADGET_MAX_MINORS; i++) {
        /* release devs[i] fields */
        cdev_del(&devs[i].cdev);
    }
    unregister_chrdev_region(MKDEV(CAP_GADGET_MAJOR, 0), CAP_GADGET_MAX_MINORS);
}




module_init(cap_gadget_init_module);
module_exit(cap_gadget_cleanup_module);
