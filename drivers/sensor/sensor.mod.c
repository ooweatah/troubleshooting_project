#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

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
	{ 0xc2a194f5, "module_layout" },
	{ 0xbab76897, "cdev_del" },
	{ 0x37a0cba, "kfree" },
	{ 0x46a4b118, "hrtimer_cancel" },
	{ 0x8c03d20c, "destroy_workqueue" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x1bcd1cdc, "class_destroy" },
	{ 0xd8bb65d6, "device_destroy" },
	{ 0x49cd25ed, "alloc_workqueue" },
	{ 0x3c5d543a, "hrtimer_start_range_ns" },
	{ 0x2d0684a9, "hrtimer_init" },
	{ 0x741facb8, "kobject_put" },
	{ 0x4a3a74d6, "kobject_add" },
	{ 0x9cab3025, "kobject_init" },
	{ 0x51a63e14, "kmem_cache_alloc_trace" },
	{ 0x20e7fe75, "kmalloc_caches" },
	{ 0x2cac7900, "cdev_add" },
	{ 0xe8c43040, "cdev_init" },
	{ 0x3c8a0e89, "device_create" },
	{ 0x71148895, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x56470118, "__warn_printk" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x828e22f4, "hrtimer_forward" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x96848186, "scnprintf" },
	{ 0x637ff78b, "sysfs_notify" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "557AA3B08210C5E36BCC023");
