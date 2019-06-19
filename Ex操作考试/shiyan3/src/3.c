/*
 * 3.c
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
#define Switch_LED_BASEADDR 0x40020000
#define XGPIO_DATA1_OFFSET 0x0
#define XGPIO_TRI1_OFFSET 0x4
#define XGPIO_DATA2_OFFSET 0X8
#define XGPIO_TRI2_OFFSET 0xC
#define XGPIO_IER_OFFSET 0x128
#define XGPIO_ISR_OFFSET 0x120
#define XGPIO_GIE_OFFSET 0X11c
void SwitchHandler();
void My_ISR() __attribute__((interrupt_handler));
int main()
{
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_TRI2_OFFSET,0x0);	//设定LED为中断输出方式
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_TRI1_OFFSET,0xffff);//设定Switch为输入方式
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_IER_OFFSET,0x1);	//通道1允许中断
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_GIE_OFFSET,0x80000000);//允许GPIO中断输出
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x4);			//中断控制器使能中断源INTR0
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);
	microblaze_enable_interrupts();							//允许处理器处理中断
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);			//读取ISR
	if((status&0x4)==0x4)
		SwitchHandler();									//调用用户中断服务程序
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);			//写IAR
}
void SwitchHandler() //求补码，通过开关输入原码
{
	u16 code;
	code=Xil_In16(Switch_LED_BASEADDR+XGPIO_DATA1_OFFSET);
	if(code<32768)
		Xil_Out16(Switch_LED_BASEADDR+XGPIO_DATA2_OFFSET,code);
	else
		Xil_Out16(Switch_LED_BASEADDR+XGPIO_DATA2_OFFSET,(~code)+32769);
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_ISR_OFFSET,
			Xil_In32(Switch_LED_BASEADDR+XGPIO_ISR_OFFSET));//清除GPIO中断
}
