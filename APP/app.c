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

/*
 * ��������Task_LED
 * ����  : LED��ˮ��
 * ����  ����
 * ���  : ��
 */

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

