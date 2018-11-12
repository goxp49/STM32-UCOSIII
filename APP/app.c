/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：app.c
 * 描述    ：LED单任务
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 系   统   ：uCOS-III
 *
 * 作者    ：wildfire team
 * 论坛    ：www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/

#include "includes.h"

static OS_Q * p_q;

static OS_TCB Q_POST_TCB;
static CPU_STK Q_POST_Stk[128];

static OS_TCB Q_PEND_TCB;
static CPU_STK Q_PEND_Stk[128];

static OS_SEM SemOfKey;          //标志KEY1是否被单击的多值信号量

int main(void)
{

	OS_ERR err;
	BSP_Init();			//板级初始化
	CPU_Init();			//CPU初始化
	OSInit(&err);		//系统初始化
	Mem_Init();

	OSQCreate((OS_Q *) p_q,
		(CPU_CHAR *) "queue",
		(OS_MSG_QTY) 20,
		(OS_ERR *) &err)

	/*创建任务*/

	 OSTaskCreate((OS_TCB *)&Q_POST_TCB,	   //任务控制块指针
					  (CPU_CHAR   *)"KEY", 	  //任务名称
					  (OS_TASK_PTR )Task_QUEUE_POST,	  //任务代码指针
					  (void 	  *)0,			  //传递给任务的参数parg
					  (OS_PRIO	   )3,			  //任务优先级
					  (CPU_STK	  *)&Q_POST_Stk[0],	  //任务堆栈基地址
					  (CPU_STK_SIZE)12, 		  //堆栈剩余警戒线
					  (CPU_STK_SIZE)128,		  //堆栈大小
					  (OS_MSG_QTY  )5,			  //可接收的最大消息队列数
					  (OS_TICK	   )0,			  //时间片轮转时间
					  (void 	  *)0,			  //任务控制块扩展信息
					  (OS_OPT	   )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //任务选项
					  (OS_ERR	  *)&err);		  //返回值

	OSTaskCreate((OS_TCB *)&Q_PEND_TCB,	  //任务控制块指针
						 (CPU_CHAR	 *)"LED",		 //任务名称
						 (OS_TASK_PTR )Task_SEM_LED,	 //任务代码指针
						 (void		 *)0,			 //传递给任务的参数parg
						 (OS_PRIO	  )2,			 //任务优先级
						 (CPU_STK	 *)&Q_PEND_Stk[0], 	 //任务堆栈基地址
						 (CPU_STK_SIZE)12,			 //堆栈剩余警戒线
						 (CPU_STK_SIZE)128, 		 //堆栈大小
						 (OS_MSG_QTY  )5,			 //可接收的最大消息队列数
						 (OS_TICK	  )0,			 //时间片轮转时间
						 (void		 *)0,			 //任务控制块扩展信息
						 (OS_OPT	  )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //任务选项
						 (OS_ERR	 *)&err);		 //返回值

    OSStart(&err);


}


void Task_QUEUE_POST(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告


	while(1)
	{
		OSQPost((OS_Q *) p_q,
			(void *) "Hellow",
			(OS_MSG_SIZE) sizeof("Hellow"),
			(OS_OPT)  OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
			(OS_ERR) * err)

		OSTimeDlyHMSM( 0, 0, 0, 500, OS_OPT_TIME_PERIODIC, &err);
	};

}

void Task_QUEUE_PEND(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告


	while(1)
	{
		os
	};

}


#if(0)

void Task_SEM_KEY_SCAN(void *p_arg)
{
	OS_ERR err;

    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	while(1)
	{
		if(Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON)
		{
			OSSemPost(&SemOfKey, OS_OPT_POST_ALL, &err);
		}

	};

}

void Task_SEM_LED(void *p_arg)
{
	OS_ERR err;

    (void)p_arg;

	while(1)
	{
		OSSemPend(&SemOfKey, 0, OS_OPT_PEND_BLOCKING, (CPU_TS*)0, &err);
		LED1_Switch();
	};

}

#endif
//-------------------------------------------------------------------------------------------------------

void Task_LED1(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

    while (1)
    {
        LED1_Switch();
        OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void Task_LED2(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

    while (1)
    {
        LED2( ON );
        OSTimeDlyHMSM(0, 0, 0, 200,OS_OPT_TIME_HMSM_STRICT,&err);
        LED2( OFF);
		OSTimeDlyHMSM(0, 0, 0, 200,OS_OPT_TIME_HMSM_STRICT,&err);

    }
}
//-------------------------------------------------------------------------------------------------------
void Task_TIMER(void *p_arg)
{
	OS_ERR err;
	OS_TMR tmr;

    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	OSTmrCreate((OS_TMR *) &tmr,
		(CPU_CHAR *) "TIMER",
		(OS_TICK) 5,
		(OS_TICK) 5,
		(OS_OPT) OS_OPT_TMR_PERIODIC,
		(OS_TMR_CALLBACK_PTR) TmrCallBack,
		(void *) "OVER",
		(OS_ERR *) err);

	//启动定时器
	OSTmrStart((OS_TMR *) &tmr, (OS_ERR *) err);


    while (1)
    {
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC | OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void TmrCallBack(OS_TMR *p_tmr, void *p_arg)
{
	//CPU_SR_ALLOC();

	LED1_Switch();

}
//-------------------------------------------------------------------------------------------------------

