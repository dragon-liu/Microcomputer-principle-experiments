/*
 * zhongduan.c
 *
 *  Created on: 2019��5��22��
 *      Author: win10
 */
#include "xil_io.h"
#include "stdio.h"

#define INTC_BASEADDR 0x41200000 //INTC�жϿ���������ַ
#define XIN_ISR_OFFSET 0 		//�ж�״̬�Ĵ���ƫ�Ƶ�ַ
#define XIN_IER_OFFSET 8		//�ж�ʹ�ܼĴ���ƫ�Ƶ�ַ
#define XIN_IAR_OFFSET 12		//�ж���Ӧ�Ĵ���ƫ�Ƶ�ַ
#define XIN_MER_OFFSET 28		//���ж�ʹ�ܼĴ���ƫ�Ƶ�ַ
#define LED_BASEADDR 0x40020000
#define XGPIO_DATA_OFFSET 0x8	//ͨ��2���ݼĴ���ƫ�Ƶ�ַ
#define XGPIO_TRI_OFFSET 0xc	//ͨ��2���ƼĴ���ƫ�Ƶ�ַ
#define TIMER_BASEADDR 0X41c00000
#define XTC_TCSR_OFFSET 0		//��ʱ��0����״̬�Ĵ���ƫ�Ƶ�ַ
#define XTC_TLR_OFFSET 4		//��ʱ��0װ�ؼĴ���ƫ�Ƶ�ַ
#define XTC_TCR_OFFSET 8		//��ʱ��0�����Ĵ���ƫ�Ƶ�ַ
#define RESET_VALUE 20000000
void TimerCounterHandler();
void My_ISR() __attribute__((interrupt_handler)); //���жϷ������
u32 LedBits;
int main()
{
	Xil_Out32(LED_BASEADDR+XGPIO_TRI_OFFSET,0x0); //�趨LEDΪ�����ʽ
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x77f);//дTCSR,ֹͣ������
	Xil_Out32(TIMER_BASEADDR+XTC_TLR_OFFSET,RESET_VALUE);//дTLR��Ԥ�ü�����ֵ
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)|0x20);//װ�ؼ�����ֵ
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x7df|0xd2);
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x8);//�жϿ�����ʹ���ж���������INTR_3
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);//ʹ��Ӳ���ж����
	microblaze_enable_interrupts();				//�������������ж�
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);//��ȡISRʶ���ж�Դ
	if((status&0x8)==0x8)
		TimerCounterHandler();					 //�����û��жϴ�����
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);//дIAR����ж�״̬

}
void TimerCounterHandler()
{
	Xil_Out32(LED_BASEADDR+XGPIO_DATA_OFFSET,1<<LedBits); //�������1λLED��
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//�����ʱ���ж�״̬
	LedBits++;
	if(LedBits==16)
		LedBits=0;
}
