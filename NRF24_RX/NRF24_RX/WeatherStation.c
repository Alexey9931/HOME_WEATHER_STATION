/*
 * WeatherStation.c
 *
 * Created: 03.06.2022 19:15:57
 *  Author: Alex2
 */ 
#include "WeatherStation.h"

unsigned char sec,min,hour,day,date,month,year,alarmhour,alarmmin;
extern char temp_street[10];
extern char hum_street[10];
extern char Vbat[10];
extern char adc_value1[10];
extern char WIND_speed[10];
extern char HALL_counter[10];
char TIME[10];
char hours[4];
char minutes[4];
char seconds[4];
char weakday[4];
char mounthday[4];
char Mounth[6];

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
	LCD_12864_Clean();
	LCD_12864_GrapnicMode(0);
}
//Главное окно
void Print_Home_Page(uint8_t *Frame_buffer)
{
	NRF24L01_Receive();
	LCD_12864_GrapnicMode(1);
	//-----------Вывод времени/даты-------------------------------//
	Clock();
	sprintf(TIME,"%s:%s",hours, minutes);
	LCD_12864_Print_11_16(1, 0, 0, TIME);
	LCD_12864_Decode_UTF8(59, 1, 0, seconds);
	LCD_12864_Decode_UTF8(73, 0, 0, "День");
	LCD_12864_Decode_UTF8(99, 0, 0, "Месяц");
	LCD_12864_Decode_UTF8(73, 1, 0, mounthday);
	LCD_12864_Decode_UTF8(85, 1, 0, weakday);
	LCD_12864_Decode_UTF8(99, 1, 0, Mounth);
	
	//-----------Вывод уличных показателей-----------------------//
	LCD_12864_Decode_UTF8(30, 4, 0, "°C");
	LCD_12864_Decode_UTF8(58, 4, 0, "%");
	LCD_12864_Print_7_11(1, 3, 0, "31.0");
	LCD_12864_Print_7_11(43, 3, 0, "49");
	//sprintf(Vbat,"%.2fВ",V_BAT(adc_value1));
	//LCD_12864_Decode_UTF8(38, 7, 0, Vbat);
	LCD_12864_Print_4_6(44, 2, 0, "3.83");
	//sprintf(WIND_speed,"%.2fм|с", wind_speed (HALL_counter));
	//LCD_12864_Decode_UTF8(32, 5, 0, WIND_speed);

	//-----------Вывод показателей в доме-----------------------//
	LCD_12864_Decode_UTF8(95, 4, 0, "°C");
	LCD_12864_Print_7_11(66, 3, 0, "30.0");
	LCD_12864_Decode_UTF8(123, 4, 0, "%");
	LCD_12864_Print_7_11(108, 3, 0, "40");
	LCD_12864_Decode_UTF8(67, 5, 0, "750мм.Hg");
	//-----------Вывод разделительных линий-----------------------//
	LCD_12864_Decode_UTF8(0, 2, 0, "улица");
	LCD_12864_Decode_UTF8(65, 2, 0, "дом");
	LCD_12864_Draw_line(0, 16, 128, 16);
	LCD_12864_Draw_line(71, 0, 71, 15);
	LCD_12864_Draw_line(97, 0, 97, 15);
	LCD_12864_Draw_line(0, 24, 30, 24);
	LCD_12864_Draw_line(30, 17, 30, 24);
	LCD_12864_Draw_line(64, 24, 83, 24);
	LCD_12864_Draw_line(83, 17, 83, 24);
	LCD_12864_Draw_line(63, 17, 63, 64);
	LCD_12864_Draw_line(64, 47, 128, 47);
	

	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
void Clock (void)
{		
	//Читаем время (для DS3231) - по сути функция RTC_read_time
	I2C_StartCondition();               // запуск i2c
	I2C_SendByte(0b11010000);			// передача адреса устройства, режим записи
	I2C_SendByte(0x00);				    // передача адреса памяти
	I2C_StopCondition();                // остановка i2c
	
	I2C_StartCondition();               // запуск i2c
	I2C_SendByte(0b11010001);			// передача адреса устройства, режим чтения
	sec = RTC_ConvertFromDec(I2C_ReadByte());     // чтение секунд, ACK
	min = RTC_ConvertFromDec(I2C_ReadByte());     // чтение минут, ACK
	hour = RTC_ConvertFromDec(I2C_ReadByte());    // чтение часов, ACK
	day = RTC_ConvertFromDec(I2C_ReadByte());     // чтение день недели, ACK
	date = RTC_ConvertFromDec(I2C_ReadByte());    // чтение число, ACK
	month = RTC_ConvertFromDec(I2C_ReadByte());   // чтение месяц, ACK
	year = RTC_ConvertFromDec(I2C_ReadLastByte());// чтение год, NACK
	I2C_StopCondition();                // остановка i2c
	
	if ((sec >= 0) && (sec <= 9)) {
		sprintf(seconds,"0%d",sec);
	}
	else {
		sprintf(seconds,"%d",sec);
	}
	if ((min >= 0) && (min <= 9)) {
		sprintf(minutes,"0%d",min);
	}
	else {
		sprintf(minutes,"%d",min);
	}
	if ((hour >= 0) && (hour <= 9)) {
		sprintf(hours,"0%d",hour);
	}
	else {
		sprintf(hours,"%d",hour);
	}
	if ((date >= 0) && (date <= 9)) {
		sprintf(mounthday,"0%d",date);
	}
	else {
		sprintf(mounthday,"%d",date);
	}
	switch (day)
	{
		case 1:
			sprintf(weakday,"Пн");
			break;
		case 2:
			sprintf(weakday,"Вт");
			break;
		case 3:
			sprintf(weakday,"Ср");
			break;
		case 4:
			sprintf(weakday,"Чт");
			break;
		case 5:
			sprintf(weakday,"Пт");
			break;
		case 6:
			sprintf(weakday,"Сб");
			break;
		case 7:
			sprintf(weakday,"Вс");
			break;
		default:
			break;
	}
	switch (month)
	{
		case 1:
		sprintf(Mounth,"Янв.");
		break;
		case 2:
		sprintf(Mounth,"Февр.");
		break;
		case 3:
		sprintf(Mounth,"Март");
		break;
		case 4:
		sprintf(Mounth,"Апр.");
		break;
		case 5:
		sprintf(Mounth,"Май");
		break;
		case 6:
		sprintf(Mounth,"Июнь");
		break;
		case 7:
		sprintf(Mounth,"Июль");
		break;
		case 8:
		sprintf(Mounth,"Авг.");
		break;
		case 9:
		sprintf(Mounth,"Сент.");
		break;
		case 10:
		sprintf(Mounth,"Окт.");
		break;
		case 11:
		sprintf(Mounth,"Нояб.");
		break;
		case 12:
		sprintf(Mounth,"Дек.");
		break;
		default:
		break;
	}
	
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