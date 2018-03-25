#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>

#include "uart.h"
#include "uart.c"
#include <avr/interrupt.h>



int readADC(int channel){
	
	unsigned int w;
	long val=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

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

	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	sei();
	
	//motorinit();
	sbi(DDRC,0);
	sbi(DDRC,1);
	sbi(DDRC,2);
	sbi(DDRC,3);
	
	sbi(DDRC,4);
	sbi(PORTC,4);
	unsigned int x,y,z;
	char str1[10],str2[10],str3[10];	
	
while(1)	
	{
		x= readADC(0);		
		y= readADC(1);
		z= readADC(3);
		
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
		
		
		//uart_puts("\n\r");
		//uart_puts("\n\r");

		if(bit_is_clear(PINC,4))
		{
		
		uart_putc('s');
		//stop();
		
		}
		
		
		if(((x>=480)&&(x<=560))&&((y>=430)&&(y<=550)))
		{
		
		uart_putc('s');
		sbi(PORTC,0);
		sbi(PORTC,1);
		sbi(PORTC,2);
		sbi(PORTC,3);
		
		
		}
		
		else if(((x>=330)&&(x<=440))&&((y>=470)&&(y<=510)))
		{
		
		uart_putc('f');
		cbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
	
		}
		
		else if(((x>=570)&&(x<=680))&&((y>=480)&&(y<=520)))
		{
		
		uart_putc('b');
		sbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
	
		}

		
		
		else if(((x>=490)&&(x<=530))&&((y>=370)&&(y<=510)))
		{
			
        uart_putc('r');	
		cbi(PORTC,0);
		sbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);	
		}
		
		else if(((x>=500)&&(x<=540))&&((y>=540)&&(y<=650)))
		{
		
	    uart_putc('l');
		cbi(PORTC,0);
		cbi(PORTC,1);
		sbi(PORTC,2);
		cbi(PORTC,3);
		}
		
		else
		{
		cbi(PORTC,0);
		cbi(PORTC,1);
		sbi(PORTC,2);
		sbi(PORTC,3);	
		}
		
		_delay_ms(400);


		
		
		uart_puts("\n\r");
		uart_puts("\n\r");
   }
   


}
