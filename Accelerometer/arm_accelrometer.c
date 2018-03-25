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
   
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	
	//motorinit();
	sbi(DDRC,0);
	sbi(DDRC,1);
	sbi(DDRC,2);
	sbi(DDRC,3);
	
	//sbi(DDRC,4);
	//sbi(PORTC,4);
	unsigned int a1,a2,b1,b2,c1,c2;
	char str1[5]={0};
	char str2[5]={0};
	char str3[5]={0};
	char str4[5]={0};
	char str5[5]={0};
	char str6[5]={0};
	
	
	
	
while(1)
	
	{
		//uart_puts("welcome");
		
		a1= readADC(0);
		a2= readADC(1);
		
		
		b1= readADC(2);
		b2= readADC(3);
		
		
		c1= readADC(4);
		c2= readADC(5);
		
		
		itoa(a1,str1,10);
		itoa(a2,str2,10);
		itoa(b1,str3,10);
		itoa(b2,str4,10);
		itoa(c1,str5,10);
		itoa(c2,str6,10);
		
		/*uart_puts("a1=");
		uart_puts(str1);
		uart_puts("\t");		
		uart_puts("a2=");
		uart_puts(str2);
		uart_puts("\n\r");
		
		uart_puts("b1=");
		uart_puts(str3);
		uart_puts("\t");		
		uart_puts("b2=");
		uart_puts(str4);
		uart_puts("\n\r");
		
		uart_puts("c1=");
		uart_puts(str5);
		uart_puts("\t");		
		uart_puts("c2=");
		uart_puts(str6);
		uart_puts("\n\r");
		uart_puts("\n\r");*/
		
		/*//if( ((a1>=490)&&(a1<=530))&&((a2>=335)&&(a2<=360))&&((b1>=800)&&(b1<=825))&&((b2>=575)&&(b2<=610))&&((c1>=800)&&(c1<=830))&&((c1>=640)&&(c1<=675)) )
		if( ((a1>=490)&&(a1<=530))&&((a2>=335)&&(a2<=360))&&((b1>=800)&&(b1<=825))&&((b2>=575)&&(b2<=610))&&((c1>=800)&&(c1<=830))&&((c2>=640)&&(c2<=675)) )
		{
		uart_puts("straight\n\r");
		_delay_ms(100);

		
		}*/
		
		if( ((a1>=250)&&(a1<=350)) )
		{
		//uart_puts("up\n\r");
		uart_putc('a'); //a=up
		sbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
		//_delay_ms(100);		
		}
		
		else if( ((a1>=700)&&(a1<=750)) )
		{
		//uart_puts("down\n\r");
		uart_putc('b');
		cbi(PORTC,0);
		sbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
		}
		
		else if( ((c2>=300)&&(c2<=380)) )
		{
		//uart_puts("gripper up\n\r");
		uart_putc('c');
		cbi(PORTC,0);
		cbi(PORTC,1);
		sbi(PORTC,2);
		cbi(PORTC,3);
		}
		
		
		/*else if( ((c2>=540)&&(c2<=570)) )
		{
		uart_puts("gripper down\n\r");
		}*/
		
		else if( ((c1>=740)&&(c1<=850)) )
		{
		//uart_puts("half move\n\r");
		uart_putc('d');
		cbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		sbi(PORTC,3);
		}
		
		
		else if( ((c1>=300)&&(c1<=400)) )
		{
		//uart_puts("halg down\n\r");
		uart_putc('e');
		cbi(PORTC,0);
		cbi(PORTC,1);
		sbi(PORTC,2);
		sbi(PORTC,3);
		}
		
		else
		{
				//uart_puts("straight\n\r");
				uart_putc('s');
				sbi(PORTC,0);
		sbi(PORTC,1);
		sbi(PORTC,2);
		sbi(PORTC,3);
				

		}

		
		
		
		
		
		
		
		
		//if( ((a1>=490)&&(a1<=530))&&((a2>=335)&&(a2<=360))&&((b1>=800)&&(b1<=825))&&((b2>=575)&&(b2<=610))&&((c1>=800)&&(c1<=830))&&((c1>=660)&&(c1<=675)) )

		
		//uart_puts("\n\r");
		//uart_puts("\n\r");

		/*if(bit_is_clear(PINC,4))
		{
		
		uart_putc('s');
		stop();
		
		}*/
		
		
		/*if(((x>=280)&&(x<=380))&&((y>=330)&&(y<=420)))
		{
		//stop();
		//uart_puts("\t");	
		//uart_puts("STOP");
		uart_putc('s');
		sbi(PORTC,0);
		sbi(PORTC,1);
		sbi(PORTC,2);
		sbi(PORTC,3);
		
		
		}
		// if((x<=300)&&((y>=340)&&(y<=370)))
		else if(((x>=420)&&(x<=498))&&((y>=360)&&(y<=400)))
		{
		//forward();
		//uart_puts("Forward");
		//uart_puts("\t");
		uart_putc('f');
		cbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
	
		}
		
		//else if((x>=400)&&((y>=340)&&(y<=370)))
		else if(((x>=180)&&(x<=240))&&((y>=360)&&(y<=400)))
		{
		//reverse();
		//uart_puts("Reverse");
		//uart_puts("\t");
		uart_putc('b');
		sbi(PORTC,0);
		cbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);
	
		}

		
		//else if(((x>=320)&&(x<=350))&&(y<=300))
		else if(((x>=320)&&(x<=350))&&((y>=440)&&(y<=520)))
		{
		//right();
		//uart_puts("Right");
       // uart_puts("\t");		
        uart_putc('r');	
		cbi(PORTC,0);
		sbi(PORTC,1);
		cbi(PORTC,2);
		cbi(PORTC,3);	
		}
		
	   // else if(((x>=300)&&(x<=340))&&(y>=400))
		else if(((x>=310)&&(x<=350))&&((y>=220)&&(y<=300)))
		{
		//left();
		//uart_puts("left");
	   // uart_puts("\t");
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
		//uart_puts("no");
	    //uart_puts("\t");
		//uart_puts("\t");

		
		}*/
		
		//_delay_ms(100);

		_delay_ms(2000);
		
		
	//	uart_puts("\n\r");
	//	uart_puts("\n\r");
   }
   


}
