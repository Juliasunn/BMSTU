//в программе каждый cat выводит по одной введенной строке а не все сразу

#include <linux/init.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/proc_fs.h>	
#include <linux/seq_file.h>	

#define PROC_NAME	"new_seqfile"
#define BUFFER_LENGTH PAGE_SIZE



#define FILE_NAME "seqfile"
#define DIR_NAME "seqdir"
#define LINK_NAME "seqlink"

MODULE_AUTHOR("Yulechka");
MODULE_LICENSE("GPL");

static unsigned long write_pos; 
static char *file_buffer;

struct proc_dir_entry * dir_entry, *file_entry, *link_entry;

static void *my_seq_start(struct seq_file *s, loff_t *pos) //вызывается при cat и после stop(). если переменная pos отлична от 0 значит дошли до конца файла
{
	printk(KERN_INFO "+Module: my_seq_start called %lld %ld\n", *pos, write_pos);
	static unsigned long begin_flag = 0;

	/* еще не дошли до конца последователности ? */	
	if ( *pos == 0)
	{	
		/* yes => взвращаем ненулевое значение чтобы начать движение по последовательности используя  next()*/
		return &begin_flag;//переходим в show() и next()
	}
	else
	{
		/* no => прочитали все данные из последовательности, возвращаемся в ее начало (кольцевой буффер) */
		*pos = 0;
		return NULL; //переходим в stop()
	}
}

/**
 * This function is called after the beginning of a sequence.
 * It's called untill the return is NULL (this ends the sequence).
 *
 */
static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos) /*до этого вызывается show(). Если при чтении дошли до конца то возвращаем v в начало,
                                                                  pos устанавливаем > 0 () */
{    
	static unsigned long next_flag = 0;
	unsigned long *read_pos = (unsigned long *)v;//таким образом изменяем значение v
	printk(KERN_INFO "+Module: my_seq_next called %ld\n", *read_pos);	
	if ( *read_pos >= write_pos)
	{
	   (*read_pos)=0; 
	   (*pos)=1;
	}
	return NULL; //возвращаемся в start().
}


static void my_seq_stop(struct seq_file *s, void *v)//вызывается после того как next вернул NULL 
{
	printk(KERN_INFO "+Module: my_seq_stop called\n");
}

/**
 * This function is called for each "step" of a sequence
 *
 */
static int my_seq_show(struct seq_file *s, void *v)
{
	
	unsigned long *read_pos = (unsigned long *) v; //позиция чтения
	char tmp[BUFFER_LENGTH];
	
	unsigned long len = snprintf(tmp, BUFFER_LENGTH, "%s", &file_buffer[*read_pos]);
	
	printk(KERN_INFO "+Module: my_seq_show called %ld %s %ld %s\n", *read_pos, &file_buffer[*read_pos], len, tmp);
									
	seq_printf(s, "%s\n", tmp);
	(*read_pos) += (1+len); //snprintf - возвращает число символов кроме '\0'	
	return 0; //если не 0 то пользователю ничего не выводится
}


ssize_t my_seq_write(struct file *filp, const char __user *buf, size_t len, loff_t *offp) //от user *buf в file_buffer
{
	printk(KERN_INFO "+ Module : my_seq_write called");
	int space_available = (BUFFER_LENGTH - write_pos)+1;
	
	if (len > space_available) 
	{
		printk(KERN_INFO "+Module: file_buffer is full!\n");
		return -ENOSPC;
	}
	if (copy_from_user( &file_buffer[write_pos], buf, len )) 
	{
		printk(KERN_INFO "+ Module : file_buffer is full!");
		return -EFAULT;
	}
	write_pos += len;
	file_buffer[write_pos-1] = '\0';
	return len;
} 

 

static struct seq_operations my_seq_ops = {
	.start = my_seq_start,
	.next  = my_seq_next,
	.stop  = my_seq_stop,
	.show  = my_seq_show
};

/**
 * This function is called when the /proc file is open.
 *
 */
static int my_open(struct inode *inode, struct file *file)
{
	int fd = seq_open(file, &my_seq_ops);
	printk(KERN_INFO "+ Module : my_open called %d", fd);
	return fd;
};


 static struct proc_ops fops = 
 {   
    .proc_open = my_open,
    .proc_read = seq_read,
    .proc_write = my_seq_write,
    .proc_lseek=seq_lseek,
    .proc_release = seq_release   
};	
	
static int __init my_init(void)
{
	printk(KERN_INFO "+ Module : module init\n");
	file_buffer = (char *)vmalloc(BUFFER_LENGTH);
	
	if (!file_buffer)
		return -ENOMEM;
	memset(file_buffer, 0, BUFFER_LENGTH); //инициализация буфера файла
	
	
	dir_entry = proc_mkdir(DIR_NAME, NULL);
	
	if (dir_entry == NULL)
	{
		return -ENOMEM;
	}	
	file_entry = proc_create(FILE_NAME, 0666, dir_entry, &fops);
	
	if (file_entry == NULL)
	{
		remove_proc_entry("seq_dir", NULL); 
		return -ENOMEM;
	}
	link_entry = proc_symlink(LINK_NAME, NULL, "/proc/seqdir/seqfile");
        write_pos = 0;
	return 0;
}


static void __exit my_exit(void)
{
	printk(KERN_INFO "+ Module : module exit\n");
		
	remove_proc_entry(LINK_NAME, NULL); 
	remove_proc_entry(FILE_NAME, NULL);
	remove_proc_entry(DIR_NAME, NULL); 
	vfree(file_buffer);
}

module_init(my_init);
module_exit(my_exit);		
