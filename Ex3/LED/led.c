/*
 * led.c
 *
 *  Created on: 2019Äê5ÔÂ15ÈÕ
 *      Author: win10
 */
#include "stdio.h"
#include "xil_io.h"
int main()
{
	unsigned short led;
	unsigned char byte;
	Xil_Out16(0x4002000c,0x0);
	while(1)
	{
		xil_printf("input hexadecimal number to be displayed:\r\n");
		led = 0;
		while(1)
		{
			byte = inbyte();
			if(byte == 0x0d)
			{
				break;
			}
			else{
				if(byte >= 'a')
					byte = byte - 0x57;
				else if(byte >= 'A')
					byte = byte - 0x37;
				else
					byte = byte - 0x30;
				led = (led << 4) + byte;
			}
		}
		Xil_Out16(0x40020008, led);
	}
}
