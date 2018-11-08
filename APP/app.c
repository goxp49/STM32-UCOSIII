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

OS_SEM SemOfKey;          //标志KEY1是否被单击的多值信号量

int main(void)
{

	OS_ERR err;
	BSP_Init();			//板级初始化
	CPU_Init();			//CPU初始化
	OSInit(&err);		//系统初始化
	Mem_Init();

	/*创建任务*/

	 OSTaskCreate((OS_TCB	  *)&TIMER_TCB,	   //任务控制块指针
					  (CPU_CHAR   *)"LED2", 	  //任务名称
					  (OS_TASK_PTR )Task_TIMER,	  //任务代码指针
					  (void 	  *)0,			  //传递给任务的参数parg
					  (OS_PRIO	   )3,			  //任务优先级
					  (CPU_STK	  *)&TIMER_Stk[0],	  //任务堆栈基地址
					  (CPU_STK_SIZE)12, 		  //堆栈剩余警戒线
					  (CPU_STK_SIZE)128,		  //堆栈大小
					  (OS_MSG_QTY  )0,			  //可接收的最大消息队列数
					  (OS_TICK	   )0,			  //时间片轮转时间
					  (void 	  *)0,			  //任务控制块扩展信息
					  (OS_OPT	   )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //任务选项
					  (OS_ERR	  *)&err);		  //返回值

    OSStart(&err);


}

/*
 * 函数名：Task_LED
 * 描述  : LED流水灯
 * 输入  ：无
 * 输出  : 无
 */

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

void Task_KEY_SCAN(void *p_arg)
{
	OS_ERR err;
	OS_TMR tmr;
	uint8_t keyStatus;

    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	OSSemCreate((OS_SEM *) &SemOfKey,
		(CPU_CHAR *) "key_scan",
		(OS_SEM_CTR) 0,
		(OS_ERR *) &err);

	while(Key_Scan() == KEY_OFF)
	{

	};

}

