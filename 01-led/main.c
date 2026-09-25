/* 点亮一颗 LED：P2.0 置低点亮，然后空转 */
#include <reg52.h>

sbit LED = P2^0;

void main(void)
{
	LED = 0;   /* 低电平点亮 */
	while (1)
	{
	}
}
