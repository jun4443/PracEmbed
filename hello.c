#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

static struct miscdevice my_drv_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mymiscdrv",
};

int __init init_hello(void){
	printk(KERN_ALERT "[Module Message] Hello, Module. \n");
	misc_register(&my_drv_dev);
	return 0;
}

void __exit exit_hello(void){
	printk( KERN_ALERT "[Module Message] Do you really want to break up with me? \n" );
	misc_deregister(&my_drv_dev);
}

module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
