#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	// --- Настройка порта D ---
	DDRD |= (1 << PD0) | (1 << PD1);	  // PD0 и PD1 как выход
	PORTD &= ~(1 << PD0) & ~(1 << PD1); // LED изначально выкл

	// --- Настройка компаратора ---
	ACSR &= ~(1 << ACD); // включить компаратор
	ACSR |= (1 << ACBG); // AIN0 = внутренняя опора 1.22V

	// Прерывание по любом изменению выхода компаратора
	ACSR |= (1 << ACIS1);
	ACSR |= (1 << ACIS0);

	while (1)
	{
		if (ACSR & (1 << ACO))
		{
			PORTD &= ~(1 << PD0);
			PORTD |= (1 << PD1);  
		}
		else
		{
			PORTD |= (1 << PD0);
			PORTD &= ~(1 << PD1);  
		}
	}
}