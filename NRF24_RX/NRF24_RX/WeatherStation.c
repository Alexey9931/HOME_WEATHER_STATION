/*
 * WeatherStation.c
 *
 * Created: 03.06.2022 19:15:57
 *  Author: Alex2
 */ 
#include "WeatherStation.h"

//Окно приветсвия на экране дисплея
void Print_Hello_World(uint8_t *Frame_buffer)
{
		
	LCD_12864_GrapnicMode(1);
	LCD_12864_Draw_rectangle(0, 0, 127, 63);
	LCD_12864_Draw_rectangle(1, 1, 125, 61);
	LCD_12864_Draw_rectangle(2, 2, 123, 59);
	LCD_12864_Draw_rectangle(3, 3, 121, 57);
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
	setpos_LCD_12864(3, 1);
	str_LCD_12864 ("HOME");
	setpos_LCD_12864(1, 2);
	str_LCD_12864 ("METEOSTATION");
	_delay_ms(3000);
	clear_LCD_12864();
	LCD_12864_GrapnicMode(1);
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_Clean();
	LCD_12864_GrapnicMode(0);
	
}
//Окно загрузки
void Print_Download(uint8_t *Frame_buffer)
{
	LCD_12864_GrapnicMode(1);
	LCD_12864_Draw_rectangle(6, 35, 112, 15);
	LCD_12864_Decode_UTF8(3, 1, 0, "Пожалуйста подождите.");
	LCD_12864_Decode_UTF8(16, 3, 0, "Идёт загрузка...");
	LCD_12864_Draw_bitmap(Frame_buffer);
	for(uint8_t i = 8; i <= 116 ; i = i + 11)
	{
		LCD_12864_Draw_rectangle_filled(i, 37, 9, 11);
		LCD_12864_Draw_bitmap(Frame_buffer);
		_delay_ms(500);
	}	
	LCD_12864_GrapnicMode(0);
}
//Вычисление кол-ва осадков
float RAIN_AMOUNT(char *adc_value)
{
	float RAIN;
	int R;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &R);
	}
	else
	{
		R = 0;
	}
	RAIN = 3*R*2.45/5120;
	
	return RAIN;
}
//Вычисление уровня заряда АКБ
float V_BAT (char *adc_value)
{
	float VBAT;
	int V;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &V);
	}
	else
	{
		V = 0;
	}
	VBAT = V*2.45*3/1024;
	
	return VBAT;
}
//Вычисление скорости ветра
float wind_speed (char *counter)
{
	float RADIUS = 0.09;
	float speed = 0;
	int n;
	if (strlen(counter) != 0)
	{
		sscanf(counter, "%d", &n);
	}
	else
	{
		n = 0;
	}
	speed = 2*3.14*RADIUS*n/4; //период 2 сек+2 магнита
	
	return speed;
}