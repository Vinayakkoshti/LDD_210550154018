#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>



/*srction for addition start*/
/*function declaration of add functionality*/
int open_add(struct inode *inode, struct file *file_op_add);
int release_add(struct inode *inode, struct file *file_op_add);
ssize_t write_add(struct file *file_op_add,const char __user *u_buff,size_t count,loff_t *offp );
ssize_t read_add(struct file *file_op_add,char __user *u_buff, size_t count, loff_t *offp);

static int add_result; // for storing the result of addition
/*add operation structure*/
struct file_operations fop_add=
{
	.owner = THIS_MODULE,
	.open = open_add,
	.read = read_add,
	.write = write_add,
	.release = release_add,
};

/*add open function defination*/
int open_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is using MyCalDriver\n");
	return 0;
}

/*add read function defination that read the user data*/
ssize_t read_add(struct file *file_op_add,char __user *u_buff,size_t count,loff_t *offp)
{
	ssize_t sdata;
	int result;
	const int *re  = &add_result; // taking the addressess of add_result
	result = copy_to_user(u_buff,re,sizeof(add_result)); // the result of addition com=py from kernel space to user
	if(result >= 0) // comdition to check whether copy operation successful or not
	{
		printk("successfully send the result\n");
		sdata = sizeof(add_result);
		return sdata;
	}
	else
	{
		printk("sending data not done\n");
		return -1;
	}
}

/*adiition write function defination*/
ssize_t write_add(struct file *file_op_add, const char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	int k_buff[2]; //initialize variable to where two integers from user space will store
	ssize_t rdata;
	result = copy_from_user((char *)k_buff,u_buff,count); // copy from user
	if(result >= 0) // condition for checking whether copy from user done or not
	{
		printk("the data from user are:%d and %d\n",(int)k_buff[0],(int)k_buff[1]); // print the two integer value 
		//collecting from user withinteger type cast
		add_result = (int)k_buff[0] + (int)k_buff[1]; 
		printk("the addition result is: %d and its send to user space\n",add_result);
		rdata = count;
		return rdata; //send the amount of data cpoied
	}
	else
	{
		printk("not able to read from user\n");
		return -1;
	}
}

/*add release function defination*/
int release_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is logging off from MyCalDriver\n");
	return 0;
}

/*sub operation function declaration*/
int open_sub(struct inode *inode, struct file *file_op_sub);
int release_sub(struct inode *inode, struct file *file_op_sub);
ssize_t write_sub(struct file *file_op_sub,const char __user *u_buff,size_t count, loff_t *offp);
ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp);

static int sub_result;
/*sub operation structure*/
struct file_operations fop_sub=
{
	.owner = THIS_MODULE,
	.open = open_sub,
	.read = read_sub,
	.write = write_sub,
	.release = release_sub,
};

/*sub open function defination*/
int open_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is using MyCalDriver\n");
	return 0;
}

/*subtraction write function defination*/
ssize_t write_sub(struct file *file_op_sub, const char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	int k_buff[2];
	ssize_t rdata;
	result = copy_from_user((char *)k_buff, u_buff, count);
	if(result >= 0)
	{
		printk("data successfully received from user asr: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		sub_result = (int)k_buff[0] - (int)k_buff[1];
		printk("the result of subtraction is: %d and the result now send to the user\n",sub_result);
		rdata = count;
		return rdata;
	}
	else
	{
		printk("data received not done successfully\n");
		return -1;
	}
}

/*sub read function defination*/
ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp)
{
	int result;
	ssize_t sdata;
	result = copy_to_user(u_buff,&sub_result,sizeof(sub_result));
	if (result >=0)
	{
		printk("The result successfully send to the user\n");
		sdata = sizeof(sub_result);
		return sdata;
	}
	else
	{
		printk("the send not done");
		return -1;
	}
}


/*sub release function defination*/
int release_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is logging of from MyCalDriver\n");
	return 0;
}

/*multiplication function declaration*/
int open_mul(struct inode *inode,struct file *file_op_mul);
int release_mul(struct inode *inode, struct file *file_op_mul);
ssize_t write_mul(struct file *file_op_mul, const char __user *u_buff,size_t count,loff_t *offp);
ssize_t read_mul(struct file *file_op_mul,char __user *u_buff,size_t count, loff_t *offp);

static int mul_result;

/*file operation for multiplicatio*/
struct file_operations fop_mul=
{
	.owner = THIS_MODULE,
	.open = open_mul,
	.read = read_mul,
	.write = write_mul,
	.release = release_mul,
};

/*open multiplication function defination*/
int open_mul(struct inode *inode, struct file *file_op_mul)
{
	printk("you have oprn the multiplication section\n");
	return 0;
}

/*multiplication write function defination*/
ssize_t write_mul(struct file *file_op_mul,const char __user *u_buff,size_t count, loff_t *offp)
{
	int result;
	int k_buff[2];
	ssize_t rdata;
	result = copy_from_user((char *)k_buff,u_buff,count);
	if(result >= 0)
	{
		printk("the data from user get successfully\n");
		printk("the data from user: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		mul_result = (int)k_buff[0] * (int)k_buff[1];
		printk("the result of multiplication: %d and send to user\n",mul_result);
		rdata = count;
		return rdata;
	}
	else
	{
		printk("error in writing data from user\n");
		return -1;
	}
}

/*multiplication read function defination*/
ssize_t read_mul(struct file *file_op_mul,char __user *u_buff,size_t count,loff_t *offp)
{
	int result;
	ssize_t sdata;
	result = copy_to_user(u_buff,&mul_result,sizeof(mul_result));
	if(result >= 0)
	{
		printk("the send successfully done\n");
		sdata = sizeof(mul_result);
		return sdata;
	}
	else
	{
		printk("The send operation not done successfully\n");
		return -1;
	}
}

/*release multiplication function defination*/
int release_mul(struct inode *inode,struct file *file_op_mul)
{
	printk("Multiplication operation end\n");
	return 0;
}

/*division function declaration*/
int open_div(struct inode *inode,struct file *file_op_div);
int release_div(struct inode *inode,struct file *file_op_div);
ssize_t write_div(struct file *file_op_div, const char __user *u_buff,size_t count,loff_t *offp);
ssize_t read_div(struct file *file_op_div, char __user *u_buff, size_t count, loff_t *offp);

static int div_result;

/*file operation structure for division*/
struct file_operations fop_div=
{
	.owner = THIS_MODULE,
	.open = open_div,
	.read = read_div,
	.write = write_div,
	.release = release_mul,
};

/*open operation for division*/
int open_div(struct inode *inode,struct file *file_op_div)
{
	printk("you are in division module section\n");
	return 0;
}

/*write division operation*/
ssize_t write_div(struct file *file_op_div, const char __user *u_buff,size_t count, loff_t *offp)
{
	int k_buff[2];
	int result;
	ssize_t rdata;
	result = copy_from_user((char *)k_buff,u_buff,count);
	if(result >= 0)
	{
		printk("data received from user done and data are: %d and %d\n",(int)k_buff[0],(int)k_buff[1]);
		div_result = (int)k_buff[0]/(int)k_buff[1];
		printk("the division result is: %d and now send to user",div_result);
		rdata = count;
		return rdata;
	}
	else
	{
		printk("data read not done successfully\n");
		return -1;
	}
}

/*dividion read operation*/
ssize_t read_div(struct file *file_op_div,char __user *u_buff, size_t count,loff_t *offp)
{
	int result;
	ssize_t sdata;
	result = copy_to_user(u_buff,&div_result,sizeof(div_result));
	if(result >= 0)
	{
		printk("data send to user done\n");
		sdata = sizeof(div_result);
		return sdata;
	}
	else
	{
		printk("data send not done successfully\n");
		return -1;
	}
}

/*divition release operation*/
int release_div(struct inode *inode,struct file *file_op_div)
{
	printk("logging off fron division module\n");
	return 0;
}

/*four character devices initializations*/
struct cdev *AddDev;
struct cdev *SubDev;
struct cdev *MulDev;
struct cdev *DivDev;

/*device number variable initialization*/
dev_t my_device_number;
dev_t mdn_add;
dev_t mdn_sub;
dev_t mdn_mul;
dev_t mdn_div;

//module initialization
static int calcu_mod_on(void) 
{
	int on_success;
	int major;

	on_success = alloc_chrdev_region(&my_device_number, 0,4,"MyCalDriver"); // dynamically allocate device number having four indexes

	if (on_success < 0) // if not success
	{
		printk(KERN_ALERT "not successfully allocated region\n");
		return 0;
	}

	major = MAJOR(my_device_number); // finding the major number
	printk(KERN_ALERT "the allocated driver having the major number: %d\n\nminor no 0: for AddDev device\nminor no 1: for SubDev device\nminor no 2: for MulDev device\nminor no 3: for DivDev device\n",major);
	
	printk("\nFor calculation purpose deiver expected the following device with its major and minor number:\naddition: AddDev\nsubtraction: SubDev\nmultiplication: MulDev\ndivision: DivDev\n");
	/*making separate device number with same major number*/
	mdn_add = MKDEV(major,0);
	mdn_sub = MKDEV(major,1);
	mdn_mul = MKDEV(major,2);
	mdn_div = MKDEV(major,3);

	AddDev = cdev_alloc(); //dynamically allocate AddDev as character driver so that kernel know about it
	AddDev->ops = &fop_add;// pointing the function pointer
	
	SubDev = cdev_alloc();
	SubDev->ops = &fop_sub;

	MulDev = cdev_alloc();
	MulDev->ops = &fop_mul;

	DivDev = cdev_alloc();
	DivDev->ops = &fop_div;

	int result_add = cdev_add(AddDev,mdn_add,1); // add AddDev device to the kernel section
	if(result_add <0 ) // condition whether addition of device successfull or not
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	int result_sub = cdev_add(SubDev,mdn_sub,1);
	if(result_sub <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	int result_mul = cdev_add(MulDev,mdn_mul,1);
	if(result_mul <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	int result_div = cdev_add(DivDev,mdn_div,1);
	if(result_div <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	return 0;
}
//module exit
static void calcu_mod_off(void)
{
	printk("your driver going to logging off\n");
	/*delete each device location separately*/
	cdev_del(AddDev);
	cdev_del(SubDev);
	cdev_del(MulDev);
	cdev_del(DivDev);
	cdev_del(my_device_number);
	printk("all devices are logging off\n");
	/*unregister from the kernel space*/
	unregister_chrdev_region(my_device_number, 4);
	printk("your driver log off\n");
}

module_init(calcu_mod_on);
module_exit(calcu_mod_off);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
