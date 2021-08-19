#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#include "ioctl.h"

#define NAME MyCharDev

static int __init device_init(void);
static void __exit device_exit(void);

static int NAME_open(struct inode *inode,struct file *file);
static int NAME_release(struct inode *inode,struct file *file);
ssize_t NAME_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp);
ssize_t NAME_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp);
static long NAME_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

static struct stats = 
{
  int size;
  char buff[];
  int r_w;
};

static struct file_operations fops =
{
  .owner=THIS_MODULE,
  .read = NAME_read,
  .write = NAME_write,
  .open = NAME_open,
  .release = NAME_release,
  .unlocked_ioctl = NAME_ioctl
};

static struct cdev *my_cdev;

static int __init device_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n MAJOR NO. is %d.... MINOR NO. is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(Mydev,1,"MyCharDev");
	if(result<0)
	{
	  printk("\nThe region requested is not obtainable\n");
	  return (-1);
	}
	
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;
	
	result=cdev_add(my_cdev,Mydev,1);
	if(result<0)
	{
	  printk("\n The char device has not been created\n");
	  unregister_chrdev_region(Mydev,1);
	  return (-1);
	}
	return 0;
	
}


static void __exit device_exit(void)
{
	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n MAJOR NO. is %d.... MINOR NO. is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);
	cdev_del(my_cdev);
	printk("\n unregistered the stuff that was allocated .....Goodbye for ever......\n");
	return;
}

int NAME_open(struct inode *inode, struct file *file)
{
	printk("\n This is kernel OPEN call.....\n");
	return 0;
}

ssize_t NAME_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	char kbuf[100] = "I am sending from kernel buffer";
	int  result;
	ssize_t retval;
	result=copy_to_user(ubuf, kbuf,sizeof(kbuf));
	if(result == 0)
	{
	  printk("copy to user space is done: %d\n",sizeof(kbuf));
	  return sizeof(kbuf);
	}
	else
	{
	printk("Error writing to user\n");
	retval = -EFAULT;
	return retval;
	}
}

ssize_t NAME_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp)
{
	char kbuf[100];
	int  result;
	ssize_t retval;
	result=copy_from_user(kbuf, ubuf,count);
	if(result == 0)
	{
	  printk("message from user : %s\n",kbuf);
	  printk("\n%dbytes of data sucessfully written\n",count);
	  return count;
	}
	else
	{
	printk("Error writing data\n");
	retval = -EFAULT;
	return retval;
	}
}

int NAME_release(struct inode *inode, struct file *file)
{
	printk("\n This is kernel CLOSE call.....\n");
	return 0;
}

static long NAME_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  char kbuf[50];
  printk("IOCTL function\n");
  struct stats *st;

  switch(cmd)
  {
    case Size: st=(struct stats*)kbuf;
                
  }
