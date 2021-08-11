#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/string.h>

static int add(int,int);
static int mul(int,int);
static int sub(int,int);
static int div(int,int);

static char* opt ="add";
static int var1 =1;
static int var2=2;

module_param(opt,charp,S_IRUGO);
module_param(var1,int,S_IRUGO);
module_param(var2,int,S_IRUGO);


static int param_init(void)
{
//	printk(KERN_ALERT "var1 :%d var2 :%d opt :%s\n",var1,var2,opt);

	if(strcmp(opt,"add")==0)
	{
	 printk(KERN_ALERT"add : %d\n",add(var1,var2));
	}
	else if(strcmp(opt,"mul")==0)
	{	
	 printk(KERN_ALERT "mul: %d\n",mul(var1,var2));
	}
	else if(strcmp(opt,"sub")==0)
	{

	 printk(KERN_ALERT "sub : %d\n",sub(var1,var2));
	}
	else if(strcmp(opt,"div")==0)
	{
	 printk(KERN_ALERT"div :%d\n",div(var1,var2));
	}	
	return 0;
}


static void param_exit(void)
{
	printk(KERN_ALERT "exiting from module");
}

static int add(int var1,int var2)
{
	return (var1+var2);
}

static int mul(int var1,int var2)
{
	return (var1*var2);
}

static int sub(int var1,int var2)
{
	return (var1-var2);
}

static int div(int var1,int var2)
{
	return (var1/var2);
}




module_init(param_init);
module_exit(param_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinayak");
