#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

 
int main(void) {
    DDRD |= (1 << PD0);

    ACSR |= (1 << ACBG);

    while (1) {
        if (ACSR & (1 << ACO)) {
            PORTD &= ~(1 << PD0);
        } else {
            PORTD |= (1 << PD0);
        }
    }
}