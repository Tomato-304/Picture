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
	{ 0x2b4dfa79, "module_layout" },
	{ 0x6ade63da, "platform_driver_unregister" },
	{ 0x315494fa, "platform_device_unregister" },
	{ 0x3b86f6b2, "__platform_driver_register" },
	{ 0xc50c9827, "platform_device_register" },
	{ 0x5bf0ad7d, "cdev_add" },
	{ 0x7e0c3c2, "cdev_init" },
	{ 0xa3859b3a, "kmem_cache_alloc_trace" },
	{ 0xbb49aaf1, "kmalloc_caches" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x37a0cba, "kfree" },
	{ 0x8bcfa640, "cdev_del" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A8E28C4672F6FC394B6D482");
