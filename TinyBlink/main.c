#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t n;

ISR((unsigned int *)0x0006)
{
	PORTD &= ~(1<<0);
	n++;
}

void timer0_init()
{
	TCNT0 = 0x00;
	OCR0A = 0x42;
	TCCR0A = (1<<CS00) | (1<<CS02); //pre-scaler 1024
	TIMSK |= (1<<OCIE0A); //enable overflow interrupt
	sei(); //enable global interrupts
	n = 0;
}

int main(void)
{
	DDRD = 0xFF;  //port D - output
    timer0_init();
    while (1) 
    {
		PORTD |= 1<<0;
		//PORTD |= 1<<1;
		if (n >= 150)
		{
			PORTD ^= 1<<1;
			TCNT0 = 0x00;
			n = 0;
		}
    }
}

