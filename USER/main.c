/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��uCOS-III������LED��ˮ�ơ�
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 * ϵ   ͳ ��uCOS-III
 * ����    ��wildfire team
 * ��̳    ��www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"



//static  OS_TCB	LED_TCB;		   //����������ƿ�
//static	CPU_STK	LED_Stk[128];	   //���������ջ

static OS_TCB	TIMER_TCB;
static CPU_STK	TIMER_Stk[128];


/*
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{

	OS_ERR err;
	BSP_Init();			//�弶��ʼ��
	CPU_Init();			//CPU��ʼ��
	OSInit(&err);		//ϵͳ��ʼ��
	Mem_Init();

	/*��������*/

	 OSTaskCreate((OS_TCB	  *)&TIMER_TCB,	   //������ƿ�ָ��
					  (CPU_CHAR   *)"LED2", 	  //��������
					  (OS_TASK_PTR )Task_TIMER,	  //�������ָ��
					  (void 	  *)0,			  //���ݸ�����Ĳ���parg
					  (OS_PRIO	   )3,			  //�������ȼ�
					  (CPU_STK	  *)&TIMER_Stk[0],	  //�����ջ����ַ
					  (CPU_STK_SIZE)12, 		  //��ջʣ�ྯ����
					  (CPU_STK_SIZE)128,		  //��ջ��С
					  (OS_MSG_QTY  )0,			  //�ɽ��յ������Ϣ������
					  (OS_TICK	   )0,			  //ʱ��Ƭ��תʱ��
					  (void 	  *)0,			  //������ƿ���չ��Ϣ
					  (OS_OPT	   )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),  //����ѡ��
					  (OS_ERR	  *)&err);		  //����ֵ

    OSStart(&err);


}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
