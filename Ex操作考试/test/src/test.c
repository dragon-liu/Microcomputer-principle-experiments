/*
 * test.c
 *
 *  Created on: 2019年6月18日
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
#define XGPIO_DATA1_OFFSET 0x0//通道1数据
#define XGPIO_TRI1_OFFSET 0x4//通道1控制
#define XGPIO_DADA2_OFFSET 0x8//通道2数据
#define XGPIO_TRI2_OFFSET 0xc//通道2控制
#define TIMER_BASEADDR 0x41c00000
#define XTC_TCSR_OFFSET 0x10 //定时器1控制
#define XTC_TLR_OFFSET 0x14 //定时器1装载
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
	Xil_Out32(Button_BASEADDR+XGPIO_TRI1_OFFSET,0x1);//设定Button为输入方式
	Xil_Out32(SEG_BASEADDR+XGPIO_TRI1_OFFSET,0x0); //段码
	Xil_Out32(SEG_BASEADDR+XGPIO_TRI2_OFFSET,0x0);	//位码
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x77f);//写TCSR，停止计数器
	Xil_Out32(TIMER_BASEADDR+XTC_TLR_OFFSET,RESET_VALUE);//写TLR,预置计数初值
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)|0x20);//装载计数初值
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x7df|0xd2);
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x8);			//对中断控制器进行中断源使能
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);
	microblaze_enable_interrupts();							//允许处理器处理中断
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);			//读取ISR
	if((status&0x8)==0x8)
		TimerCounterHandle();								//调用用户中断服务程序
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);			//写IAR
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
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//清除GPIO中断
	index1++;
}
