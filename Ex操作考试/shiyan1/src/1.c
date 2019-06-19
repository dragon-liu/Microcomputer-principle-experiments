/*
 * 1.c
 *
 *  Created on: 2019��6��18��
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
	short pos = 0xff7f;//λѡ��ʼֵ������ܴ������ҵ�һλ
	char set = 0xbf;
	unsigned int index;
	int temp;
	Xil_Out8(XPAR_GPIO_2_BASEADDR+0x4,0xff); //���ÿ�������
	Xil_Out8(0x40010000+0x4,0x0);//���ö������
	Xil_Out8(0x40010000+0xc,0x0);//����λ�����
	while(1)
	{
		sw = Xil_In8(XPAR_GPIO_2_BASEADDR);//��ȡ���ص�����
		if((sw>0x2f)&&(sw<0x3a))
			index = sw - 0x30;
		else if ((sw>0x40)&&(sw<0x47))
			index = sw - 0x37;
		else if ((sw>0x60)&&(sw<0x67))
			index = sw - 0x57;
		else index=16;

		for(i=0;i<8;i++)
		{
			Xil_Out8(0x40010000, set);//�������
			Xil_Out8(0x40010008, pos);//���λ��
			for(j = 0; j < 10000; j++);//��ʱ
			pos = pos >> 1;			   //ָ����һλ
		}

		pos = 0xff7f;
		Xil_Out8(0x40010000, segcode[index]);
		Xil_Out8(0x40010008, pos);
		for(temp=0;temp<0x1000;temp++);
	}
}
