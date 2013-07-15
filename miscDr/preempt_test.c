
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <linux/version.h>

#define PREEMPT_DEBUG
#ifdef PREEMPT_DEBUG
#define DPRINTK(fmt, args...) printk(KERN_INFO "%s: " fmt, __FUNCTION__ , ## args)
#else
#define DPRINTK(fmt, args...)
#endif


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#define preempt_get_count preempt_count
#endif

static int preempt_open(struct inode *inode, struct file *file)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());
return 0;
}

static int preempt_release(struct inode *inode, struct file *file)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());
return 0;
}

static ssize_t preempt_read(struct file *file, char *buf, size_t count,
loff_t *ppos)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

return 0;
}

static ssize_t preempt_write(struct file * file, const char * buf,
size_t count, loff_t *ppos)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

return 0;
}

static int preempt_ioctl(struct inode *inode, struct file *file,
unsigned int cmd, unsigned long arg)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

return 0;
}

static struct file_operations char_fops = {
.owner = THIS_MODULE,
.open = preempt_open,
.release = preempt_release,
.read = preempt_read,
.write = preempt_write,
.ioctl = preempt_ioctl,
};

static struct miscdevice char_dev = {
.minor = MISC_DYNAMIC_MINOR,
.name = "preempt_test",
.fops = &char_fops
};

int __init preempt_init(void)
{
int ret;

DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

ret = misc_register(&char_dev);
if (ret) {
printk(KERN_ERR "misc_register() failedn");
}

DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

return ret;
}

void __exit preempt_exit(void)
{
DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());

misc_deregister(&char_dev);

DPRINTK("%d: preempt_count : %dn", __LINE__, preempt_get_count());
}

module_init(preempt_init);
module_exit(preempt_exit);

MODULE_LICENSE("GPL");
