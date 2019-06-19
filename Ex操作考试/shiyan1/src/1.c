/*
 * 1.c
 *
 *  Created on: 2019年6月18日
 *      Author: win10
 */
#include"xil_io.h"
#include<stdio.h>
#include "xparameters.h"
#define XPAR_GPIO_2_BASEADDR 0x40020000
int main()
{
	char segcode[17] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0xbf};
	int sw;
	int i, j;
	short pos = 0xff7f;//位选初始值，数码管从左往右第一位
	char set = 0xbf;
	unsigned int index;
	int temp;
	Xil_Out8(XPAR_GPIO_2_BASEADDR+0x4,0xff); //设置开关输入
	Xil_Out8(0x40010000+0x4,0x0);//设置段码输出
	Xil_Out8(0x40010000+0xc,0x0);//设置位码输出
	while(1)
	{
		sw = Xil_In8(XPAR_GPIO_2_BASEADDR);//读取开关的输入
		if((sw>0x2f)&&(sw<0x3a))
			index = sw - 0x30;
		else if ((sw>0x40)&&(sw<0x47))
			index = sw - 0x37;
		else if ((sw>0x60)&&(sw<0x67))
			index = sw - 0x57;
		else index=16;

		for(i=0;i<8;i++)
		{
			Xil_Out8(0x40010000, set);//输出段码
			Xil_Out8(0x40010008, pos);//输出位码
			for(j = 0; j < 10000; j++);//延时
			pos = pos >> 1;			   //指向下一位
		}

		pos = 0xff7f;
		Xil_Out8(0x40010000, segcode[index]);
		Xil_Out8(0x40010008, pos);
		for(temp=0;temp<0x1000;temp++);
	}
}
