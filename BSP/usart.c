/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��usart.c
 * ����    ������Ӧ�ú�����

 * ��汾  ��ST3.5.0
 *
 * ����    ��goxp49
**********************************************************************************/
#include <usart.h>


void USART1_Config(void)
{
	GPIO_InitTypeDef gpio_initSturcture;
	USART_InitTypeDef usart_initSturcture;

	/* ʹ��ʱ��,USART1������PA8 ~ PA12 ,TX ->9, RX->10*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE);

	/* ����TX�趨 */
	gpio_initSturcture.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initSturcture.GPIO_Pin = GPIO_Pin_9;
	gpio_initSturcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_initSturcture);

	/* ����RX�趨 */
	gpio_initSturcture.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_initSturcture.GPIO_Pin = GPIO_Pin_10;
	//gpio_initSturcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_initSturcture);

	/* USART1�趨 */
	usart_initSturcture.USART_BaudRate = 115200;
	usart_initSturcture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_initSturcture.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_initSturcture.USART_Parity = USART_Parity_No;
	usart_initSturcture.USART_StopBits = USART_StopBits_1;
	usart_initSturcture.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_initSturcture);

	/* ʹ��USART */
	USART_Cmd(USART1, ENABLE);

}


void USART_SendMessage(uint16_t DataToSend)
{
	USART_SendData(USART1,DataToSend);
	/* ����Ƿ������ */
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
