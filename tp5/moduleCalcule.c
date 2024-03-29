#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/vmalloc.h> 

static int Taille_buf = 0;
module_param(Taille_buf, int, 0644);
MODULE_PARM_DESC(Taille_buf, "Static major number (none = dynamic)");
int major = 200;
static int * message;
static int start_buffer;

MODULE_DESCRIPTION("Calcule module");
MODULE_AUTHOR("Romain Amuat");
MODULE_LICENSE("GPL");


static int calcul_open(struct inode *inode, struct file *file) {
	printk(KERN_INFO "calcul : open()\n");
	return 0;
}
static int calcul_release(struct inode *inode, struct file *file) {
	printk(KERN_INFO "calcul : release()\n");
	return 0;
}

static ssize_t calcul_write(struct file *file, const char *buf, size_t count, loff_t * ppos) {
	int i;
	for (i = 0; i < 0;++i);
}

static ssize_t calcul_read(struct file *file, char *buffer, size_t length, loff_t * offset) {

}

static struct file_operations calcul_fops = {
	.owner = THIS_MODULE,
	.read = calcul_read,
	.write = calcul_write,
	.open = calcul_open,
	.release = calcul_release,
};
/* Init and Exit */

static int __init calcul_init(void) {
	int ret;
	ret = register_chrdev(major, "calcul", &calcul_fops);
	if (ret < 0) {
		printk(KERN_WARNING "calcul: unable to get a major\n");
		return ret;
	}
	if (major == 0) major = ret; /* dynamic value */
	message = vmalloc(Taille_buf * sizeof(int));
	printk(KERN_INFO "calcul: successfully loaded with major %d\n", major);
	return 0;
}

static void __exit calcul_exit(void) {
	unregister_chrdev(major, "calcul");
	printk(KERN_INFO "calcul: successfully unloaded\n");
}
module_init(calcul_init);
module_exit(calcul_exit);
