/*
 * LCD_12864.h
 *
 * Created: 12.05.2022 20:45:14
 *  Author: Alex2
 */ 


#ifndef LCD_12864_H_
#define LCD_12864_H_

#include "main.h"

#define RS PORTD7
#define RW PORTD6
#define E PORTD5
//#define PSB PORTB1

void LCD_12864_ini(void);
void str_LCD_12864 (char *str1);
void LCD_12864_GrapnicMode(uint8_t enable);
void LCD_12864_Draw_bitmap(const unsigned char *bitmap);
void LCD_1286_Draw_pixel(uint8_t x, uint8_t y);
void clear_LCD_12864(void);
void setpos_LCD_12864(unsigned char x, unsigned y);
void LCD_12864_send_data(uint8_t data);
void LCD_12864_send_command(uint8_t command);
void strob(void);
void LCD_12864_print_symbol(uint16_t x, uint16_t symbol, uint8_t inversion);
void LCD_12864_Clean();
void LCD_12864_Clean_Frame_buffer(void);
void LCD_12864_Decode_UTF8(uint16_t x, uint8_t y, uint8_t inversion, char *tx_buffer);
void LCD_12864_Inversion(uint16_t x_start, uint16_t x_end);
void LCD_12864_Draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end);
void LCD_12864_Draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height);


#endif /* LCD_12864_H_ */