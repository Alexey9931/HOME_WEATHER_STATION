/*
 * lcd.h
 *
 * Created: 18.11.2021 15:12:53
 *  Author: Alex2
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "main.h"

//�������������-
#define e1 I2C_SendByteByADDR(portlcd|=0x04,0b01001110) // ��������� ����� E � 1
#define e0 I2C_SendByteByADDR(portlcd&=~0x04,0b01001110) // ��������� ����� E � 0
#define rs1 I2C_SendByteByADDR(portlcd|=0x01,0b01001110) // ��������� ����� RS � 1
#define rs0 I2C_SendByteByADDR(portlcd&=~0x01,0b01001110) // ��������� ����� RS � 0
#define setled() I2C_SendByteByADDR(portlcd|=0x08,0b01001110) // ��������� ���������
#define setwrite() I2C_SendByteByADDR(portlcd&=~0x02,0b01001110) // ��������� ������ � ������ �������

void LCD_ini(void);
void setpos(unsigned char x, unsigned y);
void str_lcd (char *str1);
void sendchar(unsigned char c);
void clearlcd();

#endif /* LCD_H_ */