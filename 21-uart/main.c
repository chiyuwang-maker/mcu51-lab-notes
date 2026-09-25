/* 串口回显：波特率 4800，收到什么发回什么 */
#include <reg52.h>

typedef unsigned char u8;

void uart_init(void)
{
	SCON = 0x50;       /* 方式 1，允许接收 */
	TMOD = 0x20;       /* 定时器 1，模式 2（8 位自动重装） */
	PCON = 0x80;       /* SMOD=1，波特率加倍 */
	TH1 = 0xF3;        /* 12MHz 下约 4800 */
	TL1 = 0xF3;
	ES = 1;
	EA = 1;
	TR1 = 1;
}

void main(void)
{
	uart_init();
	while (1)
	{
	}
}

void uart_isr(void) interrupt 4
{
	u8 data_byte;

	data_byte = SBUF;
	RI = 0;
	SBUF = data_byte;
	while (!TI)
		;
	TI = 0;
}
