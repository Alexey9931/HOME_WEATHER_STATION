/*
 * lcd.c
 *
 * Created: 18.11.2021 15:13:05
 *  Author: Alex2
 */ 
#include "lcdtwi.h"

unsigned char portlcd = 0; //ячейка для хранения данных порта микросхемы расширения

void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1; //включаем линию Е
	_delay_us(50);
	I2C_SendByteByADDR(portlcd|c,0b01001110);
	e0; //выключаем линию Е
	_delay_us(50);
}
//—————————————-
void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) rs0;
	else rs1;
	unsigned char hc=0;
	hc=c>>4;
	sendhalfbyte(hc); sendhalfbyte(c);
}
//—————————————-
void sendchar(unsigned char c)
{
	sendbyte(c,1);
}
//—————————————-
void setpos(unsigned char x, unsigned y)
{
	char adress;
	adress=(0x40*y+x)|0b10000000;
	sendbyte(adress|0x80, 0);
}
//—————————————-
void LCD_ini(void)
{
	_delay_ms(40); //Ждем 40 мс
	sendhalfbyte(0b00000011);
	_delay_us(39);	
	sendhalfbyte(0b00000010);//из "танцев с бубном"
	_delay_ms(1);	
	sendbyte(0b00101000,0);//переход в 4бит режим
	_delay_us(39);
	sendbyte(0b00101000,0);//переход в 4бит режим
	_delay_us(37);
	sendbyte(0b00001000, 0);//display on/off control
	_delay_us(37);
	sendbyte(0b00000001, 0);//display clear
	_delay_ms(1);
	sendbyte(0b00000110, 0);//entry mode set
	_delay_ms(1);
	sendbyte(0b00001100, 0);
	_delay_ms(1);
	 setled();//подсветка
	 setwrite();//запись
}
//—————————————-
void str_lcd (char *str1)
{
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	sendchar(str1[n]);
}
//—————————————-
void clearlcd ()
{
    sendbyte(0b00000001, 0);
    _delay_ms(2);
}