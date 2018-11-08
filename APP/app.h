#ifndef	_APP_H_
#define	_APP_H_


/**************** 用户任务声明 *******************/
void Task_LED1(void *p_arg);
void Task_LED2(void *p_arg);
void Task_TIMER(void *p_arg);
void TmrCallBack(OS_TMR *p_tmr, void *p_arg);

#endif	//_APP_H_
