#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

int my_add(int ,int);

int my_add(var1,var2)
{
	printk(KERN_ALERT "Im in add\n");

	return (var1+var2);
}

EXPORT_SYMBOL_GPL(my_add);


static int my_fun(void)
{
	printk("hello\n");
	return 0;
}
static void my_exit(void)
{
	printk(KERN_ALERT "exiting from add");

}


module_init(my_fun);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
