#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/slab.h>

#define BUFFER_MAX (64)
#define OK (0)
#define ERROR (-1)

struct cdev *gdev;
struct file_operations *gfile;
dev_t devno;
unsigned int setdevnum = 1;
int reg_major = 232;
int reg_minor = 0;
char buffer[BUFFER_MAX];
struct semaphore sema;
int open_count = 0;


int hello_open(struct inode *p, struct file *f)
{
    
    down(&sema);
    if(open_count >= 1)  // 临界区代码可以睡眠
    {
        up(&sema);
        printk(KERN_INFO "device is busy, hello_open failed!!\n");
        return -EBUSY;
    }
    open_count++;
    up(&sema);
    printk(KERN_INFO "hello_open OK\n");
    return OK;
}

int hello_close(struct inode *inode, struct file *file)
{
    if(open_count != 1)
    {
        printk(KERN_INFO "something wrong, hello_close failed!!\n");
        return -EFAULT;
    }
    open_count--;
    printk(KERN_INFO "hello_close\n");
    return 0;
}

ssize_t hello_write(struct file *f, const char __user *u, size_t s, loff_t *l)
{
    printk(KERN_INFO "hello_write\n");
    int writelen = 0;
    writelen = BUFFER_MAX > s ? s : BUFFER_MAX;
    if(copy_from_user(buffer, u, writelen))
    {
        return -EFAULT;
    }
    return writelen;
}

ssize_t hello_read(struct file *f, char __user *u, size_t s, loff_t *l)
{
    printk(KERN_INFO "hello_read\n");
    int readlen = 0;
    readlen = BUFFER_MAX > s ? s : BUFFER_MAX;
    if(copy_to_user(u, buffer, readlen))
    {
        return -EFAULT;
    }
    return readlen;
}

int hello_init(void)
{
    devno = MKDEV(reg_major, reg_minor);
    if(register_chrdev_region(devno, setdevnum, "hello LOL") == OK)
    {
        printk(KERN_EMERG "register_chrdev_region ok\n");
    }
    else
    {
        printk(KERN_EMERG "register_chrdev_region error\n");
        return ERROR;
    }

    printk(KERN_EMERG "hello driver init\n");

    gdev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    gfile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);
    
    gfile -> open = hello_open;
    gfile -> release = hello_close;
    gfile -> read = hello_read;
    gfile -> write = hello_write;
    gfile -> owner = THIS_MODULE;
    
    cdev_init(gdev, gfile);
    cdev_add(gdev, devno, 3);

    sema_init(&sema, 1);
    return 0;
}

void __exit hello_exit(void)
{
    cdev_del(gdev);
    unregister_chrdev_region(devno, setdevnum);
    return;
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
