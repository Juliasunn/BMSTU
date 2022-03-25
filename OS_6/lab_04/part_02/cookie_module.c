#include <linux/module.h> // MODULE_LICENSE
#include <linux/kernel.h> // KERN_INFO
#include <linux/init.h>	  // ​Макросы __init и ​__exit
#include <linux/init_task.h>
#include <linux/vmalloc.h>

#include <linux/proc_fs.h> // proc_create
#define COOKIE_LENGTH PAGE_SIZE

MODULE_LICENSE("GPL");


static unsigned int read_pos;        //
static unsigned int write_pos;// 
static char *cookie_pot;
struct proc_dir_entry * dir_entry, *file_entry, *link_entry;

static int fortune_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "+proc file opend.....\t");
    return 0;
}
static int fortune_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "+proc file released.....\n");
    return 0;
}


static ssize_t fortune_write( struct file *filp, const char __user *buff, size_t len, loff_t *f_pos) //user->kernel

{
	printk(KERN_INFO "+ Module : Запись в файл");
	int space_available = (COOKIE_LENGTH - write_pos)+1;
	
	if (len > space_available) 
	{
		printk(KERN_INFO "+fortune: cookie pot is full!\n");
		return -ENOSPC;
	}
	if (copy_from_user( &cookie_pot[write_pos], buff, len )) 
	{
		printk(KERN_INFO "+ Module : Буфер полон!");
		return -EFAULT;
	}
	write_pos += len;
	cookie_pot[write_pos-1] = 0;
	return len;
}

static ssize_t fortune_read(struct file *file, char __user *buf, size_t count, loff_t *f_pos) //kernel->user
{
	int len;
	char tmp_buf[COOKIE_LENGTH]; 
	
	if (*f_pos > 0) //без этого чтение не остановится те зациклится	
		return 0;
	
	/* Wrap-around */
	if (read_pos >= write_pos) 
		read_pos  = 0;
	len = sprintf(tmp_buf, "%s\n", &cookie_pot[read_pos]);
	//len = snprintf(tmp_buf, count, "%s\n", &cookie_pot[read_pos]); // читаем count байт в tmp_buf,в len получаем кол-во реально прочитанных
	if (copy_to_user(buf, (const void *)tmp_buf, len))     //Returns number of bytes that could not be copied. On success, this will be zero.
		return -EFAULT;								
	
	read_pos += len;
	
	*f_pos += len;

	printk(KERN_INFO "+Module : чтение из файла\n");
	return len;
}

static struct proc_ops proc_fops =
	{
		
	.proc_open = fortune_open,
        .proc_read = fortune_read,
        .proc_write = fortune_write,
        .proc_release = fortune_release
};



static int __init cookie_md_init(void)
{
	printk(KERN_INFO "+ cookie module init\n");
	cookie_pot = (char *)vmalloc(COOKIE_LENGTH);
	
	if (!cookie_pot)
		return -ENOMEM;
	memset(cookie_pot, 0, COOKIE_LENGTH);
	
	dir_entry = proc_mkdir("fortune_dir", NULL);
	
	if (dir_entry == NULL)
	{
		vfree(cookie_pot);
		return -ENOMEM;
	}	
	file_entry = proc_create("fortune", 0666, dir_entry, &proc_fops);
	
	if (file_entry == NULL)
	{
		vfree(cookie_pot);
		remove_proc_entry("fortune_dir", NULL); 
		return -ENOMEM;
	}
	
	
	link_entry = proc_symlink("symlink_to_fortune", NULL, "/proc/fortune_dir/fortune");
	write_pos = 0;
	read_pos = 0;
	return 0;
}

static void __exit cookie_md_exit(void)
{
	printk(KERN_INFO "+ cookie module exit\n");
	
	
	remove_proc_entry("symlink_to_fortune", NULL); 
	remove_proc_entry("fortune",   dir_entry);
	remove_proc_entry("fortune_dir", NULL);  
	vfree(cookie_pot);
}



module_init(cookie_md_init);
module_exit(cookie_md_exit);
