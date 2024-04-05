#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/err.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NHAT_NGUYEN");
MODULE_DESCRIPTION("excercise 1");
MODULE_VERSION("0.0");



static struct class *my_class;


static int my_file_opener(struct inode *inode, struct file *file)
{
    
    return 0;
}

static int my_file_closer(struct inode *inode, struct file *file)
{

    return 0;
}

static ssize_t my_file_reader(struct file *file, char *buffer, size_t length,loff_t *offset)
{

    return 0;
}
static struct file_operations fops = {
.owner = THIS_MODULE,
.open = my_file_opener,
.read = my_file_reader,
.release = my_file_closer
};

static int get_device_num(void)
{
    int ret;
    ret = register_chrdev(122,"my_device",&fops);
    printk(KERN_INFO "allocated\n");
    if(ret < 0)
    {
        printk(KERN_INFO "FAILED\n");
        return ret;
    }
    printk(KERN_INFO "SUCCESS\n");
    return 0;
}

static void unregis_num(void)
{
   device_destroy(my_class,122);
   class_destroy(my_class);
    unregister_chrdev(122,"my_device");
    printk(KERN_INFO "DELETTE\n");
}



static int __init run_exercise(void)
{
    get_device_num();
    my_class = class_create(THIS_MODULE,"my_class");
    if (IS_ERR(my_class)) {
        unregister_chrdev(122, "my_device");
        printk(KERN_INFO "Failed to create class\n");
        return PTR_ERR(my_class);
    }

    device_create(my_class,NULL,122,NULL,"my_device");
    printk(KERN_INFO "Device registered successfully\n");
    return 0;
}



static void __exit stop_exercise(void)
{
    unregis_num();
}


module_init(run_exercise);
module_exit(stop_exercise);

