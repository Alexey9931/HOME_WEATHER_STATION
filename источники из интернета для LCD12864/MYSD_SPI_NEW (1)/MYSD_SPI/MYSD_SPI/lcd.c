#include "lcd.h"

//----------------------------------------
void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1; //включаем линию Е
	_delay_us(50);
	PORTD&=0b00001111; //стираем информацию на входах DB4-DB7, остальное не трогаем
	PORTD|=c;
	e0; //выключаем линию Е
	_delay_us(50);
}
//----------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) rs0;
	else         rs1;
	unsigned char hc=0;
	hc=c>>4;
	sendhalfbyte(hc); sendhalfbyte(c);
}
//----------------------------------------
void sendcharlcd(unsigned char c)
{
	sendbyte(c,1);
}
//----------------------------------------
void setpos(unsigned char x, unsigned y)
{
	switch(y)
	{
		case 0:
		sendbyte(x|0x80,0);
		break;
		case 1:
		sendbyte((0x40+x)|0x80,0);
		break;
		case 2:
		sendbyte((0x14+x)|0x80,0);
		break;
		case 3:
		sendbyte((0x54+x)|0x80,0);
		break;
	}
}
//----------------------------------------
void LCD_ini(void)
{
	_delay_ms(15); //Ждем 15 мс (стр 45)
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	_delay_ms(1);
	sendbyte(0b00000110, 0); //курсор (хоть он у нас и невидимый) будет двигаться влево
	_delay_ms(1);
}
//----------------------------------------
void clearlcd(void)
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}
//----------------------------------------
void str_lcd (char str1[])
{  
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	sendcharlcd(str1[n]);
}
//----------------------------------------
void str80_lcd (char str1[])
{
	unsigned char n;
	sendbyte(0x80,0);//1 строка
	for(n=0;n<=19;n++)
		sendcharlcd(str1[n]);
	for(n=40;n<=59;n++)//на 3ю строку перейдём автоматически в силу организации DDRAM дисплея
		sendcharlcd(str1[n]);
	sendbyte(0xC0,0);//2 строка
	for(n=20;n<=39;n++)
		sendcharlcd(str1[n]);
	for(n=60;n<=79;n++)//на 4ю строку перейдём автоматически в силу организации DDRAM дисплея
		sendcharlcd(str1[n]);
}
//----------------------------------------
