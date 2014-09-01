#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kthread.h>  // for threads
#include<linux/time.h>
#include<linux/timer.h>
#include<linux/init.h>
#include<linux/delay.h>
#include< <asm/semaphore.h>

static struct task_struct *thread1;
int num;


int thread_fn(void *data)
{

	printk(KERN_INFO "In thread1");
//	msleep(5);
	printk(KERN_INFO "after sleep");
	if(kthread_should_stop())
	{
		do_exit(0);
	}
	schedule();
	printk(KERN_INFO "after schedule");
	return 0;
}

int thread_init (void) 
{
 
	char name[8]="thread1";
	printk(KERN_INFO "-->in init\n");
	thread1 = kthread_run(thread_fn,NULL,name);
	printk(KERN_INFO "--->in parant\n");

	return 0;
}



void thread_cleanup(void)
{
	int ret;
	ret = kthread_stop(thread1);
	if(!ret)
	printk(KERN_INFO "Thread stopped");

}
MODULE_LICENSE("GPL"); 
module_init(thread_init);
module_exit(thread_cleanup);
MODULE_AUTHOR("revati ranjan");
