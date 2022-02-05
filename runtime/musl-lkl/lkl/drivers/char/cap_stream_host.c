#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/poll.h>
#include <linux/semaphore.h>

#define MY_MAJOR       45
#define MY_MAX_MINORS  1024


#define CAP_TYPE 0xE4
#define CAP_SETSIZE _IOW(CAP_TYPE, 0x01, int)
#define CAP_ADV _IOW(CAP_TYPE, 0x02, int)
#define CAP_PRB _IOW(CAP_TYPE, 0x03, int)
#define CAP_REG_BUF _IOW(CAP_TYPE, 0x05, int)
#define CAP_WAIT _IOW(CAP_TYPE, 0x06, int)

#define MODE_FILE	0
#define MODE_STREAM	1
#define MODE_MAX	MODE_STREAM

#define PLOCK	1

extern copy_from_cap(void *dst, void *src_cap_location, int len);
extern copy_to_cap(void *src_cap_location, void *src, int len);


extern int read_cap(void *dst, int unused, int len);
extern int write_cap(void *src, int unused, int len);

extern int wrap_host_cap_stream_adv(void *func, void *device, char *key);
extern int wrap_host_cap_stream_prb(char *key);

extern int wrap_host_make_cap_call(int id, void *buf, int len);

extern int wrap_host_finish_cap_call(int id, void *buff);
extern int wrap_host_fetch_cap_call(int id, void *cap, void *size);



extern int wrap_host_cap_wait(int id);
extern int wrap_host_cap_wake(int id);

struct my_device_data {
	struct cdev cdev;
    /* my data starts here */
	int size;
 	char key[10];
	char cap[32];
	int id;
//
	void *stream_buf;
	int stream_buf_size;

	wait_queue_head_t wait_queue_etx_data;
	bool poll_can_read;

	spinlock_t event_lock;
};


static int my_open(struct inode *inode, struct file *file)
{
//	lkl_printf("CF_STREAM HOST is open \n");

    struct my_device_data *my_data =
             container_of(inode->i_cdev, struct my_device_data, cdev);

    /* validate access to device */
    file->private_data = my_data;
    init_waitqueue_head(&my_data->wait_queue_etx_data);
    spin_lock_init(&my_data->event_lock);
    
//	lkl_printf("&my_data->stream_buf = %p, \n", &my_data->stream_buf);
	my_data->poll_can_read = false;

    return 0;
}

struct p_args {
	void *file;
	void *src;
	int size;
	struct my_device_data *md;
};


//	while(tmp == true) {
//		spin_lock_irqsave(&event_lock, flags);
//		tmp = poll_can_read;
//		spin_unlock_irqrestore(&event_lock, flags);
//	}

// if -48 changes, new value should be adjusted in o_call inside monitor
//; static ssize_t portal_write(void *arg) {
//  3220a4: 79 71        	addi	sp, sp, -48
//

static ssize_t portal_write(int id) {
//  lkl_printf(" portal w rite, %p, arg\n", id);

	volatile struct my_device_data *my_data;

	wrap_host_finish_cap_call(id, (void *) &my_data);

	wrap_host_fetch_cap_call(id, (void *) ALIGN((unsigned long) my_data->cap, 16), (void *) &my_data->size);

//	lkl_printf("two calls done, size = %d, stream = %p\n", my_data->size, my_data->stream_buf);

	while(my_data->stream_buf == NULL); //it is better to return and enter again

	copy_from_cap(my_data->stream_buf, (void *) ALIGN((unsigned long) my_data->cap, 16), my_data->size);

	my_data->stream_buf_size = my_data->size;
	my_data->stream_buf = 0;

//	lkl_printf("id = %d, md->id = %d\n", id, my_data->id);
	wrap_host_cap_wake(my_data->id);

#if 0
//one call -- destroy the thread
	extern void wrap_thread_exit(void);
	wrap_thread_exit();
#else
	extern void wrap_ocall_exit(long ret);
	wrap_ocall_exit(my_data->size);
#endif
//never
	return my_data->size;
}



static ssize_t my_read(struct file *file, char __user *user_buffer,
                   size_t size, loff_t *offset)
{
	lkl_printf("read nothing\n");
    return 0;
}

static ssize_t my_write(struct file *file, const char __user *user_buffer,
                    size_t size, loff_t * offset)
{
	struct my_device_data *my_data = (struct my_device_data *) file->private_data;

//	lkl_printf("my_write, buf = %p, size = %d\n", user_buffer, size);
	wrap_host_make_cap_call(my_data->id, (void *) user_buffer, size);

	return size;
}

static struct f_ptrs {
	void *ptr;
} ptrs[2];

static int fpc = 0;

static long my_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;
			void (*tcall) (void);
	unsigned long flags;
	unsigned long *target;
	struct my_device_data *tmp_data;

    struct my_device_data *my_data = (struct my_device_data *) file->private_data;
	switch ( cmd ) {
		case CAP_SETSIZE:
			my_data->size = (int) arg;
			return 0;
		case CAP_REG_BUF:

			my_data->stream_buf = (long) arg;
//			lkl_printf("my_data->stream_buf = %p", my_data->stream_buf);
			my_data->stream_buf_size = my_data->size;

			return 0;
		case CAP_ADV:
			memcpy(my_data->key, (void *) arg, 10);
			my_data->id = wrap_host_cap_stream_adv(&portal_write, my_data, my_data->key);
//			lkl_printf("cap_adv id = %d\n", my_data->id);
			return 0;
////////////
		case CAP_PRB:
			memcpy(my_data->key, (void *) arg, 10);

			my_data->id = wrap_host_cap_stream_prb(my_data->key);
//			lkl_printf("cap_prb id = %d\n", my_data->id);
			return 0;
		case CAP_WAIT:
			wrap_host_cap_wait(my_data->id);
			return 0;//my_data->stream_buf_size;

		default:
	        return -ENOTTY;
	}
}

static loff_t my_llseek(struct file *file, loff_t offset, int orig)
{
	loff_t ret;
    struct my_device_data *my_data = (struct my_device_data *) file->private_data;

	ret = no_seek_end_llseek_size(file, offset, orig, my_data->size);
	return ret;
}

static unsigned int my_poll(struct file *filp, struct poll_table_struct *wait)
{
	__poll_t mask = 0;
	unsigned long flags;
    struct my_device_data *my_data = (struct my_device_data *) filp->private_data;

#ifdef PLOCK
	spin_lock_irqsave(&my_data->event_lock, flags);
#endif

	poll_wait(filp, &my_data->wait_queue_etx_data, wait);

	if( my_data->poll_can_read ) {
		my_data->poll_can_read = false;
		mask |= ( POLLIN | POLLRDNORM );
	}
#ifdef PLOCK
	spin_unlock_irqrestore(&my_data->event_lock, flags);
#endif

	return mask;
}


static struct my_device_data devs[MY_MAX_MINORS];

static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
//    .release = my_release,
    .unlocked_ioctl = my_ioctl,
	.llseek		= my_llseek,
	.poll		= my_poll,
};

static int my_init_module_stream_host(void)
{
    int i, err;

    lkl_printf("CAP_STREAM_HOST INIT %d %x\n", MY_MAJOR, CAP_SETSIZE);

    err = register_chrdev_region(MKDEV(MY_MAJOR, 0), MY_MAX_MINORS,
                                 "my_device_driver_new");
    if (err != 0) {
        /* report error */
	lkl_printf("register chrdev returned %d\n", err);
        return err;
    }

    for(i = 0; i < MY_MAX_MINORS; i++) {
        /* initialize devs[i] fields */
        cdev_init(&devs[i].cdev, &my_fops);
        cdev_add(&devs[i].cdev, MKDEV(MY_MAJOR, i), 1);
    }

    return 0;
}

static void my_cleanup_module_stream_host(void)
{
    int i;

    for(i = 0; i < MY_MAX_MINORS; i++) {
        /* release devs[i] fields */
        cdev_del(&devs[i].cdev);
    }
    unregister_chrdev_region(MKDEV(MY_MAJOR, 0), MY_MAX_MINORS);
}




module_init(my_init_module_stream_host);
module_exit(my_cleanup_module_stream_host);
