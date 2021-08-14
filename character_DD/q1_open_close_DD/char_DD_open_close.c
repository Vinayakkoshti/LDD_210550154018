#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#define NAME MyCharDevice



int NAME_open(struct inode *inode , struct file *filp);

int NAME_release(struct inode *inode , struct file *filp);

struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open  = NAME_open,	
	.release = NAME_release,

};


struct cdev *my_cdev;


static int CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t mydev;
	mydev = MKDEV(255,0);
        MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk(KERN_ALERT"\nmajor number is %d  minor number is %d \n",MAJOR,MINOR);
	
	result = register_chrdev_region(mydev,1,"MyCharDevice");
	
	if(result<0)
	{
		printk(KERN_ALERT"The region is requested for is not obtainable\n");
		return (-1);
	}

	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	result = cdev_add(my_cdev,mydev,1);

	if(result<0)
	{
		printk(KERN_ALERT"char Device has not been Created....\n");
		unregister_chrdev_region(mydev,1);
		return (-1);
	}

	return 0;
}


void CharDevice_exit(void)
{
	dev_t mydev;
	int MAJOR,MINOR;
	mydev = MKDEV(255,0);
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);

	printk(KERN_ALERT"the major number is %d and minor number is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk(KERN_ALERT"I have deleted stuff that have created, bye love you\n");

}



int NAME_open(struct inode *inode , struct file *filp)
{
	printk(KERN_ALERT"hey Buddy i am Opend file LOL !!!");
	return 0;
}


int NAME_release(struct inode *inode , struct file *filp)
{

	printk(KERN_ALERT"hey Buddy i am Closed file LOL !!!");
	return 0;
}

module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cdac vinayak");
