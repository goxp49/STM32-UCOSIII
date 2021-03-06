/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：bsp.c
 * 描述    ：板级初始化
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 	系   统：uCOS-III
 *
 * 作者    ：wildfire team
 * 论坛    ：www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/

#include "includes.h"
#include "os_cfg_app.h"
/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无
 * 输出  ：无
 */
void BSP_Init(void)
{
    OS_CPU_SysTickInit(BSP_CPU_ClkFreq() / (CPU_INT32U)OSCfg_TickRate_Hz);   //调用 SysTick 初始化函数，设置定时器计数值和启动定时器

    LED_GPIO_Config();  /* LED 端口初始化 */
	Key_GPIO_Config();
	//USART1_Config();
	EXTI_Config();
}

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ);//初始化并使能SysTick定时器
	if (SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ))	// ST3.5.0库版本
	{
		/* Capture error */
		while (1);
	}
}

void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*   NVIC INIT */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&NVIC_InitStructure);

	/*   EXTI INIT  */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;

	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

	EXTI_Init(&EXTI_InitStructure);

}




/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;


    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}

/***********时间戳相关函数***************/
//void CPU_TS_TmrInit(void)
//{
//}
//
//uint32_t CPU_TS_TmrRd(void)
//{
//	uint32_t i;
//	return i;
//}

