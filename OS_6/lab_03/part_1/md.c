#include <linux/init.h>
#include <linux/module.h>
#include <linux/init_task.h>

MODULE_LICENSE("GPL"); //GNU public license единственный обязательный макрос


 /*Возможные значения члена состояния task->state следующие:
[cpp] view plain copy

    #define TASK_RUNNING        0  
    #define TASK_INTERRUPTIBLE  1  
    #define TASK_UNINTERRUPTIBLE    2  
    #define __TASK_STOPPED      4  
    #define __TASK_TRACED       8  
    #define EXIT_ZOMBIE     16  
    #define EXIT_DEAD       32  
    #define TASK_DEAD       64  
    #define TASK_WAKEKILL       128  
    #define TASK_WAKING     256 */
static int __init md_init(void)
{
	printk("+ My first module was loaded!\n");
	struct task_struct *task = &init_task;
	do
	{
		printk(KERN_INFO  "id process: %d, name process: %s, current state: %ld, priority: %d, parent id: %d, parent name: %s\n", task->pid, task->comm, task->state, task->prio, \
		task->parent->pid, task->parent->comm);

		
	
	} while ((task = next_task(task)) != &init_task);
	

	printk(KERN_INFO  "[CURRENT] id process: %d, name process: %s, current state: %ld, priority: %d, parent id: %d, parent name: %s\n",
	 current->pid, current->comm, current->state, current->prio, current->parent->pid, current->parent->comm);
	
	return 0;
}

static void __exit md_exit(void)
{
	printk("+ My first module was unloaded!\n");
		printk(KERN_INFO  "[CURRENT] id process: %d, name process: %s, current state: %ld, priority: %d, parent id: %d, parent name: %s\n",
		current->pid, current->comm, current->state, current->prio, current->parent->pid, current->parent->comm);
}


module_init(md_init);
module_exit(md_exit);
