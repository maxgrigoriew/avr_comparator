#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#define F_CPU 8000000UL
 
int main(void) {
	
	ACSR &= ~(1 << ACD); // Включаем компаратор
	ACSR |= (1 << ACIE); // Разрешаем прерывание от компаратора

	ACSR |= (1 << ACBG); // Внутренний компаратор
	DDRD |= (1 << 0); // Устанавливаем PD0 как выход для светодиода

    while(1) {
       if (ACSR & (1 << ACO)) { // Если компаратор сработал AIN0 > AIN1
		PORTD &= ~(1 << PD0); // Выключаем светодиод
	   } else {
		   PORTD |= (1 << PD0); // Включаем светодиод
	   }
    }
}