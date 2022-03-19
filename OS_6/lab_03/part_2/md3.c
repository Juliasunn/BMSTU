#include <linux/init.h>
#include <linux/module.h>
#include "md.h"

MODULE_LICENSE("GPL"); //GNU public license единственный обязательный макрос

static int __init md3_init(void)
{
	printk("+ md3 init\n");
	printk("+ md3 call md1_data %s\n", md1_data);
	printk("+ md3 call md1_proc %s\n", md1_proc());
	//printk("+ call md1_local %s\n", md1_local());
	//printk("+ call md1_noexport %s\n", md1_noexport());
	return 0;
}

static void __exit md3_exit(void)
{
	printk("+ md3 exit\n");
}

module_init(md3_init);
module_exit(md3_exit);
