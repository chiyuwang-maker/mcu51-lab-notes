/* 直流电机短时运转：约转 5 秒后停转 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit MOTO = P1^0;

/* 粗延时，i=1 约 10us（12MHz 晶振量级） */
void delay(u16 i)
{
	while (i--)
		;
}

void main(void)
{
	u8 i;

	MOTO = 0;              /* 先关掉 */
	for (i = 0; i < 100; i++)
	{
		MOTO = 1;
		delay(5000);       /* 约 50ms × 100 ≈ 5s */
	}
	MOTO = 0;

	while (1)
	{
	}
}
