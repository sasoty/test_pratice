#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/uaccess.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NHAT_NGUYEN");
MODULE_DESCRIPTION("excercise 1");
MODULE_VERSION("0.0");



static struct class *my_class;
static struct cdev my_cdev;
dev_t dev = 0;





static int my_file_opener(struct inode *inode, struct file *file)
{
    printk("device file opened\n");
    return 0;
}

static int my_file_closer(struct inode *inode, struct file *file)
{
    printk("device file closed \n");
    return 0;
}

static ssize_t my_file_reader(struct file *file, char __user *buffer, size_t length,loff_t *offset)
{
    copy_to_user(buffer, kernel_buffer, mem_size);
    printk("device file read success \n");
    return 0;
}

static ssize_t my_file_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset)
{
    copy_from_user(kernel_buffer, buffer, len);
    printk("device file writen success \n");
    return 0;
}

static struct file_operations fops = {
.owner = THIS_MODULE,
.open = my_file_opener,
.write = my_file_write,
.read = my_file_reader,
.release = my_file_closer
};

static int get_device_num(void)
{
    
    if((alloc_chrdev_region(&dev, 0, 1, "my_device")) <0)
    {
                printk(KERN_INFO "Cannot allocate major number\n");
                unregister_chrdev_region(dev,1);
                return -1;
        }

        if(IS_ERR(device_create(my_class,NULL,dev,NULL,"my_device")))
        {
            printk(KERN_INFO "Cannot create the Device 1\n");
            class_destroy(my_class);
            return -1;
        }    

        cdev_init(&my_cdev,&fops);
        if(( cdev_add(&my_cdev, dev,1)) < 0)
        {
            printk(KERN_INFO "Cannot add the device to the system\n");
              unregister_chrdev_region(dev,1);
            return -1;
        }


    
    printk(KERN_INFO "SUCCESS\n");
    return 0;
}


static void unregis_num(void)
{
   device_destroy(my_class,dev);
   class_destroy(my_class);
      unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "DELETTE\n");
}



static int __init run_exercise(void)
{
    get_device_num();

    printk(KERN_INFO "Device registered successfully\n");
    return 0;
}



static void __exit stop_exercise(void)
{
    unregis_num();
}


module_init(run_exercise);
module_exit(stop_exercise);

