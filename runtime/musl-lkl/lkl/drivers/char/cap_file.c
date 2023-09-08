#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/poll.h>

#define CAP_FILE_MAJOR       43
#define CAP_FILE_MAX_MINORS  1024


#define CAP_TYPE 0xE2
#define CAP_SETCAP _IOW(CAP_TYPE, 0x00, int)
#define CAP_SETSIZE _IOW(CAP_TYPE, 0x01, int)
#define CAP_ADV _IOW(CAP_TYPE, 0x02, int)
#define CAP_PRB _IOW(CAP_TYPE, 0x03, int)
#define CAP_SETMODE _IOW(CAP_TYPE, 0x04, int)
#define CAP_REG_BUF _IOW(CAP_TYPE, 0x05, int)

#define MODE_FILE	0
#define MODE_STREAM	1
#define MODE_MAX	MODE_STREAM

extern copy_from_cap(void *dst, void *src_cap_location, int len);
extern copy_to_cap(void *src_cap_location, void *src, int len);

extern int wrap_host_cap_adv(void *ptr, long size, char *key);
extern int wrap_host_cap_prb(char *key, void *location, void *size);

struct cap_file_device_data {
	struct cdev cdev;
//
	int size;
 	char key[10];
	void *ptr;
	char cap[16];
};

static int cap_file_open(struct inode *inode, struct file *file)
{
	lkl_printf("device is open: CAPFILE\n");
	struct cap_file_device_data *cap_file_data = container_of(inode->i_cdev, struct cap_file_device_data, cdev);

	/* validate access to device */
	file->private_data = cap_file_data;

	return 0;
}

static ssize_t cap_file_read(struct file *file, char __user *user_buffer, size_t size, loff_t *offset) {
	volatile struct cap_file_device_data *cap_file_data = (struct cap_file_device_data *) file->private_data;
	ssize_t len = min(cap_file_data->size - *offset, size);

	if (len <= 0)
		return 0;

//if you see bad numbers, you should use aligned buffers

	copy_from_cap(user_buffer, (void *) cap_file_data->cap, len);

	*offset += len;

	return len;
}

static ssize_t cap_file_write(struct file *file, const char __user *user_buffer, size_t size, loff_t * offset) {
	struct cap_file_device_data *cap_file_data = (struct cap_file_device_data *) file->private_data;
	ssize_t len = min(cap_file_data->size - *offset, size);

	if (len <= 0)
		return 0;

	copy_to_cap((void *) cap_file_data->cap, (void *) user_buffer, len);
//	write_cap((void *)user_buffer, 0, len);

	*offset += len;

	return len;
}

static long cap_file_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;

	struct cap_file_device_data *cap_file_data = (struct cap_file_device_data *) file->private_data;
	switch ( cmd ) {
		case CAP_SETCAP:
			cap_file_data->ptr = (void *)arg;
			return 0;
		case CAP_SETSIZE:
			cap_file_data->size = (int) arg;
			return 0;
		case CAP_ADV:
			memcpy(cap_file_data->key, (void *) arg, 10);
			wrap_host_cap_adv(cap_file_data->ptr, cap_file_data->size, cap_file_data->key);
  			return 0;
		case CAP_PRB:
			memcpy(cap_file_data->key, (void *) arg, 10);
			wrap_host_cap_prb(cap_file_data->key, (void *) cap_file_data->cap, &cap_file_data->size);
			return 0;
		default:
	        return -ENOTTY;
	}
}

static loff_t cap_file_llseek(struct file *file, loff_t offset, int orig)
{
	loff_t ret;
	struct cap_file_device_data *cap_file_data = (struct cap_file_device_data *) file->private_data;

	ret = no_seek_end_llseek_size(file, offset, orig, cap_file_data->size);
	return ret;
}

static struct cap_file_device_data devs[CAP_FILE_MAX_MINORS];

static const struct file_operations cap_file_fops = {
    .owner = THIS_MODULE,
    .open = cap_file_open,
    .read = cap_file_read,
    .write = cap_file_write,
    .unlocked_ioctl = cap_file_ioctl,
	.llseek		= cap_file_llseek,
};

static int cap_file_init_module(void)
{
    int i, err;

    lkl_printf("CAP_FILE INIT %d %x\n", CAP_FILE_MAJOR, CAP_SETSIZE);

    err = register_chrdev_region(MKDEV(CAP_FILE_MAJOR, 0), CAP_FILE_MAX_MINORS,
                                 "cap_file");
    if (err != 0) {
        /* report error */
	lkl_printf("register chrdev returned %d\n", err);
        return err;
    }

    for(i = 0; i < CAP_FILE_MAX_MINORS; i++) {
        /* initialize devs[i] fields */
        cdev_init(&devs[i].cdev, &cap_file_fops);
        cdev_add(&devs[i].cdev, MKDEV(CAP_FILE_MAJOR, i), 1);
    }

    return 0;
}

static void cap_file_cleanup_module(void)
{
    int i;

    for(i = 0; i < CAP_FILE_MAX_MINORS; i++) {
        /* release devs[i] fields */
        cdev_del(&devs[i].cdev);
    }
    unregister_chrdev_region(MKDEV(CAP_FILE_MAJOR, 0), CAP_FILE_MAX_MINORS);
}




module_init(cap_file_init_module);
module_exit(cap_file_cleanup_module);
