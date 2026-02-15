#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 

 

int main(void) {
    DDRD |= (1<<PD0);        // PD0 = PWM выход
    DDRD &= ~(1<<PD6) | (1 << PD7);  
	DDRC &= (1 << PC3);
	
	ACSR &= ~(1 << ACD); // Включаем компаратор
	SFIOR |= (1 << ACME); // Разряд ACME в регистре SFIOR разрешает использовать мультиплексор для выбора одного из входов компаратора.

	ADMUX &= ~(1 << MUX2); 
	ADMUX |= (1 << MUX1) | (1 << MUX0); // 3 канал ацп

    while(1) {
       if (ACSR & (1 << ACO)) { // Если компаратор сработал AIN0 > AIN1
		   PORTD |= (1 << PD0); // Включаем светодиод
	   } else {
		   PORTD &= ~(1 << PD0); // Выключаем светодиод
	   }
    }
}