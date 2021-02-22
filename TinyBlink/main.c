#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t n;

SIGNAL(TIMER0_COMPA_vect)
{
	PORTD ^= 1<<0;
	//PORTD &= ~(1<<0);
	n++;
}

void timer0_init()
{
	OCR0A = 0x80; //number to count up to
	TCCR0A = 0x02; //clear timer on compare match (CTC) mode
	TIFR |= 0x01; //clear interrupt flag
	TIMSK = 0x01; // TC0 compare match A interrupt enable
	TCCR0B = 0x04; // clock source CLK/1024, start timer (0x05)
	sei(); //enable global interrupts
	n = 0;
}

int main(void)
{
	DDRD = 0xFF;  //port D - output
    timer0_init();
    while (1) 
    {
		//PORTD |= 1<<0;
		
		if (n >= 15)
		{
			PORTD ^= 1<<1;
			TCNT0 = 0x00;
			n = 0;
		}
    }
}

