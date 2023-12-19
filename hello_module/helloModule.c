#include<linux/module.h>

// The following includes are not initially required, but have been included for Assignment #3 - Sp 2020
#include<linux/sched/signal.h>
#include<linux/pid_namespace.h>
#include<linux/cdev.h>
#include<linux/proc_fs.h>
#include<linux/slab.h>

int proc_count(void)
{
  int i=0;
  struct task_struct *thechild;
  for_each_process(thechild)
    i++;
  return i;
}

unsigned long code_memory(void)
{
  unsigned long totalmem=0;
  unsigned long thismem;
  struct task_struct *thechild;
  for_each_process(thechild)
  {
    printk(KERN_INFO "pid %d",thechild->pid);
    if (thechild->mm != NULL) {
    thismem = thechild->mm->end_code - thechild->mm->start_code;
    printk(KERN_INFO " has codesize %lu.\n", thismem);
    totalmem = totalmem + thismem;
}
  }
  return totalmem;
}



int proc_init (void) {
  printk(KERN_INFO "helloModule: kernel module initialized\n");
  printk(KERN_INFO "There are %d running processes.\n", proc_count());
  printk(KERN_INFO "Running processes have %lu bytes of code.\n", code_memory());
  return 0;
}

void proc_cleanup(void) {
  printk(KERN_INFO "helloModule: performing cleanup of module\n");
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);

