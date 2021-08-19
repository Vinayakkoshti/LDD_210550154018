#include <linux/cdev.h> 
#include <linux/fs.h> 
#include <linux/kdev_t.h> 
#include <linux/types.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/uaccess.h>
#include "jiff.h"
#include <linux/jiffies.h>
#include <linux/string.h>

int my_open_fn(struct inode *inode, struct file *file_d);
int my_release_fn(struct inode *inode,struct file *file_d);
ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp);
long my_ioctl_fn(struct file *file_d,unsigned int cmd,unsigned long arg);

static char k_buff[100];
static int delay_trigger = 0;
struct file_operations op ={
	.owner = THIS_MODULE,
	.open = my_open_fn,
	.read = my_read_fn,
	.unlocked_ioctl = my_ioctl_fn,
	.release = my_release_fn,
};

int my_open_fn(struct inode *inode, struct file *file_d)
{
	printk("My device is using My charcter driver\n");
	return 0;
}

long my_ioctl_fn(struct file *file_d, unsigned int cmd,unsigned long arg)
{
	char *p = "data from kernel";
	int i =0;
	unsigned long timeout;
	timeout = jiffies + (arg * HZ); 
	while(time_before(jiffies,timeout))
	{
		continue;
	}
	while(p[i] != '\0')
	{
		*(k_buff+i) = p[i];
		i++;
	}
	k_buff[i] = '\0';
	printk("the data send from kernel to user: %s\n",k_buff);
	delay_trigger++;
	return 0;
}

ssize_t my_read_fn(struct file *file_d, char __user *u_buff, size_t count, loff_t *offp)
{
	int re,i = 0;
	ssize_t amtdata;
	printk("data got for send to user is: %s\n",k_buff);
	
	i=strlen(k_buff);

	if(delay_trigger == 1)
	{	
		re = copy_to_user(u_buff,(const char *)k_buff, i);

		if(re >= 0) 
		{	
			printk("total data successfully copy from kernel to user\n");
			amtdata = i;
			delay_trigger = 0;
			return amtdata;
		}
		else
		{
			printk("error in reading\n");
			delay_trigger = 0;
			return -1;
		}
	}
	return amtdata;
}

int my_release_fn(struct inode *inode, struct file *file_d)
{
	printk("my device in now logging off\n");
	return 0;
}
struct cdev *MyCharDevice;
dev_t my_driver_no;
static int my_driver_mod_init(void)
{
	int major,minor;
	my_driver_no = MKDEV(255,0);
	major = MAJOR(my_driver_no);
	minor = MINOR(my_driver_no);
	
	printk("module logging in\n");

	int res = register_chrdev_region(my_driver_no,1,"MyCharDriver");

	if(res < 0) 
	{
		printk("\nDriver not allocated with driver number\n");
		return -1;
	}

	printk("my charcter driver got the region with major no %d and minor no %d\n",major,minor);
	printk("\nFor use the driver, driver expect the device having the following name:\nMyCharDevice\n");
	MyCharDevice = cdev_alloc();
	MyCharDevice->ops = &op;

	int result = cdev_add(MyCharDevice,my_driver_no,1);

	if(result < 0) 
	{
		printk("Driver not recognised by kernel\n");
		return -1;
	}

	return 0;
}

static void my_driver_mod_exit(void)
{
	printk("module going to be logging off\n");
	unregister_chrdev_region(my_driver_no,1);
	printk("Driver now unregister\n");
	cdev_del(MyCharDevice);
	printk("kernel forgot my chracter driver\n");
}


module_init(my_driver_mod_init);
module_exit(my_driver_mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
MODULE_DESCRIPTION("charter driver linux kerner module");
