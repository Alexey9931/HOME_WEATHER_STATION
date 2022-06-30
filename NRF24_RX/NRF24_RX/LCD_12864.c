/*
 * LCD_12864.c
 *
 * Created: 12.05.2022 20:45:00
 *  Author: Alex2
 */ 
#include "LCD_12864.h"

extern uint8_t Frame_buffer[1024]; //����� �����
extern uint8_t ST7920_width; //������ ������� � ��������
extern uint8_t ST7920_height; //������ ������� � ��������

/*-----------------------------------����� 5*7----------------------------------*/
/*
const uint8_t Font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0/ --> space     20
	0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, //1/ --> !         21
	0x00, 0x07, 0x00, 0x07, 0x00, 0x00, //2/ --> "         22 � �.�.
	0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, //3/ --> #
	0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, //4/ --> $
	0x00, 0x23, 0x13, 0x08, 0x64, 0x62, //5/ --> %
	0x00, 0x36, 0x49, 0x55, 0x22, 0x40, //6/ --> &
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00, //7/ --> '
	0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, //8/ --> (
	0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, //9/ --> )
	0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, //10/ --> *
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, //11/ --> +
	0x00, 0xA0, 0x60, 0x00, 0x00, 0x00, //12/ --> ,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08, //13/ --> -
	0x00, 0x60, 0x60, 0x00, 0x00, 0x00, //14/ --> .
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02, //15/ --> /
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, //16/ --> 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, //17/ --> 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46, //18/ --> 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, //19/ --> 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, //20/ --> 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39, //21/ --> 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, //22/ --> 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03, //23/ --> 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36, //24/ --> 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, //25/ --> 9
	0x00, 0x6C, 0x6C, 0x00, 0x00, 0x00, //26/ --> :
	0x00, 0x00, 0x56, 0x36, 0x00, 0x00, //27/ --> ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00, //28/ --> <
	0x00, 0x24, 0x24, 0x24, 0x24, 0x24, //29/ --> =
	0x00, 0x00, 0x41, 0x22, 0x14, 0x08, //30/ --> >
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06, //31/ --> ?
	0x00, 0x32, 0x49, 0x79, 0x41, 0x3E, //32/ --> @
	0x00, 0x7E, 0x11, 0x11, 0x11, 0x7E, //33/ --> A
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, //34/ --> B
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, //35/ --> C
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, //36/ --> D
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, //37/ --> E
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, //38/ --> F
	0x00, 0x3E, 0x41, 0x49, 0x49, 0x3A, //39/ --> G
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, //40/ --> H
	0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, //41/ --> I
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, //42/ --> J
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, //43/ --> K
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, //44/ --> L
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, //45/ --> M
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, //46/ --> N
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, //47/ --> O
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, //48/ --> P
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, //49/ --> Q
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, //50/ --> R
	0x00, 0x46, 0x49, 0x49, 0x49, 0x31, //51/ --> S
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, //52/ --> T
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, //53/ --> U
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, //54/ --> V
	0x00, 0x3F, 0x40, 0x60, 0x40, 0x3F, //55/ --> W
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63, //56/ --> X
	0x00, 0x07, 0x08, 0x70, 0x08, 0x07, //57/ --> Y
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43, //58/ --> Z
	0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, //59/ --> [
	0x00, 0x15, 0x16, 0x7C, 0x16, 0x15, //60/ --> '\'
	0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, //61/ --> ]
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04, //62/ --> ^
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40, //63/ --> _
	0x00, 0x01, 0x02, 0x04, 0x00, 0x00, //64/ --> `
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78, //65/ --> a
	0x00, 0x7F, 0x44, 0x44, 0x44, 0x38, //66/ --> b
	0x00, 0x38, 0x44, 0x44, 0x44, 0x00, //67/ --> c
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, //68/ --> d
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18, //69/ --> e
	0x00, 0x10, 0x7E, 0x11, 0x01, 0x02, //70/ --> f
	0x00, 0x0C, 0x52, 0x52, 0x52, 0x3E, //71/ --> g
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, //72/ --> h
	0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, //73/ --> i
	0x00, 0x20, 0x40, 0x40, 0x3D, 0x00, //74/ --> j
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, //75/ --> k
	0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, //76/ --> l
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, //77/ --> m
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, //78/ --> n
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38, //79/ --> o
	0x00, 0x7C, 0x14, 0x14, 0x14, 0x08, //80/ --> p
	0x00, 0x08, 0x14, 0x14, 0x18, 0x7C, //81/ --> q
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, //82/ --> r
	0x00, 0x48, 0x54, 0x54, 0x54, 0x20, //83/ --> s
	0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, //84/ --> t
	0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, //85/ --> u
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, //86/ --> v
	0x00, 0x1E, 0x20, 0x10, 0x20, 0x1E, //87/ --> w
	0x00, 0x22, 0x14, 0x08, 0x14, 0x22, //88/ --> x
	0x00, 0x06, 0x48, 0x48, 0x48, 0x3E, //89/ --> y
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, //90/ --> z
	0x00, 0x08, 0x36, 0x41, 0x00, 0x00, //91/ --> {
	0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, //92/ --> |
	0x00, 0x41, 0x36, 0x08, 0x00, 0x00, //93/ --> }
	0x00, 0x08, 0x08, 0x2A, 0x1C, 0x08, //94/ --> ~
	0x00, 0x7E, 0x11, 0x11, 0x11, 0x7E, //95/ --> �
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x33, //96/ --> �
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, //97/ --> �
	0x00, 0x7F, 0x01, 0x01, 0x01, 0x03, //98/ --> �
	0x00, 0xE0, 0x51, 0x4F, 0x41, 0xFF, //99/ --> �
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, //100/ --> �
	0x00, 0x77, 0x08, 0x7F, 0x08, 0x77, //101/ --> �
	0x00, 0x41, 0x49, 0x49, 0x49, 0x36, //102/ --> �
	0x00, 0x7F, 0x10, 0x08, 0x04, 0x7F, //103/ --> �
	0x00, 0x7C, 0x21, 0x12, 0x09, 0x7C, //104/ --> �
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, //105/ --> �
	0x00, 0x20, 0x41, 0x3F, 0x01, 0x7F, //106/ --> �
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, //107/ --> �
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, //108/ --> �
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, //109/ --> �
	0x00, 0x7F, 0x01, 0x01, 0x01, 0x7F, //110/ --> �
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, //111/ --> �
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, //112/ --> �
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, //113/ --> �
	0x00, 0x47, 0x28, 0x10, 0x08, 0x07, //114/ --> �
	0x00, 0x1C, 0x22, 0x7F, 0x22, 0x1C, //115/ --> �
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63, //116/ --> �
	0x00, 0x7F, 0x40, 0x40, 0x40, 0xFF, //117/ --> �
	0x00, 0x07, 0x08, 0x08, 0x08, 0x7F, //118/ --> �
	0x00, 0x7F, 0x40, 0x7F, 0x40, 0x7F, //119/ --> �
	0x00, 0x7F, 0x40, 0x7F, 0x40, 0xFF, //120/ --> �
	0x00, 0x01, 0x7F, 0x48, 0x48, 0x30, //121/ --> �
	0x00, 0x7F, 0x48, 0x30, 0x00, 0x7F, //122/ --> �
	0x00, 0x00, 0x7F, 0x48, 0x48, 0x30, //123/ --> �
	0x00, 0x22, 0x41, 0x49, 0x49, 0x3E, //124/ --> �
	0x00, 0x7F, 0x08, 0x3E, 0x41, 0x3E, //125/ --> �
	0x00, 0x46, 0x29, 0x19, 0x09, 0x7f, //126/ --> �
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78, //127/ --> a
	0x00, 0x3c, 0x4a, 0x4a, 0x49, 0x31, //128/ --> �
	0x00, 0x7c, 0x54, 0x54, 0x28, 0x00, //129/ --> �
	0x00, 0x7c, 0x04, 0x04, 0x04, 0x0c, //130/ --> �
	0x00, 0xe0, 0x54, 0x4c, 0x44, 0xfc, //131/ --> �
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18, //132/ --> �
	0x00, 0x6c, 0x10, 0x7c, 0x10, 0x6c, //133/ --> �
	0x00, 0x44, 0x44, 0x54, 0x54, 0x28, //134/ --> �
	0x00, 0x7c, 0x20, 0x10, 0x08, 0x7c, //135/ --> �
	0x00, 0x7c, 0x41, 0x22, 0x11, 0x7c, //136/ --> �
	0x00, 0x7c, 0x10, 0x28, 0x44, 0x00, //137/ --> �
	0x00, 0x20, 0x44, 0x3c, 0x04, 0x7c, //138/ --> �
	0x00, 0x7c, 0x08, 0x10, 0x08, 0x7c, //139/ --> �
	0x00, 0x7c, 0x10, 0x10, 0x10, 0x7c, //140/ --> �
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38, //141/ --> �
	0x00, 0x7c, 0x04, 0x04, 0x04, 0x7c, //142/ --> �
	0x00, 0x7C, 0x14, 0x14, 0x14, 0x08, //143/ --> �
	0x00, 0x38, 0x44, 0x44, 0x44, 0x28, //144/ --> �
	0x00, 0x04, 0x04, 0x7c, 0x04, 0x04, //145/ --> �
	0x00, 0x0C, 0x50, 0x50, 0x50, 0x3C, //146/ --> �
	0x00, 0x30, 0x48, 0xfc, 0x48, 0x30, //147/ --> �
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44, //148/ --> �
	0x00, 0x7c, 0x40, 0x40, 0x40, 0xfc, //149/ --> �
	0x00, 0x0c, 0x10, 0x10, 0x10, 0x7c, //150/ --> �
	0x00, 0x7c, 0x40, 0x7c, 0x40, 0x7c, //151/ --> �
	0x00, 0x7c, 0x40, 0x7c, 0x40, 0xfc, //152/ --> �
	0x00, 0x04, 0x7c, 0x50, 0x50, 0x20, //153/ --> �
	0x00, 0x7c, 0x50, 0x50, 0x20, 0x7c, //154/ --> �
	0x00, 0x7c, 0x50, 0x50, 0x20, 0x00, //155/ --> �
	0x00, 0x28, 0x44, 0x54, 0x54, 0x38, //156/ --> �
	0x00, 0x7c, 0x10, 0x38, 0x44, 0x38, //157/ --> �
	0x00, 0x08, 0x54, 0x34, 0x14, 0x7c, //158/ --> �
	0x00, 0x7E, 0x4B, 0x4A, 0x4B, 0x42, //159/ --> �
	0x00, 0x38, 0x55, 0x54, 0x55, 0x18, //160/ --> �
	0x00, 0x00, 0x06, 0x09, 0x09, 0x06, //161/ --> �
};*/
/*----------�������������--------------------*/
void LCD_12864_ini(void)
{
	_delay_ms(40);
	LCD_12864_send_command(0xC);//display on
	_delay_us(100);
	clear_LCD_12864();
	LCD_12864_send_command(6);//������ ���������� ������
	_delay_ms(10);
}
/*----------��������� ������������ ������--------------------*/
void LCD_12864_GrapnicMode(uint8_t enable)   // 1-enable, 0-disable
{
	if (enable) 
	{
		LCD_12864_send_command(0x34); //��������� � extended instruction
		_delay_ms(1);	
	    LCD_12864_send_command(0x36); //��� ������. �����
		_delay_ms(1);	
	}
	else
	{
		LCD_12864_send_command(0x30); //��������� � basic instruction
		_delay_ms(1);
	}
}
/*----------����� ����������� �� ����� �������--------------------*/
void LCD_12864_Draw_bitmap(const unsigned char *bitmap) {
	/// ������� ������ ����������� �� �������
	/// �������� � ������� ST7920.
	/// \param *bitmap - ����������� 128*64. �.�. ����� �� 1024 ���������.
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
/*----------��������� �������--------------------*/
void LCD_1286_Draw_pixel(uint8_t x, uint8_t y) {
	/// ������� ��������� �����.
	/// param\ x - ���������� �� X(�� 0 �� 127)
	/// paran\ y - ���������� �� Y(�� 0 �� 63)
	if ((y < ST7920_height) && (x < ST7920_width)) {
		Frame_buffer[(x) + ((y / 8) * 128)] |= 0x01 << y % 8;
	}
}
/*----------�������--------------------*/
void clear_LCD_12864(void)
{
	LCD_12864_send_command(0x1);//clear
	_delay_ms(10);
}
/*----------���������������� ����������� ������--------------------*/
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
/*----------����� ����������� ������ �������--------------------*/
void str_LCD_12864 (char *str1)
{
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	LCD_12864_send_data(str1[n]);
}
/*----------�������� ������--------------------*/
void LCD_12864_send_data(uint8_t data)
{
	PORTD |= (1<<RS);
    //�������� 5 ������
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
	//�������� 4 �����
	PORTD &= ~(1<<RW);
	strob();
	strob();
	strob();
	strob();
	
	PORTD &= ~(1<<RS);
}
/*----------�������� �������--------------------*/
void LCD_12864_send_command(uint8_t command)
{
	PORTD |= (1<<RS);
    //�������� 5 ������
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
	//�������� 4 �����
	PORTD &= ~(1<<RW);
	strob();
	strob();
	strob();
	strob();
	
	PORTD &= ~(1<<RS);
}
/*----------�������� �������--------------------*/
void strob(void)
{
	_delay_us(1);
	PORTD |= (1<<E);
	_delay_us(1);
	PORTD &= ~(1<<E);
	_delay_us(1);
}
/*---------------------������� ������ ������� 5*7 �� �������-----------------------------*/
void LCD_12864_print_symbol(uint16_t x, uint16_t symbol, uint8_t inversion) {
	/// ������� ������ ������� �� �������
	/// \param x ��������� �� � (�� 0 �� 1023)
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	/// \param symbol - ��� �������
	/// \param inversion - ��������. 1 - ���, 0 - ����.
	for (int i = 0; i <= 6; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 6) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 6) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
}
/*---------------------������� ������ ������� 4*6 �� �������-----------------------------*/
void LCD_12864_print_symbol_4_6(uint16_t x, uint16_t symbol, uint8_t inversion) {
	/// ������� ������ ������� �� �������
	/// \param x ��������� �� � (�� 0 �� 1023)
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	/// \param symbol - ��� �������
	/// \param inversion - ��������. 1 - ���, 0 - ����.
	for (int i = 0; i <= 3; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 4) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 4) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
}
/*---------------------������� ������ ������� 11*16 ��� ����������� �������-----------------------------*/
void LCD_12864_print_symbol_11_16(uint16_t x, uint16_t symbol, uint8_t inversion) {
	/// ������� ������ ������� �� �������
	/// \param x ��������� �� � (�� 0 �� 1023)
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	/// \param symbol - ��� �������
	/// \param inversion - ��������. 1 - ���, 0 - ����.
	for (int i = 0; i <= 10; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 22) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 22) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
	x += 117;
	for (int i = 11; i <= 21; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 22) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 22) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
}
/*---------------------������� ������ ������� 7*11 -----------------------------*/
void LCD_12864_print_symbol_7_11(uint16_t x, uint16_t symbol, uint8_t inversion) {
	/// ������� ������ ������� �� �������
	/// \param x ��������� �� � (�� 0 �� 1023)
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	/// \param symbol - ��� �������
	/// \param inversion - ��������. 1 - ���, 0 - ����.
	for (int i = 0; i <= 6; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 14) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 14) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
	x += 121;
	for (int i = 7; i <= 13; i++) {
		if (inversion) {
			Frame_buffer[i + x - 1] = ~read_symbol_from_SD ((symbol * 14) + i);
			//Frame_buffer[i + x - 1] = ~Font[(symbol * 6) + i];
			} else {
			Frame_buffer[i + x - 1] = read_symbol_from_SD ((symbol * 14) + i);
			//Frame_buffer[i + x - 1] = Font[(symbol * 6) + i];
		}
	}
}
/*---------------------������� ������ ������ 7*11-----------------------------*/
void LCD_12864_Print_7_11(uint16_t x, uint8_t y, uint8_t inversion, char *tx_buffer) {
	/// ������� ������������� UTF-8 � ����� �������� � ����������� ��������� � ����� �����
	/// \param x - ���������� �� �. �� 0 �� 127
	/// \param y - ���������� �� y. �� 0 �� 7
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	
	//�������� ������ � �������� �������� ��� ���������� ������� �������
	FATFS fs;
	asm("nop");
	pf_mount(&fs); //��������� FAT
	pf_open("/7_11.txt");
	
	x = x + y * 128;
	uint16_t symbol = 0;
	for (int i = 0; i < strlen(tx_buffer); i++)
	{
		symbol = tx_buffer[i];
		if (inversion)
		{
			if(symbol != 46) LCD_12864_print_symbol_7_11(x, symbol - 48, 1);
			else LCD_12864_print_symbol_7_11(x, 10, 1);
		}
		else
		{
			if(symbol != 46) LCD_12864_print_symbol_7_11(x, symbol - 48, 0);
			else LCD_12864_print_symbol_7_11(x, 10, 0);
		}
		x = x + 8;
	}
	// ��������� ������ � ������
	pf_mount(0x00);
}
/*---------------------������� ������ ������ 4*6-----------------------------*/
void LCD_12864_Print_4_6(uint16_t x, uint8_t y, uint8_t inversion, char *tx_buffer) {
	/// ������� ������������� UTF-8 � ����� �������� � ����������� ��������� � ����� �����
	/// \param x - ���������� �� �. �� 0 �� 127
	/// \param y - ���������� �� y. �� 0 �� 7
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	
	//�������� ������ � �������� �������� ��� ���������� ������� �������
	FATFS fs;
	asm("nop");
	pf_mount(&fs); //��������� FAT
	pf_open("/4_6.txt");
	
	x = x + y * 128;
	uint16_t symbol = 0;
	for (int i = 0; i < strlen(tx_buffer); i++)
	{
		symbol = tx_buffer[i];
		if (inversion)
		{
			if(symbol != 46) LCD_12864_print_symbol_4_6(x, symbol - 48, 1);
			else LCD_12864_print_symbol_4_6(x, 10, 1);
		}
		else
		{
			if(symbol != 46) LCD_12864_print_symbol_4_6(x, symbol - 48, 0);
			else LCD_12864_print_symbol_4_6(x, 10, 0);
		}
		x = x + 5;
	}
	// ��������� ������ � ������
	pf_mount(0x00);
}
/*---------------------������� ������ ������ 11*16-----------------------------*/
void LCD_12864_Print_11_16(uint16_t x, uint8_t y, uint8_t inversion, char *tx_buffer) {
	/// ������� ������������� UTF-8 � ����� �������� � ����������� ��������� � ����� �����
	/// \param x - ���������� �� �. �� 0 �� 127
	/// \param y - ���������� �� y. �� 0 �� 7
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	
	//�������� ������ � �������� �������� ��� ���������� ������� �������
	FATFS fs;
	asm("nop");
	pf_mount(&fs); //��������� FAT
	pf_open("/Cloc.txt");
	
	x = x + y * 128;
	uint16_t symbol = 0;
	for (int i = 0; i < strlen(tx_buffer); i++)
	{
			symbol = tx_buffer[i];
			if (inversion)
			{
				LCD_12864_print_symbol_11_16(x, symbol - 48, 1); 
			}
			else
			{
				LCD_12864_print_symbol_11_16(x, symbol - 48, 0); 
			}
			x = x + 12;
	}
	// ��������� ������ � ������
	pf_mount(0x00);
}
/*----------------������� ������������� UTF-8 � ����� �������� 5*7-----------------*/
void LCD_12864_Decode_UTF8(uint16_t x, uint8_t y, uint8_t inversion, char *tx_buffer) {
	/// ������� ������������� UTF-8 � ����� �������� � ����������� ��������� � ����� �����
	/// \param x - ���������� �� �. �� 0 �� 127
	/// \param y - ���������� �� y. �� 0 �� 7
	/// ������� ������� �� ���������(������ �� 8 ��������)
	/// 1 ������: x = 0;
	///	2 ������: x = 128;
	/// 3 ������: x = 256;
	/// 4 ������: x = 384;
	/// 5 ������: x = 512;
	/// 6 ������: x = 640;
	/// 7 ������: x = 786;
	/// 8 ������: x = 896;
	
	//�������� ������ � �������� �������� ��� ���������� ������� �������
	FATFS fs;
	asm("nop");
	pf_mount(&fs); //��������� FAT
	pf_open("/Font.txt");
	
	x = x + y * 128;
	uint16_t symbol = 0;
	for (int i = 0; i < strlen(tx_buffer); i++) 
	{
		if ((tx_buffer[i] < 192)&&(tx_buffer[i]!=168)&&(tx_buffer[i]!=184)&&(tx_buffer[i]!=176)) 
		{   //���������� ����� � �������. ���� �� �������� ������, �� [i] <0xD0. �� � font �������� ���� "�" 
			symbol = tx_buffer[i];
			if (inversion) 
			{
				LCD_12864_print_symbol(x, symbol - 32, 1); //������� UTF-8. Basic Latin. � "������" �� "z". �������� ���.
			} 
			else 
			{
				LCD_12864_print_symbol(x, symbol - 32, 0); //������� UTF-8. Basic Latin. � "������" �� "z". �������� ����.
			}
			x = x + 6;			
		}
		else 
		{ //������� �����
			symbol = tx_buffer[i];
			if ((symbol <= 255) && (symbol >= 192)) 
			{
				if (inversion) 
				{
					LCD_12864_print_symbol(x, symbol - 97, 1); //������� UTF-8. ���������. � ����� "�" �� "�". �������� ���.
				} 
				else 
				{
					LCD_12864_print_symbol(x, symbol - 97, 0); //������� UTF-8. ���������. � ����� "�" �� "�". �������� ����.
				}
				x = x + 6;
			} 			
			if (symbol == 168) 
			{
				if (inversion) 
				{
					LCD_12864_print_symbol(x, 159, 1); ////������� UTF-8. ���������. ����� "�". �������� ���.
				} 
				else 
				{
					LCD_12864_print_symbol(x, 159, 0); ////������� UTF-8. ���������. ����� "�". �������� ����.
				}
				x = x + 6;
			} 
		    if (symbol == 184) 
			{
				if (inversion) 
				{
					LCD_12864_print_symbol(x, 160, 1); ////������� UTF-8. ���������. ����� "�". �������� ���.
				} else 
				{
					LCD_12864_print_symbol(x, 160, 0); ////������� UTF-8. ���������. ����� "�". �������� ����.
				}
				x = x + 6;
			} 
			if (symbol == 176) 
			{
				if (inversion)
			    {
					LCD_12864_print_symbol(x, 161, 1); ////������� UTF-8. Basic Latin. ������ "�". �������� ���.
				} 
				else 
				{
					LCD_12864_print_symbol(x, 161, 0); ////������� UTF-8. Basic Latin. ������ "�". �������� ����.
				}
				x = x + 6;
			}

		}
	}
	// ��������� ������ � ������
	pf_mount(0x00);
}
/*---------------------������� �������� ������ ����� � ������------------------*/
void LCD_12864_Inversion(uint16_t x_start, uint16_t x_end) {
	/// ������� �������� ������ ����� � ������
	/// \param x_start - ��������� ����� �� � �� 0 �� 1024
	/// \param x_end - �������� ����� �� y �� 0 �� 1024
	for (; x_start < x_end; x_start++) {
		Frame_buffer[x_start] = ~(Frame_buffer[x_start]);
	}
}
/*---------------������� ������� ������� � ����������� ������--------------------*/
void LCD_12864_Clean() {
	/// ������� ������� ������� � ����������� ������
	uint8_t x, y;
	for (y = 0; y < 64; y++) {
		if (y < 32) {
			LCD_12864_send_command(0x80 | y);
			LCD_12864_send_command(0x80);
			} else {
			LCD_12864_send_command(0x80 | (y - 32));
			LCD_12864_send_command(0x88);
		}
		for (x = 0; x < 8; x++) {
			LCD_12864_send_data(0x00);
			LCD_12864_send_data(0x00);
		}
	}
	LCD_12864_Clean_Frame_buffer();
}
/*------------------------������� ������� ������ �����-------------------------*/
void LCD_12864_Clean_Frame_buffer(void) {
	/// ������� ������� ������ �����
	memset(Frame_buffer, 0x00, sizeof(Frame_buffer));
}
/*----------��������� �������--------------------*/
/*-----------------------------------------------*/
/*----------�����--------------------*/
void LCD_12864_Draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end) {
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
/*----------���������� �������������--------------------*/
void LCD_12864_Draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	/// ������� ���������� �������������
	/// \param x - ��������� ����� �� ��� "x"
	/// \param y - ��������� ����� �� ��� "y"
	/// \param width - ������ ��������������
	/// \param height - ������ ��������������

	/*�������� ������ � ������*/
	if ((x + width) >= ST7920_width) {
		width = ST7920_width - x;
	}
	if ((y + height) >= ST7920_height) {
		height = ST7920_height - y;
	}

	/*������ �����*/
	LCD_12864_Draw_line(x, y, x + width, y); /*���� ��������������*/
	LCD_12864_Draw_line(x, y + height, x + width, y + height); /*��� ��������������*/
	LCD_12864_Draw_line(x, y, x, y + height); /*����� ������� ��������������*/
	LCD_12864_Draw_line(x + width, y, x + width, y + height); /*������ ������� ��������������*/
}
/*-------------------------------������� ����������� �������������---------------------------------*/
void LCD_12864_Draw_rectangle_filled(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	/// ������� ����������� �������������
	/// \param x - ��������� ����� �� ��� "x"
	/// \param y - ��������� ����� �� ��� "y"
	/// \param width - ������ ��������������
	/// \param height - ������ ��������������

	/*�������� ������ � ������*/
	if ((x + width) >= ST7920_width) {
		width = ST7920_width - x;
	}
	if ((y + height) >= ST7920_height) {
		height = ST7920_height - y;
	}

	/*������ �����*/
	for (uint8_t i = 0; i <= height; i++) {
		LCD_12864_Draw_line(x, y + i, x + width, y + i);
	}
}