#include <linux/init.h>
#include <linux/module.h>
#include "md.h"

MODULE_LICENSE("GPL"); //GNU public license единственный обязательный макрос

static int __init md2_init(void)
{
	printk("+ md2 init\n");
	printk("+ md2 call md1_data %s\n", md1_data);
	printk("+ md2 call md1_proc %s\n", md1_proc());
	//printk("+ call md1_local %s\n", md1_local());
	printk("+ call md1_noexport %s\n", md1_noexport());
	return -1;
}

static void __exit md2_exit(void)
{
	printk("+ md2 exit\n");
}

module_init(md2_init);
module_exit(md2_exit);
