#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>

static struct timer_list my_timer;
dev_t ktm_dn;
static int count=0;

static void tim_call_bck(struct timer_list *timer) // timer call back function
{
	printk("The timer callback function will called [%d]\n",count++);

}

static int tim_on(void)
{

	timer_setup(&my_timer,tim_call_bck,0); 
	int ret = mod_timer(&my_timer,jiffies + msecs_to_jiffies(2000)); 
	if(ret == 0) 
	{
		printk("Not able to fire\n");
	}
	return 0;
}

static void tim_off(void)
{
	printk("driver going to log off\n");
	del_timer(&my_timer);
	printk("good bye\n");
}

module_init(tim_on);
module_exit(tim_off);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
