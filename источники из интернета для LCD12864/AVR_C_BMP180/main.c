// 				Author:  Skyer                            			   //
// 				Website: www.smartep.ru                  			   //
/////////////////////////////////////////////////////////////////////////
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <avr/pgmspace.h>
	#include <string.h>
//=============================================================================================================
	#include "lib/i2c.h"
	#include "lib/bmp180.h"
//=============================================================================================================
	#define	SEG_PORT 							PORTA
	#define	SEG_DDR  							DDRA
	#define	DIG_PORT 							PORTB
	#define	DIG_DDR  							DDRB
	#define	Digit1  							PB0
	#define	Digit2  							PB1
	#define	Digit3  							PB2
	#define	Digit4  							PB3
	#define DISPLAY_DELAY						4
	#define SYMBOL_POINT						0b10000000
	#define SYMBOL_MINUS						0b01000000
//=============================================================================================================
	uint16_t 	ms = 0;
	uint8_t 	sec = 0, min = 0, hour = 0;
	uint32_t 	second_count = 0;
	uint8_t 	refresh = 0;
	uint8_t 	dig[4] = {0, 0, 0, 0};
	int32_t 	BMP180_Temperature = BMP180_ERROR;
	uint32_t 	BMP180_Pressure = BMP180_ERROR;
	uint32_t 	BMP180_Update_Time = 0;
//=============================================================================================================
	// Массив для декодирования цифры в код числа для 7-сегментного индикатора
	uint8_t digits[10] = {
		//hgfedcba
		0b00111111,
		0b00000110,
		0b01011011,
		0b01001111,
		0b01100110,
		0b01101101,
		0b01111101,
		0b00000111,
		0b01111111,
		0b01101111,
	};
//=============================================================================================================
ISR(TIMER2_COMP_vect)
{
	uint8_t sreg_save = SREG;
	ms++;
	if(ms == 1000)
	{
		second_count++;
		ms = 0;
		sec++;
		if (sec == 60)
		{
			sec = 0;
			min++;
			if (min == 60)
			{
				min = 0;
				hour++;
				if (hour == 24)
					hour = 0;
			}
		}
	}
	SREG = sreg_save;
}
//=============================================================================================================
void BMP180_Update()
{
	BMP180_Read(&BMP180_Temperature, &BMP180_Pressure);
	BMP180_Update_Time = second_count + BMP180_REFRESH_TIME;
	refresh = 1;
}
//=============================================================================================================
int main (void)
{
	// Запрещаем прерывания
	cli();
	// Настраиваем порты ввода-вывода
	SEG_DDR = 0xFF;
	SEG_PORT = 0x00;
	DIG_DDR = (1 << Digit1)|(1 << Digit2)|(1 << Digit3)|(1 << Digit4);
	DIG_PORT &= ~((1 << Digit1)|(1 << Digit2)|(1 << Digit3)|(1 << Digit4));
	I2C_Init();
	BMP180_Init();
	// Настраиваем таймеры
	// Разрешение прерывания таймера 2
	TIMSK = (1 << OCIE2);
	// Настраиваем таймер 2 на подсчет секунд
	// Предделитель на 64
	TCCR2 = (1 << WGM21)|(0 << WGM20)|(1 << CS22)|(0 << CS21)|(0 << CS20);
	OCR2 = F_CPU / 64 / 1000;
	// Обнуляем счетчик таймера 2
	TCNT2 = 0;
	// Запуск первого измерения температуры
	_delay_ms(1000);
	BMP180_Update();
	// Разрешаем прерывания
	sei();
	// Основная программа
	while (1)
	{
		if(second_count >= BMP180_Update_Time)
			BMP180_Update();
		// Преобразование температуры в отдельные цифры для вывода
		if (refresh)
		{
			if (BMP180_Pressure != BMP180_ERROR)
			{
				int32_t pressure = BMP180_Pressure / 133;
				if (pressure >= 1000)
					dig[0] = digits[pressure % 10000 / 1000];
				else
					dig[0] = 0;
				dig[1] = digits[pressure % 1000 / 100];
				dig[2] = digits[pressure / 10 % 10];
				dig[3] = digits[pressure % 10];
			}
			else
				memset(dig, SYMBOL_MINUS, sizeof(dig));
			refresh = 0;
		}
		DIG_PORT = (1 << Digit1);
		SEG_PORT = dig[0];
		_delay_ms(DISPLAY_DELAY);
		DIG_PORT = (1 << Digit2);
		SEG_PORT = dig[1];
		_delay_ms(DISPLAY_DELAY);
		DIG_PORT = (1 << Digit3);
		SEG_PORT = dig[2];
		_delay_ms(DISPLAY_DELAY);
		DIG_PORT = (1 << Digit4);
		SEG_PORT = dig[3];
		_delay_ms(DISPLAY_DELAY);
	}
}
