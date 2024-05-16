#include <rtthread.h>
#include "motor.h"
 
ALIGN(RT_ALIGN_SIZE)
static char motor_statck[1024];
static struct rt_thread motor_th;

void motor_th_entry(void *parameter)
{

		
}
void thread_init(void)
{
	rt_err_t res;
    res=rt_thread_init(&motor_th,
                        "motor_th",
                        motor_th_entry,
                        RT_NULL,
                        motor_statck,
                        1024,
                        20,
                        5);
	if(res==RT_EOK)
	{
		rt_kprintf("motor_th init successed..\n");
		res = rt_thread_startup(&motor_th);
        if(res != RT_EOK)
        {
            rt_kprintf("motor_th startup failed..\n");
            return;
        }
         rt_kprintf("motor_th startup successed..\n");
	}
}



