#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/completion.h>
#include<linux/delay.h>
#define NAME compdevice


//function prototypes
int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t synch_completion_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t synch_completion_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);

//structure defining operations that the driver provides
struct file_operations fops = 
{
	.owner	= THIS_MODULE,
	.open	= NAME_open,
	.release= NAME_release,
	.read = synch_completion_read,
	.write=synch_completion_write

};


struct cdev *my_cdev;
struct completion synch_completion;

int result;
int major,minor; 
dev_t mydev;

char kbuff[100];

static int __init synch_completion_init(void)
{

	mydev=MKDEV(255,0); 
        major=MAJOR(mydev);
        minor=MINOR(mydev);
        printk("\n major number %d.....minor number %d\n",major,minor);

	result=register_chrdev_region(mydev,1,"compdevice");
        if(result<0)
        {
                printk("\nthe region is not obtainable\n");
                return(-1);

        }

	
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	result = cdev_add(my_cdev,mydev,1);
	if(result<0)
	{
		printk("\nchar device not created\n");
		unregister_chrdev_region(mydev,1);
		return (-1);
	}

	init_completion(&synch_completion);
	return 0;
			
}

void __exit synch_completion_exit(void)
{
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("device unregisterd that was allocated");
}

int NAME_open(struct inode *inode,struct file *filp)
{
	printk("\nthis is kernal..... open call\n");
	return 0;
}

int NAME_release(struct inode *inode, struct file *filp)
{
	printk("\n release method of character device\n");
	return 0;
}

ssize_t synch_completion_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	int cnt,len;
	printk("in read function\n");

	wait_for_completion(&synch_completion);

	len = strlen(kbuff);
	cnt = copy_to_user(Ubuff,kbuff, len);
	memset(kbuff, 0, sizeof(kbuff));

	return len-cnt;
}
ssize_t synch_completion_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	int cnt;
	printk("in write function");
	cnt = copy_from_user(kbuff, Ubuff, count);

	msleep(5000);
	complete(&synch_completion);

	return count - cnt;
}



module_init(synch_completion_init);
module_exit(synch_completion_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
