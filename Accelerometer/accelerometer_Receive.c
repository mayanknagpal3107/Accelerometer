#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <util/delay.h>
#include "uart.h"
#include "uart.c"
#include <avr/interrupt.h>
void forward()
{
		sbi(PORTD,4);
		sbi(PORTD,5);		
		sbi(PORTD,2);
		cbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);		
}

void reverse()
{		sbi(PORTD,4);
		sbi(PORTD,5);		
		cbi(PORTD,2);
		sbi(PORTD,3);
		cbi(PORTD,7);
		sbi(PORTD,6);		
}

void left()
{		sbi(PORTD,4);
		sbi(PORTD,5);		
		cbi(PORTD,2);
		sbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);		
}
void right()
{		sbi(PORTD,4);
		sbi(PORTD,5);		
		sbi(PORTD,2);
		cbi(PORTD,3);
		cbi(PORTD,7);
		sbi(PORTD,6);
}
void stop()
{	cbi(PORTD,4);
	cbi(PORTD,5);
	cbi(PORTD,2);
	cbi(PORTD,3);
	cbi(PORTD,7);
	cbi(PORTD,6);	
}

motorinit()
{

	sbi(DDRD,2);
	sbi(DDRD,3);
	
	sbi(DDRD,4);
	sbi(DDRD,5);
	
	sbi(DDRD,6);
	sbi(DDRD,7);


}






void main()
{
   
DDRC=0xff;
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	//uart_puts("initialized");//uart_putc('f');
	motorinit();
	sbi(DDRC,4);
	sbi(PORTC,4);
	char c;
	unsigned int x,y,z;
	char str1[10],str2[10],str3[10];
	stop();
	
while(1)
	
	{
	
		c=uart_getc();
		if(c!=0)
		{
			uart_putc(c);
			if(c=='l')
			{
				forward();
				//uart_puts("forward\n");
				sbi(PORTC,0);
				cbi(PORTC,1);
				cbi(PORTC,2);
				cbi(PORTC,3);
				//_delay_ms(50);
			}
			 if(c=='r')
			{
				reverse();
				//uart_puts("reverse\n");
				sbi(PORTC,1);
				cbi(PORTC,0);
				cbi(PORTC,2);
				cbi(PORTC,3);
				//_delay_ms(50);
			}
			
			 if(c=='f')
			{
				left();
				//uart_puts("left\n");
				sbi(PORTC,2);
				cbi(PORTC,0);
				cbi(PORTC,1);
				cbi(PORTC,3);
				//_delay_ms(50);
			}
			 if(c=='b')
			{
					right();
				//uart_puts("right\n");
				sbi(PORTC,3);
				cbi(PORTC,0);
				cbi(PORTC,1);
				cbi(PORTC,2);
				//_delay_ms(50);
			}
			
			 if(c=='s')
			{
				stop();
				//uart_puts("stop\n");
				sbi(PORTC,0);
				sbi(PORTC,1);
				sbi(PORTC,2);
				sbi(PORTC,3);
			}
			
		}
	}

		
		
}