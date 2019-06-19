/*
 * Console_patch16.c
 *
 *  Created on: 2019Äê5ÔÂ15ÈÕ
 *      Author: win10
 */
#include "stdio.h"
#include "xil_io.h"
int main()
{
	char button;
	Xil_Out8(0x40000004,0x1f);
	while(1)
	while((Xil_In8(0x40010000)&0x1f)!=0)
	{
		button = Xil_In8(0x40010000)&0x1f;
		while((Xil_In8(0x40010000)&0x1f)!=0);
		xil_printf("The pushed button's code is 0x%x\n", button);
	}
}
