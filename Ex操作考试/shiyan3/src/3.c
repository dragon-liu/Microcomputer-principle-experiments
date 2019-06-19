/*
 * 3.c
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
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_TRI2_OFFSET,0x0);	//�趨LEDΪ�ж������ʽ
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_TRI1_OFFSET,0xffff);//�趨SwitchΪ���뷽ʽ
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_IER_OFFSET,0x1);	//ͨ��1�����ж�
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_GIE_OFFSET,0x80000000);//����GPIO�ж����
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x4);			//�жϿ�����ʹ���ж�ԴINTR0
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);
	microblaze_enable_interrupts();							//�������������ж�
	return 0;
}
void My_ISR()
{
	int status;
	status=Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET);			//��ȡISR
	if((status&0x4)==0x4)
		SwitchHandler();									//�����û��жϷ������
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,status);			//дIAR
}
void SwitchHandler() //���룬ͨ����������ԭ��
{
	u16 code;
	code=Xil_In16(Switch_LED_BASEADDR+XGPIO_DATA1_OFFSET);
	if(code<32768)
		Xil_Out16(Switch_LED_BASEADDR+XGPIO_DATA2_OFFSET,code);
	else
		Xil_Out16(Switch_LED_BASEADDR+XGPIO_DATA2_OFFSET,(~code)+32769);
	Xil_Out32(Switch_LED_BASEADDR+XGPIO_ISR_OFFSET,
			Xil_In32(Switch_LED_BASEADDR+XGPIO_ISR_OFFSET));//���GPIO�ж�
}
