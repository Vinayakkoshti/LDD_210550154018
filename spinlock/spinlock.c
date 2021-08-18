#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/spinlock.h>
#include<linux/delay.h>

#define NAME spin_dev

int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t synch_spinlock_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);


struct file_operations fops = 
{
	.owner	= THIS_MODULE,
	.open	= NAME_open,
	.release= NAME_release,
	.read = synch_spinlock_read

};

struct cdev *my_cdev;
spinlock_t slock;
int result;
int major,minor;
dev_t mydev;

static int __init synch_spinlock_init(void)
{

	mydev=MKDEV(255,0); 
        major=MAJOR(mydev);
        minor=MINOR(mydev);
        printk("\n major number %d.....minor number %d\n",major,minor);

	result=register_chrdev_region(mydev,1,"spindevice");
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
	spin_lock_init(&slock);
	return 0;
			
}

void __exit synch_spinlock_exit(void)
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


ssize_t synch_spinlock_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	static unsigned int value=5;
	printk("in read function\n");

	spin_lock(&slock);
	mdelay(1000);
	value++;
	copy_to_user(Ubuff, &value, sizeof(value));
	spin_unlock(&slock);

	return sizeof(value);
}




module_init(synch_spinlock_init);
module_exit(synch_spinlock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
