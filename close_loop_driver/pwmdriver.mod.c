#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xcf79a31, "module_layout" },
	{ 0x7fe29886, "class_destroy" },
	{ 0x121cbf25, "class_unregister" },
	{ 0xfaaad20d, "device_destroy" },
	{ 0x81fc2fd3, "device_remove_file" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x320dca76, "device_create_file" },
	{ 0xcc2e009e, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x3949871f, "__class_create" },
	{ 0x1f87bfc, "__register_chrdev" },
	{ 0x20c55ae0, "sscanf" },
	{ 0xac8f37b2, "outer_cache" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "85F66FA19E4304F692D364D");
