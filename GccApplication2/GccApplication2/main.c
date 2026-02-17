#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#define F_CPU 16000000UL

#define RC_1 PORTD |= (1 << PD2) // Пин для управления светодиодом
#define RC_0 PORTD &= ~(1 << PD2) // Пин для управления светодиодом

#define E_1_PORTD PORTD |= (1 << PD3) // разрешаем выход на дисплей
#define E_0_PORTD PORTD &= ~(1 << PD3) // запрещаем выход на дисплей

// настройки портов жк
void PORT_LCD_settingd() {
	DDRD = 0b11111110;        // PD0 = PWM выход
	E_1_PORTD; // Разрешаем выход на дисплей
}
 

void LCD_command(unsigned char cmd) {
	PORTD = cmd; // Записываем команду в порт
	RC_0; // Разрешаем выход на дисплей
	E_1_PORTD;
	_delay_ms(1); // Ждем 1 мс
	E_0_PORTD; // Запрещаем выход на дисплей
	PORTD = (cmd << 4); // Устанавливаем бит RS в 1 для передачи команды

	RC_0;
	E_1_PORTD;
	_delay_ms(1);  
	E_0_PORTD;  
	_delay_ms(1);  

}

// передача данных
void LCD_data(unsigned char data) {
	PORTD = data; // Записываем команду в порт
	RC_1;  
	E_1_PORTD;
	_delay_ms(1); // Ждем 1 мс
	E_0_PORTD; // Запрещаем выход на дисплей
	PORTD = (data << 4); // Устанавливаем бит RS в 1 для передачи команды

	RC_1;
	E_1_PORTD;
	_delay_ms(1);  
	E_0_PORTD;  
	_delay_ms(1);  

}

// настройка дисплея
void LCD_settings() {
	_delay_ms(15); // Ждем 15 мс после подачи питания на дисплей

	LCD_command(0b00110000); // Устанавливаем бит RS в 1 для передачи команды
	_delay_ms(5); // Ждем 1 мс
	LCD_command(0b00110000);
	_delay_ms(1); // Ждем 1 мс
	LCD_command(0b00110000);
}


int main(void) {
	PORT_LCD_settingd();
	LCD_settings();
	
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