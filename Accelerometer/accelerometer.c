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


int readADC(int channel){
	
	unsigned int w;
	long val=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
	//ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	
	//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running 4
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
	
	
	 //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   ADCSRA|=(1<<ADIF);	
   
   w=ADCL;
   w|=(ADCH<<8);
   
   return w;
   
   
	
	
}



void main()
{
   
DDRC=0x0f;
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	uart_puts("initialized");//uart_putc('f');
	motorinit();
	sbi(DDRC,4);
	sbi(PORTC,4);
	unsigned int x,y,z;
	char str1[10],str2[10],str3[10];
	
	
while(1)
	
	{

		
		x= readADC(5);
		y= readADC(6);
		z= readADC(7);
		
	itoa(x,str1,10);
		uart_puts("X=");
		uart_puts(str1);
		uart_puts("\t");
		
		itoa(y,str2,10);
		uart_puts("Y=");
		uart_puts(str2);
		uart_puts("\t");
		
		itoa(z,str3,10);
		uart_puts("z=");
		uart_puts(str3);	
		
		
		uart_puts("\n\r");
		uart_puts("\n\r");

	/*	if(bit_is_clear(PINC,4))
		{
		
		uart_puts("SWITCH");
		stop();
		
		}
		
		
		if(((x>=280)&&(x<=380))&&((y>=330)&&(y<=420)))
		{
		stop();
		uart_puts("\t");	
		uart_puts("STOP");
		
		
		}
		// if((x<=300)&&((y>=340)&&(y<=370)))
		else if(((x>=420)&&(x<=498))&&((y>=360)&&(y<=400)))
		{
		forward();
		uart_puts("Forward");
		uart_puts("\t");
	
		}
		
		//else if((x>=400)&&((y>=340)&&(y<=370)))
		else if(((x>=180)&&(x<=240))&&((y>=360)&&(y<=400)))
		{
		reverse();
		uart_puts("Reverse");
		uart_puts("\t");
	
		}

		
		//else if(((x>=320)&&(x<=350))&&(y<=300))
		else if(((x>=320)&&(x<=350))&&((y>=440)&&(y<=520)))
		{
		right();
		uart_puts("Right");
        uart_puts("\t");		
		}
		
	   // else if(((x>=300)&&(x<=340))&&(y>=400))
		else if(((x>=310)&&(x<=350))&&((y>=220)&&(y<=300)))
		{
		left();
		uart_puts("left");
	    uart_puts("\t");
		}
		
		else
		{
		uart_puts("no");
			    uart_puts("\t");

		
		}
		
		_delay_ms(100);*/

		_delay_ms(400);
		
		
		//uart_puts("\n\r");
		//uart_puts("\n\r");
   }
   


}
