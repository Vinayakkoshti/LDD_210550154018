#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include "ioctl_header.h"



int Myopen(struct inode *inode, struct file *file_ioctl);
int Myrelease(struct inode *inode, struct file *file_ioctl);
long Myioctl(struct file *file_ioctl,unsigned int cmd, unsigned long arg );


struct file_operations calop=
{
	.owner = THIS_MODULE,
	.open = Myopen,
	.unlocked_ioctl = Myioctl,
	.release = Myrelease,
};

struct operator
{
	int num1;
	int num2;
};


int Myopen(struct inode *inode, struct file *file_ioctl)
{
	printk("open in ioctl\n");
	return 0;
}

long Myioctl(struct file *file_ioctl, unsigned int cmd,unsigned long arg)
{
	int op1,op2;
	struct operator *data;
	char u_buff[20];
	int count;
	int add,mul,sub,div;

	data = (struct operator *)u_buff; 
	count=copy_from_user(u_buff,(struct operator *)arg,sizeof(struct operator));
	op1 = data->num1;
	op2 = data->num2;

	switch(cmd)
	{
		case ADD:printk("In Addition\n");
			  add = op1 + op2;
			 printk("add: %d\n",add);
			 break;

		case SUB:printk("In Subtraction\n");
			 sub = op1-op2;
			 printk("sub: %d\n",sub);
			 break;

		case MUL:printk("In Multiplication\n");
			 mul =  op1*op2;
			 printk("mul: %d\n",mul);
			 break;

		case DIV:printk("In Division\n");
			 div = op1/op2;
			 printk("div: %d\n",div);
			 break;

		default:printk("invalid option\n");
			break;
	}
	return 0;
}

int Myrelease(struct inode *inode, struct file *file_ioctl)
{
	printk("In release\n");
	return 0;
}

struct cdev *MyIoctlCalDevice;
dev_t ioctl_cal_dn;

static int ioctl_init(void)
{
	printk("welcome to ioctl based calculator driver module\n");
	 
	int major,minor,result;

	result = alloc_chrdev_region(&ioctl_cal_dn,0,1,"MyIoctl");
	if(result < 0)
	{
		printk("Driver not allocated any region by kernel\n");
		return -1;
	}

	major = MAJOR(ioctl_cal_dn); 
	minor = MINOR(ioctl_cal_dn);
	printk("the driver is allocated region by the kernel with major number: %d and minor number: %d\n",major,minor);
	printk("\nFor ioctl based calculator driver, driver expected the following device:\nMyIoctlCalDevice\n");

	MyIoctlCalDevice = cdev_alloc();
	MyIoctlCalDevice->ops = &calop;

	result = cdev_add(MyIoctlCalDevice,ioctl_cal_dn,1);
	if(result <0)
	{
		printk("the device is not added by kernel\n");
		return -1;
	}
	return 0;
}


static void ioctl_exit(void)
{
	printk("bye from ioctl\n");
	cdev_del(MyIoctlCalDevice);
	unregister_chrdev_region(ioctl_cal_dn,1);
	printk("unregisterd ioctl\n");
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
