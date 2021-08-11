#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"headers.h"

static int var1 = 10;
static int var2 = 20;

static int my_avg(void)
{
	static int res;
	res = my_add(var1,var2);
	res=res/2;

	printk(KERN_ALERT "avrage :%d\n",res);
	return 0;
}

static void my_exit(void)
{
	printk(KERN_ALERT"exiting from avrage...");
}


module_init(my_avg);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
