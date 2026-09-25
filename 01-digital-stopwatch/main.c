/* 数字秒表：定时器 0 每 10ms 中断，数码管显示 mm-ss-xx */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 code SEG[] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};

u8 centi;              /* 0.01 秒，满 100 = 1 秒 */
u8 sec;
u8 min;
u8 digits[8];          /* 8 位数码管段码缓存 */

void delay(u16 i)
{
	while (i--)
		;
}

void timer0_init(void)
{
	TMOD |= 0x01;      /* 定时器 0，模式 1 */
	TH0 = 0xD8;        /* 约 10ms（12MHz） */
	TL0 = 0xF0;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void update_digits(void)
{
	digits[0] = SEG[min / 10];
	digits[1] = SEG[min % 10];
	digits[2] = 0x40;          /* '-' */
	digits[3] = SEG[sec / 10];
	digits[4] = SEG[sec % 10];
	digits[5] = 0x40;
	digits[6] = SEG[centi / 10];
	digits[7] = SEG[centi % 10];
}

void scan_display(void)
{
	u8 i;
	for (i = 0; i < 8; i++)
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
		case 7: LSA = 0; LSB = 0; LSC = 0; break;
		}
		P0 = digits[i];
		delay(100);
		P0 = 0x00;
	}
}

void main(void)
{
	timer0_init();
	while (1)
	{
		update_digits();
		scan_display();
	}
}

void timer0_isr(void) interrupt 1
{
	TH0 = 0xD8;
	TL0 = 0xF0;
	centi++;
	if (centi >= 100)
	{
		centi = 0;
		sec++;
		if (sec >= 60)
		{
			sec = 0;
			min++;
			if (min >= 60)
				min = 0;
		}
	}
}
