#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NHAT_NGUYEN");
MODULE_DESCRIPTION("excercise 1");
MODULE_VERSION("0.0");

static dev_t dev_num;

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

static int get_device_num(int count)
{
    int ret;
    ret = register_chrdev_region(dev_num,count,"test");
    if(ret < 0)
    {
        printk(KERN_INFO "FAILED\n");
        return ret;
    }
    int major_num = MAJOR(dev_num);
    printk(KERN_INFO "%d", major_num);
    printk(KERN_INFO "SUCCESS\n");
    return 0;
}

static void unregis_num(void)
{
    unregister_chrdev_region(dev_num,2);
    printk(KERN_INFO "SUCCESS\n");
}

static struct file_operations fops = {
.open = my_file_opener,
.read = my_file_reader,
.release = my_file_closer
};

static int __init run_exercise(void)
{
    get_device_num(2);
    return 0;
}



static void __exit stop_exercise(void)
{
    unregis_num();
}


module_init(run_exercise);
module_exit(stop_exercise);
