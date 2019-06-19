/*
 * da.c
 *
 *  Created on: 2019Äê5ÔÂ29ÈÕ
 *      Author: win10
 */
# include "xil_io.h"
# define INTC_BASEADDR 0x41200000
# define XIN_ISR_OFFSET 0x0
# define XIN_IER_OFFSET 0x8
# define XIN_IAR_OFFSET 0xc
# define XIN_MER_OFFSET 0x1c
# define XSP_BASEADDR 0x44a00000
# define XSP_DGIER_OFFSET 0x1c
# define XSP_IISR_OFFSET 0x20
# define XSP_IIER_OFFSET 0x28
# define XSP_CR_OFFSET 0x60
# define XSP_DTR_OFFSET 0x68
# define XSP_SSR_OFFSET 0x70
void My_ISR()__attribute__((interrupt_handler));
short int volt=0;
int main ()
{

	Xil_Out32(XSP_BASEADDR+XSP_CR_OFFSET,0x16);
	Xil_Out32(XSP_BASEADDR+XSP_SSR_OFFSET,0x0);
	Xil_Out32(XSP_BASEADDR+XSP_IIER_OFFSET,0x4);
	Xil_Out32(XSP_BASEADDR+XSP_DGIER_OFFSET,0x80000000);
	Xil_Out32(INTC_BASEADDR+XIN_IER_OFFSET,0x1);
	Xil_Out32(INTC_BASEADDR+XIN_MER_OFFSET,0x3);
	microblaze_enable_interrupts();
	Xil_Out16(XSP_BASEADDR+XSP_DTR_OFFSET,volt);
}
void My_ISR()
{
	Xil_Out32(XSP_BASEADDR+XSP_IISR_OFFSET,Xil_In32(XSP_BASEADDR+XSP_IISR_OFFSET));
	Xil_Out32(INTC_BASEADDR+XIN_IAR_OFFSET,Xil_In32(INTC_BASEADDR+XIN_ISR_OFFSET));
	volt=volt+0xb;
	Xil_Out16(XSP_BASEADDR+XSP_DTR_OFFSET,volt&0xfff);

}
