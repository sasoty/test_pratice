#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

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



static const char ____versions[]
__used __section("__versions") =
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x1c\x00\x00\x00\x48\xcf\x07\x77"
	"__register_chrdev\0\0\0"
	"\x18\x00\x00\x00\xf1\x7b\xac\xde"
	"class_create\0\0\0\0"
	"\x18\x00\x00\x00\xc4\x9d\xe2\x08"
	"device_create\0\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x18\x00\x00\x00\x3f\xdf\x84\xc5"
	"device_destroy\0\0"
	"\x18\x00\x00\x00\xe8\x6d\x33\xec"
	"class_destroy\0\0\0"
	"\x1c\x00\x00\x00\xc0\xfb\xc3\x6b"
	"__unregister_chrdev\0"
	"\x18\x00\x00\x00\x86\x05\x44\xe7"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "22E0E93BD2A2C5A998A7F81");
