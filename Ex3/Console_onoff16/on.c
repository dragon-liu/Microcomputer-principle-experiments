/*
 * on.c
 *
 *  Created on: 2019Äê5ÔÂ15ÈÕ
 *      Author: win10
 */
#include "stdio.h"
#include "xil_io.h"
int main()
{
	unsigned short last_sw,current_sw;
	Xil_Out16(0x40000004,0xffff);
	while(1)
	{
		last_sw = current_sw;
		current_sw = Xil_In16(0x40000000)&0xffff;
		if(last_sw!=current_sw)
		xil_printf("The switches' code is 0x%4x\n", current_sw);
	}
}
