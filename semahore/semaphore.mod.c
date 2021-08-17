#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x1e2a3dfd, "module_layout" },
	{ 0xdf5f66fb, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xadecc241, "cdev_add" },
	{ 0x21cc1430, "cdev_alloc" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x581cde4e, "up" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xf9a482f9, "msleep" },
	{ 0xca5a7528, "down_interruptible" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "81AFDFC95191F74351EE832");
