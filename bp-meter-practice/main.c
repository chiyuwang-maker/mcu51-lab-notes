/*
 * 血压计练习稿（自写逻辑整理）
 * - 读 AIN3 外部输入，粗换算后显示在数码管前 4 位
 * - 后几位固定显示段码示意（原练习里的 H / P 等）
 * - K1 切换 LED1 与电机
 * 仅用 reg52.h，XPT2046 读写内联在本文件
 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit AD_DIN  = P3^4;
sbit AD_CS   = P3^5;
sbit AD_DCLK = P3^6;
sbit AD_DOUT = P3^7;

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

sbit K1   = P3^1;
sbit LED1 = P2^0;
sbit MOTO = P1^0;
sbit BEEP = P1^5;

u8 disp[8];
u8 code SEG[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};

void delay(u16 i)
{
	while (i--)
		;
}

u16 read_ad(u8 cmd)
{
	u8 i;
	u16 val = 0;

	AD_DCLK = 0;
	AD_CS = 0;
	for (i = 0; i < 8; i++)
	{
		AD_DIN = (cmd & 0x80) ? 1 : 0;
		cmd <<= 1;
		AD_DCLK = 1;
		AD_DCLK = 0;
	}
	for (i = 0; i < 12; i++)
	{
		AD_DCLK = 1;
		AD_DCLK = 0;
		val <<= 1;
		if (AD_DOUT)
			val |= 1;
	}
	AD_CS = 1;
	return val;
}

void key_process(void)
{
	if (K1 == 0)
	{
		delay(1000);           /* 消抖 */
		if (K1 == 0)
		{
			LED1 = ~LED1;
			MOTO = ~MOTO;
		}
		while (!K1)
			;                  /* 松手再继续 */
	}
}

/* 采样并换算到显示值；公式保留原练习里的粗映射 */
void update_disp(void)
{
	static u8 skip;
	static u16 ad;
	u16 shown;
	u16 place;
	u8 i;

	if (++skip >= 50)
	{
		skip = 0;
		ad = read_ad(0xE4);    /* AIN3 */
	}

	/* 原练习：n = 96 + (4096 - temp) / 70 */
	shown = 96 + (4096 - ad) / 70;

	place = 1000;
	for (i = 0; i < 4; i++)
	{
		disp[i] = SEG[(shown / place) % 10];
		place /= 10;
	}
	disp[4] = 0x76;   /* 示意 'H' */
	disp[5] = 0x73;   /* 示意 'P' */
	disp[6] = 0xDC;   /* 原练习固定段码 */
	disp[7] = 0x00;
}

void scan_display(void)
{
	u8 i;
	for (i = 0; i < 7; i++)
	{
		switch (i)
		{
		case 0: LSA = 1; LSB = 1; LSC = 1; break;
		case 1: LSA = 0; LSB = 1; LSC = 1; break;
		case 2: LSA = 1; LSB = 0; LSC = 1; break;
		case 3: LSA = 0; LSB = 0; LSC = 1; break;
		case 4: LSA = 1; LSB = 1; LSC = 0; break;
		case 5: LSA = 0; LSB = 1; LSC = 0; break;
		case 6: LSA = 1; LSB = 0; LSC = 0; break;
		}
		P0 = disp[i];
		delay(100);
		P0 = 0x00;
	}
}

void main(void)
{
	LED1 = 1;
	MOTO = 0;
	BEEP = 0;

	while (1)
	{
		key_process();
		update_disp();
		scan_display();
	}
}
