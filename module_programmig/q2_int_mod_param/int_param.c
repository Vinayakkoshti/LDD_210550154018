#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int var_int = 50;

module_param(var_int,int,S_IRUGO);


static int param_int(void)
{
	
	printk(KERN_ALERT "int value : %d\n",var_int);

	return 0;
}

static void param_exit(void)
{
	printk(KERN_ALERT "exiting from module....\n");
}


module_init(param_int);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
MODULE_DESCRIPTION("Demo of module param.");
