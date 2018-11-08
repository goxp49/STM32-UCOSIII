/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��app.c
 * ����    ��LED������
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 ϵ   ͳ   ��uCOS-III
 *
 * ����    ��wildfire team
 * ��̳    ��www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/

#include "includes.h"

static OS_TCB SEM_KEY_TCB;
static CPU_STK SEM_KEY_Stk[128];

static OS_TCB SEM_LED_TCB;
static CPU_STK SEM_LED_Stk[128];


OS_SEM SemOfKey;          //��־KEY1�Ƿ񱻵����Ķ�ֵ�ź���

int main(void)
{

	OS_ERR err;
	BSP_Init();			//�弶��ʼ��
	CPU_Init();			//CPU��ʼ��
	OSInit(&err);		//ϵͳ��ʼ��
	Mem_Init();

	/*��������*/

	 OSTaskCreate((OS_TCB *)&SEM_KEY_TCB,	   //������ƿ�ָ��
					  (CPU_CHAR   *)"KEY", 	  //��������
					  (OS_TASK_PTR )Task_SEM_KEY_SCAN,	  //�������ָ��
					  (void 	  *)0,			  //���ݸ�����Ĳ���parg
					  (OS_PRIO	   )3,			  //�������ȼ�
					  (CPU_STK	  *)&SEM_KEY_Stk[0],	  //�����ջ����ַ
					  (CPU_STK_SIZE)12, 		  //��ջʣ�ྯ����
					  (CPU_STK_SIZE)128,		  //��ջ��С
					  (OS_MSG_QTY  )0,			  //�ɽ��յ������Ϣ������
					  (OS_TICK	   )0,			  //ʱ��Ƭ��תʱ��
					  (void 	  *)0,			  //������ƿ���չ��Ϣ
					  (OS_OPT	   )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //����ѡ��
					  (OS_ERR	  *)&err);		  //����ֵ
					  
	OSTaskCreate((OS_TCB *)&SEM_LED_TCB,	  //������ƿ�ָ��
						 (CPU_CHAR	 *)"LED",		 //��������
						 (OS_TASK_PTR )Task_SEM_LED,	 //�������ָ��
						 (void		 *)0,			 //���ݸ�����Ĳ���parg
						 (OS_PRIO	  )2,			 //�������ȼ�
						 (CPU_STK	 *)&SEM_LED_Stk[0], 	 //�����ջ����ַ
						 (CPU_STK_SIZE)12,			 //��ջʣ�ྯ����
						 (CPU_STK_SIZE)128, 		 //��ջ��С
						 (OS_MSG_QTY  )0,			 //�ɽ��յ������Ϣ������
						 (OS_TICK	  )0,			 //ʱ��Ƭ��תʱ��
						 (void		 *)0,			 //������ƿ���չ��Ϣ
						 (OS_OPT	  )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //����ѡ��
						 (OS_ERR	 *)&err);		 //����ֵ

    OSStart(&err);


}


void Task_SEM_KEY_SCAN(void *p_arg)
{
	OS_ERR err;

    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	OSSemCreate((OS_SEM *) &SemOfKey,
		(CPU_CHAR *) "key_scan",
		(OS_SEM_CTR) 0,
		(OS_ERR *) &err);

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


//-------------------------------------------------------------------------------------------------------

void Task_LED1(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

    while (1)
    {
        LED1_Switch();
        OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void Task_LED2(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

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

    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	OSTmrCreate((OS_TMR *) &tmr,
		(CPU_CHAR *) "TIMER",
		(OS_TICK) 5,
		(OS_TICK) 5,
		(OS_OPT) OS_OPT_TMR_PERIODIC,
		(OS_TMR_CALLBACK_PTR) TmrCallBack,
		(void *) "OVER",
		(OS_ERR *) err);

	//������ʱ��
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

