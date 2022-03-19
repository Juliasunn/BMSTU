#include <linux/init.h>
#include <linux/module.h>
#include "md.h"
char *md1_data = " This is data from md1 ";

MODULE_LICENSE("GPL"); //GNU public license единственный обязательный макрос
//MODULE_AUTOR("Julia") 

char *md1_proc(void)
{
	return md1_data;
}

static char *md1_local(void)
{
	return md1_data;
}

extern char *md1_noexport(void)
{
	return md1_data;
}

static int __init md1_init(void)
{
	printk("+ md1 init\n");
	return 0;
}

static void __exit md1_exit(void)
{
	printk("+ md1 exit\n");
}

EXPORT_SYMBOL(md1_data);
EXPORT_SYMBOL(md1_proc);

module_init(md1_init);
module_exit(md1_exit);
