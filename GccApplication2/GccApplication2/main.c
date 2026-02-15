#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 

 

int main(void) {
    DDRD |= (1<<PD0);        // PD0 = PWM выход
    DDRD &= ~(1<<PD6) | (1 << PD7);  

	// ACSR &= ~(1 << ACD); // Включаем компаратор
	// ACSR |= (1 << ACBG); // Внешнее сравнение с землей


    while(1) {
       if (ACSR & (1 << ACO)) { // Если компаратор сработал AIN0 > AIN1
		   PORTD |= (1 << PD0); // Включаем светодиод
	   } else {
		   PORTD &= ~(1 << PD0); // Выключаем светодиод
	   }
    }
}