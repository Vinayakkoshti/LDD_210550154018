#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/delay.h>


int sem_open(struct inode *inode,struct file *filp);
int sem_release(struct inode *inode, struct file *filp);
ssize_t semaphore_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);


struct file_operations synch_semaphore_fops = 
{
	.owner	= THIS_MODULE,
	.open	= sem_open,
	.release= sem_release,
	.read = semaphore_read

};




struct cdev *my_sem;
struct semaphore sem_dev;
int result;
int major,minor;
dev_t mydev;

static int semaphore_init(void)
{

	mydev=MKDEV(255,0); 
        major=MAJOR(mydev);
        minor=MINOR(mydev);
        printk("\n major number : %d minor number : %d\n",major,minor);

	result=register_chrdev_region(mydev,1,"Mysem");
        if(result<0)
        {
                printk("\nthe region is not obtainable\n");
                return(-1);

        }


	my_sem = cdev_alloc();
	my_sem->ops = &synch_semaphore_fops;
	result = cdev_add(my_sem,mydev,1);
	if(result<0)
	{
		printk("\ndevice not created\n");
		unregister_chrdev_region(mydev,1);
		return (-1);
	}

	sema_init(&sem_dev,1);
	return 0;
			
}


void semaphore_exit(void)
{
	unregister_chrdev_region(mydev,1);
	cdev_del(my_sem);
	printk("removed.....");
}


int sem_open(struct inode *inode,struct file *filp)
{
	printk("\nHey i opend file\n");
	return 0;
}


int sem_release(struct inode *inode, struct file *filp)
{
	printk("\n hey i closed file\n");
	return 0;
}

ssize_t semaphore_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	static unsigned int value=5;
	int return_count ;

	printk("In read function\n");

	if(down_interruptible(&sem_dev))
		return -ERESTARTSYS;
	
	msleep(5000);
	value++;

	return_count = copy_to_user(Ubuff, &value, sizeof(value));

	up(&sem_dev);
	return sizeof(value);
}


module_init(semaphore_init);
module_exit(semaphore_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
