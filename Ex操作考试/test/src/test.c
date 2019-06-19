/*
 * test.c
 *
 *  Created on: 2019��6��18��
 *      Author: win10
 */

#include "xil_io.h"
#include "stdio.h"
#include "xparameters.h"
#define INTC_BASEADDR 0x41200000
#define XIN_ISR_OFFSET 0
#define XIN_IER_OFFSET 8
#define XIN_IAR_OFFSET 12
#define XIN_MER_OFFSET 28
#define SEG_BASEADDR 0X40010000
#define Button_BASEADDR 0x40000000
#define XGPIO_DATA1_OFFSET 0x0//ͨ��1����
#define XGPIO_TRI1_OFFSET 0x4//ͨ��1����
#define XGPIO_DADA2_OFFSET 0x8//ͨ��2����
#define XGPIO_TRI2_OFFSET 0xc//ͨ��2����
#define TIMER_BASEADDR 0x41c00000
#define XTC_TCSR_OFFSET 0x10 //��ʱ��1����
#define XTC_TLR_OFFSET 0x14 //��ʱ��1װ��
#define RESET_VALUE 50000000
void TimerCounterHandle();
void My_ISR() __attribute__((interrupt_handler));

unsigned short pos=0xfe;
char segcode1[4]={0xf9,0xb0,0x92,0xf8};
char segcode2[4]={0xa4,0x99,0x82,0x80};
char* segcode=segcode1;
unsigned int index1=0;
int button,flag;

int main()
{
	Xil_Out32(Button_BASEADDR+XGPIO_TRI1_OFFSET,0x1);//�趨ButtonΪ���뷽ʽ
	Xil_Out32(SEG_BASEADDR+XGPIO_TRI1_OFFSET,0x0); //����
	Xil_Out32(SEG_BASEADDR+XGPIO_TRI2_OFFSET,0x0);	//λ��
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x77f);//дTCSR��ֹͣ������
	Xil_Out32(TIMER_BASEADDR+XTC_TLR_OFFSET,RESET_VALUE);//дTLR,Ԥ�ü�����ֵ
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)|0x20);//װ�ؼ�����ֵ
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x7df|0xd2);
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x8);			//���жϿ����������ж�Դʹ��
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);
	microblaze_enable_interrupts();							//�������������ж�
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);			//��ȡISR
	if((status&0x8)==0x8)
		TimerCounterHandle();								//�����û��жϷ������
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);			//дIAR
}
void TimerCounterHandle()
{
	button=Xil_In8(Button_BASEADDR)&0x1;
	if(button!=0)
	{
		if(segcode==segcode1)
			segcode=segcode2;
		else if(segcode==segcode2)
			segcode=segcode1;
	}
	if(index1>=4)
		index1=0;
	Xil_Out8(SEG_BASEADDR+XGPIO_DADA2_OFFSET,pos);
	Xil_Out8(SEG_BASEADDR,segcode[index1]);
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//���GPIO�ж�
	index1++;
}
