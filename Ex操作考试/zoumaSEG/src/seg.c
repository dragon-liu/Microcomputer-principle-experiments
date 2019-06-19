/*
 * seg.c
 *
 *  Created on: 2019年6月19日
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
#define Switch_SEG_BASEADDR 0x40020000
#define XGPIO_DATA1_OFFSET 0x0//通道1数据
#define XGPIO_TRI1_OFFSET 0x4//通道1控制
#define XGPIO_DADA2_OFFSET 0x8//通道2数据
#define XGPIO_TRI2_OFFSET 0xc//通道2控制
#define TIMER_BASEADDR 0x41c00000
#define XTC_TCSR_OFFSET 0x10 //定时器1控制
#define XTC_TLR_OFFSET 0x14 //定时器1装载
#define RESET_VALUE 50000000 //0.5s
void TimerCounterHandle();
void My_ISR() __attribute__((interrupt_handler));

unsigned short pos[4]={0xff7f,0x7fbf,0x3fdf,0x1fef};
char segcode1[4]={0xc0,0xf9,0xa4,0xb0};
char segcode2[4]={0x99,0x92,0x82,0xf8};
unsigned short index1;
char sw,last;
int i;

int main()
{
	Xil_Out32(Switch_SEG_BASEADDR+XGPIO_TRI1_OFFSET,0xffff);//设定Switch为输入方式
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
	sw=Xil_In8(Switch_SEG_BASEADDR);
		if(sw==0x0)
		{
			Xil_Out8(SEG_BASEADDR, segcode1[i]);//输出段码
			Xil_Out8(SEG_BASEADDR+XGPIO_DADA2_OFFSET, pos[i]);//输出位码
			i++;
			if(i==4)
			{
				i=0;
			}
			Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//清除GPIO中断

		}
		else if(sw==0x1)
		{
			Xil_Out8(SEG_BASEADDR, segcode2[i]);//输出段码
			Xil_Out8(SEG_BASEADDR+XGPIO_DADA2_OFFSET, pos[i]);//输出位码
			i++;
			if(i==4)
			{
				i=0;
			}
			Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//清除GPIO中断
		}
}
