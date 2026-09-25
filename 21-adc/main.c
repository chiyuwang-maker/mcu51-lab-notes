/* 电位器 AD：位带 SPI 读 XPT2046 AIN0，前 4 位数码管显示 0～4095 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

/* XPT2046 软件 SPI */
sbit AD_DIN  = P3^4;
sbit AD_CS   = P3^5;
sbit AD_DCLK = P3^6;
sbit AD_DOUT = P3^7;

/* 数码管位选 */
sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 disp[4];
u8 code SEG[10] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};

void delay(u16 i)
{
	while (i--)
		;
}

/* 读一次 12 位 AD；cmd 例：0x94=AIN0，0xD4=AIN1，0xA4=AIN2，0xE4=AIN3 */
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

void update_disp(void)
{
	static u8 skip;
	static u16 ad;
	u16 n;

	if (++skip >= 50)   /* 不必每次扫描都采样 */
	{
		skip = 0;
		ad = read_ad(0x94);   /* AIN0 电位器 */
	}
	n = ad;
	disp[0] = SEG[n / 1000];
	disp[1] = SEG[n % 1000 / 100];
	disp[2] = SEG[n % 100 / 10];
	disp[3] = SEG[n % 10];
}

void scan_display(void)
{
	u8 i;
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0: LSA = 1; LSB = 1; LSC = 1; break;
		case 1: LSA = 0; LSB = 1; LSC = 1; break;
		case 2: LSA = 1; LSB = 0; LSC = 1; break;
		case 3: LSA = 0; LSB = 0; LSC = 1; break;
		}
		P0 = disp[i];
		delay(100);
		P0 = 0x00;
	}
}

void main(void)
{
	while (1)
	{
		update_disp();
		scan_display();
	}
}
