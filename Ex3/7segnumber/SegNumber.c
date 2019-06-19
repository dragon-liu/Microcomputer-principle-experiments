/*
 * SegNumber.c
 *
 *  Created on: 2019Äê5ÔÂ15ÈÕ
 *      Author: win10
 */
#include "stdio.h"
#include "xil_io.h"
int main()
{
	char segcode[8] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8};
	short pos = 0xff7f;
	int i,j;
	Xil_Out8(0x40020004, 0x0);
	Xil_Out8(0x4002000c, 0x0);
	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			Xil_Out8(0x40020000, segcode[i]);
			Xil_Out8(0x40020008, pos);
			for(j = 0; j < 10000; j++);
			pos = pos >> 1;
		}
		pos = 0xff7f;
	}
	return 0;
}
