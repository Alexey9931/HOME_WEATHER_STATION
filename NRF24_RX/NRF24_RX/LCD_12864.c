/*
 * LCD_12864.c
 *
 * Created: 12.05.2022 20:45:00
 *  Author: Alex2
 */ 
#include "LCD_12864.h"

extern uint8_t Frame_buffer[1024]; //Буфер кадра
extern uint8_t ST7920_width; //Ширина дисплея в пикселях
extern uint8_t ST7920_height; //Высота дисплея в пикселях

/*----------Инициализация--------------------*/
void LCD_12864_ini(void)
{
	_delay_ms(40);
	LCD_12864_send_command(0xC);//display on
	_delay_us(100);
	clear_LCD_12864();
	LCD_12864_send_command(6);//курсор сдвигается вправо
	_delay_ms(10);
}
/*----------Включение графического режима--------------------*/
void LCD_12864_GrapnicMode(uint8_t enable)   // 1-enable, 0-disable
{
	if (enable) 
	{
		LCD_12864_send_command(0x34); //Переходим в extended instruction
		_delay_ms(1);	
	    LCD_12864_send_command(0x36); //вкл графич. режим
		_delay_ms(1);	
	}
	else
	{
		LCD_12864_send_command(0x30); //Переходим в basic instruction
		_delay_ms(1);
	}
}
/*----------Вывод изображения на экран дисплея--------------------*/
void LCD_12864_Draw_bitmap(const unsigned char *bitmap) {
	/// Функция вывода изображения на дисплей
	/// Работает с памятью ST7920.
	/// \param *bitmap - изображение 128*64. т.е. Буфер из 1024 элементов.
	uint8_t x, y;
	uint16_t i = 0;
	uint8_t Temp, Db;

	for (y = 0; y < 64; y++) {
		for (x = 0; x < 8; x++) {
			if (y < 32) {
				LCD_12864_send_command(0x80 | y);				//y(0-31)
				LCD_12864_send_command(0x80 | x);				//x(0-8)
				} else {
				LCD_12864_send_command(0x80 | (y - 32));		//y(0-31)
				LCD_12864_send_command(0x88 | x);				//x(0-8)
			}

			i = ((y / 8) * 128) + (x * 16);
			Db = y % 8;

			Temp = (((bitmap[i] >> Db) & 0x01) << 7) | (((bitmap[i + 1] >> Db) & 0x01) << 6) | (((bitmap[i + 2] >> Db) & 0x01) << 5)
			| (((bitmap[i + 3] >> Db) & 0x01) << 4) | (((bitmap[i + 4] >> Db) & 0x01) << 3) | (((bitmap[i + 5] >> Db) & 0x01) << 2)
			| (((bitmap[i + 6] >> Db) & 0x01) << 1) | (((bitmap[i + 7] >> Db) & 0x01) << 0);
			LCD_12864_send_data(Temp);

			Temp = (((bitmap[i + 8] >> Db) & 0x01) << 7) | (((bitmap[i + 9] >> Db) & 0x01) << 6) | (((bitmap[i + 10] >> Db) & 0x01) << 5)
			| (((bitmap[i + 11] >> Db) & 0x01) << 4) | (((bitmap[i + 12] >> Db) & 0x01) << 3) | (((bitmap[i + 13] >> Db) & 0x01) << 2)
			| (((bitmap[i + 14] >> Db) & 0x01) << 1) | (((bitmap[i + 15] >> Db) & 0x01) << 0);

			LCD_12864_send_data(Temp);
		}
	}
}
/*----------Рисование пикселя--------------------*/
void LCD_1286_Draw_pixel(uint8_t x, uint8_t y) {
	/// Функция рисования точки.
	/// param\ x - координата по X(от 0 до 127)
	/// paran\ y - координата по Y(от 0 до 63)
	if (y < ST7920_height && x < ST7920_width) {
		Frame_buffer[(x) + ((y / 8) * 128)] |= 0x01 << y % 8;
	}
}
/*----------Очистка--------------------*/
void clear_LCD_12864(void)
{
	LCD_12864_send_command(0x1);//clear
	_delay_ms(10);
}
/*----------Позиционирование символьного текста--------------------*/
void setpos_LCD_12864(unsigned char x, unsigned y)
{
	uint8_t command;
	switch (y)
	{
		case 0: command = 0x80; break;
		case 1: command = 0x90; break;
		case 2: command = 0x88; break;
		case 3: command = 0x98; break;
	}
	command = command | x;
	LCD_12864_send_command(command);
}
/*----------Вывод символьного текста строкой--------------------*/
void str_LCD_12864 (char *str1)
{
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	LCD_12864_send_data(str1[n]);
}
/*----------Отправка данных--------------------*/
void LCD_12864_send_data(uint8_t data)
{
	PORTD |= (1<<RS);
    //передача 5 единиц
	PORTD |= (1<<RW);
	strob();
	strob();
	strob();
	strob();
	strob();
	PORTD &= ~(1<<RW);//r/w=0
	strob();
	PORTD |= (1<<RW);//rs=1
	strob();
	PORTD &= ~(1<<RW);
	strob();
	for (int k = 0; k < 12; k++)
	{
		if ((k == 4)||(k == 5)||(k == 6)||(k == 7))
		{
			PORTD &= ~(1<<RW);
			strob();
		}
		else
		{
			switch(data & 0x80)
			{
				case 0x80: PORTD |= (1<<RW);
						strob();
						break;
				case 0: PORTD &= ~(1<<RW);
						strob();	
						break;
			}
			data = data << 1;
		}
	}
	//передача 4 нулей
	PORTD &= ~(1<<RW);
	strob();
	strob();
	strob();
	strob();
	
	PORTD &= ~(1<<RS);
}
/*----------Отправка команды--------------------*/
void LCD_12864_send_command(uint8_t command)
{
	PORTD |= (1<<RS);
    //передача 5 единиц
	PORTD |= (1<<RW);
	strob();
	strob();
	strob();
	strob();
	strob();
	PORTD &= ~(1<<RW);//r/w=0
	strob();
	PORTD &= ~(1<<RW);//rs=0
	strob();
	PORTD &= ~(1<<RW);
	strob();
	for (int k = 0; k < 12; k++)
	{
		if ((k == 4)||(k == 5)||(k == 6)||(k == 7))
		{
			PORTD &= ~(1<<RW);
			strob();
		}
		else
		{
			switch(command & 0x80)
			{
				case 0x80: PORTD |= (1<<RW);
				strob();
				break;
				case 0: PORTD &= ~(1<<RW);
				strob();
				break;
			}
			command = command << 1;
		}
	}
	//передача 4 нулей
	PORTD &= ~(1<<RW);
	strob();
	strob();
	strob();
	strob();
	
	PORTD &= ~(1<<RS);
}
/*----------Тактовый импульс--------------------*/
void strob(void)
{
	_delay_us(1);
	PORTD |= (1<<E);
	_delay_us(1);
	PORTD &= ~(1<<E);
	_delay_us(1);
}

/*----------Различная графика--------------------*/
/*-----------------------------------------------*/
/*----------Линия--------------------*/
void ST7920_Draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end) {
	int dx = (x_end >= x_start) ? x_end - x_start : x_start - x_end;
	int dy = (y_end >= y_start) ? y_end - y_start : y_start - y_end;
	int sx = (x_start < x_end) ? 1 : -1;
	int sy = (y_start < y_end) ? 1 : -1;
	int err = dx - dy;

	for (;;) {
		LCD_1286_Draw_pixel(x_start, y_start);
		if (x_start == x_end && y_start == y_end)
		break;
		int e2 = err + err;
		if (e2 > -dy) {
			err -= dy;
			x_start += sx;
		}
		if (e2 < dx) {
			err += dx;
			y_start += sy;
		}
	}
}
/*----------Пустотелый прямоугольник--------------------*/
void ST7920_Draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	/// Вывести пустотелый прямоугольник
	/// \param x - начальная точка по оси "x"
	/// \param y - начальная точка по оси "y"
	/// \param width - ширина прямоугольника
	/// \param height - высота прямоугольника

	/*Проверка ширины и высоты*/
	if ((x + width) >= ST7920_width) {
		width = ST7920_width - x;
	}
	if ((y + height) >= ST7920_height) {
		height = ST7920_height - y;
	}

	/*Рисуем линии*/
	ST7920_Draw_line(x, y, x + width, y); /*Верх прямоугольника*/
	ST7920_Draw_line(x, y + height, x + width, y + height); /*Низ прямоугольника*/
	ST7920_Draw_line(x, y, x, y + height); /*Левая сторона прямоугольника*/
	ST7920_Draw_line(x + width, y, x + width, y + height); /*Правая сторона прямоугольника*/
}