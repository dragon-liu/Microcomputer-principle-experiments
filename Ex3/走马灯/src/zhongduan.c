/*
 * zhongduan.c
 *
 *  Created on: 2019年5月22日
 *      Author: win10
 */
#include "xil_io.h"
#include "stdio.h"

#define INTC_BASEADDR 0x41200000 //INTC中断控制器基地址
#define XIN_ISR_OFFSET 0 		//中断状态寄存器偏移地址
#define XIN_IER_OFFSET 8		//中断使能寄存器偏移地址
#define XIN_IAR_OFFSET 12		//中断响应寄存器偏移地址
#define XIN_MER_OFFSET 28		//主中断使能寄存器偏移地址
#define LED_BASEADDR 0x40020000
#define XGPIO_DATA_OFFSET 0x8	//通道2数据寄存器偏移地址
#define XGPIO_TRI_OFFSET 0xc	//通道2控制寄存器偏移地址
#define TIMER_BASEADDR 0X41c00000
#define XTC_TCSR_OFFSET 0		//定时器0控制状态寄存器偏移地址
#define XTC_TLR_OFFSET 4		//定时器0装载寄存器偏移地址
#define XTC_TCR_OFFSET 8		//定时器0计数寄存器偏移地址
#define RESET_VALUE 20000000
void TimerCounterHandler();
void My_ISR() __attribute__((interrupt_handler)); //总中断服务程序
u32 LedBits;
int main()
{
	Xil_Out32(LED_BASEADDR+XGPIO_TRI_OFFSET,0x0); //设定LED为输出方式
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x77f);//写TCSR,停止计数器
	Xil_Out32(TIMER_BASEADDR+XTC_TLR_OFFSET,RESET_VALUE);//写TLR，预置计数初值
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)|0x20);//装载计数初值
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET)&0x7df|0xd2);
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x8);//中断控制器使能中断输入引脚INTR_3
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);//使能硬件中断输出
	microblaze_enable_interrupts();				//允许处理器接收中断
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);//读取ISR识别中断源
	if((status&0x8)==0x8)
		TimerCounterHandler();					 //调用用户中断处理函数
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);//写IAR清除中断状态

}
void TimerCounterHandler()
{
	Xil_Out32(LED_BASEADDR+XGPIO_DATA_OFFSET,1<<LedBits); //输出点亮1位LED灯
	Xil_Out32(TIMER_BASEADDR+XTC_TCSR_OFFSET,Xil_In32(TIMER_BASEADDR+XTC_TCSR_OFFSET));//清除定时器中断状态
	LedBits++;
	if(LedBits==16)
		LedBits=0;
}
