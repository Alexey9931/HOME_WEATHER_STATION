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
extern char Rain[10];
extern char adc_value2[10];
extern char wind_direction[10];
extern char TIME[10];
extern char hours[4];
extern char minutes[4];
extern char seconds[4];
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
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer();
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
	LCD_12864_Print_7_11(1, 3, 0, temp_street);
	LCD_12864_Print_7_11(43, 3, 0, hum_street);
	sprintf(Vbat,"%.2f",V_BAT(adc_value1));
	LCD_12864_Print_4_6(44, 2, 0, Vbat);
	//sprintf(Rain,"%.2f ",RAIN_AMOUNT(adc_value2));
	//LCD_12864_Decode_UTF8(32, 5, 0, Rain);
	sprintf(WIND_speed,"%.2f", wind_speed (HALL_counter));
	LCD_12864_Print_4_6(26, 5, 0, WIND_speed);
	LCD_12864_Decode_UTF8(45, 5, 0, "м/с");
	LCD_12864_Decode_UTF8(27, 6, 0, "осадки");
	LCD_12864_Draw_line(25, 52, 24, 52);
	LCD_12864_Draw_line(24, 52, 24, 59);
	LCD_12864_Draw_line(24, 59, 28, 59);
	LCD_1286_Draw_pixel(27, 58);
	LCD_1286_Draw_pixel(27, 60);
	LCD_1286_Draw_pixel(26, 57);
	LCD_1286_Draw_pixel(26, 61);
	if (RAIN_AMOUNT(adc_value2) >= 0.9f)  LCD_12864_Decode_UTF8(30, 7, 0, "нет");
	

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
	//-----------Вывод индикатора АКБ-----------------------//
	LCD_12864_Draw_line(34, 28, 40, 28);
	LCD_12864_Draw_line(34, 19, 34, 27);
	LCD_12864_Draw_line(40, 19, 40, 27);
	LCD_12864_Draw_line(34, 19, 36, 19);
	LCD_12864_Draw_line(38, 19, 40, 19);
	LCD_12864_Draw_line(36, 18, 36, 19);
	LCD_12864_Draw_line(38, 18, 38, 19);
	LCD_12864_Draw_line(36, 18, 38, 18);
	if (V_BAT(adc_value1) >= 4.0f) {
		LCD_12864_Draw_line(36, 26, 38, 26);
		LCD_12864_Draw_line(36, 25, 38, 25);
		LCD_12864_Draw_line(36, 24, 38, 24);
		LCD_12864_Draw_line(36, 23, 38, 23);
		LCD_12864_Draw_line(36, 22, 38, 22);
		LCD_12864_Draw_line(36, 21, 38, 21);
	}
	else if ((V_BAT(adc_value1) >= 3.9f) && (V_BAT(adc_value1) < 4.0f)) {
		LCD_12864_Draw_line(36, 26, 38, 26);
		LCD_12864_Draw_line(36, 25, 38, 25);
		LCD_12864_Draw_line(36, 24, 38, 24);
		LCD_12864_Draw_line(36, 23, 38, 23);
		LCD_12864_Draw_line(36, 22, 38, 22);
	}
	else if ((V_BAT(adc_value1) >= 3.8f) && (V_BAT(adc_value1) < 3.9f)) {
		LCD_12864_Draw_line(36, 26, 38, 26);
		LCD_12864_Draw_line(36, 25, 38, 25);
		LCD_12864_Draw_line(36, 24, 38, 24);
		LCD_12864_Draw_line(36, 23, 38, 23);
	}
	else if ((V_BAT(adc_value1) >= 3.7f) && (V_BAT(adc_value1) < 3.8f)) {
		LCD_12864_Draw_line(36, 26, 38, 26);
		LCD_12864_Draw_line(36, 25, 38, 25);
		LCD_12864_Draw_line(36, 24, 38, 24);
	}
	else if ((V_BAT(adc_value1) >= 3.6f) && (V_BAT(adc_value1) < 3.7f)) {
		LCD_12864_Draw_line(36, 26, 38, 26);
		LCD_12864_Draw_line(36, 25, 38, 25);
	}
	else if ((V_BAT(adc_value1) >= 3.5f) && (V_BAT(adc_value1) < 3.6f)) {
		LCD_12864_Draw_line(36, 26, 38, 26);
	}
	else {}
	//-----------Вывод индикатора флюгера-----------------------//
	LCD_12864_Draw_circle(11, 52, 9);
	//---------N-----------------
	LCD_1286_Clean_pixel(11, 44);
	LCD_1286_Clean_pixel(10, 44);
	LCD_1286_Clean_pixel(9, 44);
	LCD_1286_Clean_pixel(8, 44);
	LCD_1286_Clean_pixel(12, 44);
	LCD_1286_Clean_pixel(13, 44);
	LCD_1286_Clean_pixel(14, 44);
	LCD_1286_Draw_pixel(9, 43);
	LCD_1286_Draw_pixel(9, 44);
	LCD_1286_Draw_pixel(9, 45);
	LCD_1286_Draw_pixel(9, 42);
	LCD_1286_Draw_pixel(9, 41);
	LCD_1286_Draw_pixel(10, 42);
	LCD_1286_Draw_pixel(11, 43);
	LCD_1286_Draw_pixel(12, 44);
	LCD_1286_Draw_pixel(13, 43);
	LCD_1286_Draw_pixel(13, 44);
	LCD_1286_Draw_pixel(13, 45);
	LCD_1286_Draw_pixel(13, 42);
	LCD_1286_Draw_pixel(13, 41);
	//---------S-----------------
	LCD_1286_Clean_pixel(11, 61);
	LCD_1286_Clean_pixel(10, 61);
	LCD_1286_Clean_pixel(9, 61);
	LCD_1286_Clean_pixel(8, 61);
	LCD_1286_Clean_pixel(12, 61);
	LCD_1286_Clean_pixel(13, 61);
	LCD_1286_Clean_pixel(14, 61);
	LCD_1286_Draw_pixel(9, 60);
	LCD_1286_Draw_pixel(9, 63);
	LCD_1286_Draw_pixel(10, 61);
	LCD_1286_Draw_pixel(10, 59);
	LCD_1286_Draw_pixel(10, 63);
	LCD_1286_Draw_pixel(11, 61);
	LCD_1286_Draw_pixel(11, 59);
	LCD_1286_Draw_pixel(11, 63);
	LCD_1286_Draw_pixel(12, 61);
	LCD_1286_Draw_pixel(12, 59);
	LCD_1286_Draw_pixel(12, 63);
	LCD_1286_Draw_pixel(13, 62);
	LCD_1286_Draw_pixel(13, 59);
	//---------E-----------------
	LCD_1286_Clean_pixel(20, 52);
	LCD_1286_Clean_pixel(20, 53);
	LCD_1286_Clean_pixel(20, 54);
	LCD_1286_Clean_pixel(19, 55);
	LCD_1286_Draw_pixel(19, 48);
	LCD_1286_Clean_pixel(20, 51);
	LCD_1286_Clean_pixel(20, 50);
	LCD_1286_Draw_pixel(20, 52);
	LCD_1286_Draw_pixel(20, 50);
	LCD_1286_Draw_pixel(20, 54);
	LCD_1286_Draw_pixel(21, 52);
	LCD_1286_Draw_pixel(21, 50);
	LCD_1286_Draw_pixel(21, 54);
	LCD_1286_Draw_pixel(22, 52);
	LCD_1286_Draw_pixel(22, 50);
	LCD_1286_Draw_pixel(22, 54);
	LCD_1286_Draw_pixel(19, 52);
	LCD_1286_Draw_pixel(19, 50);
	LCD_1286_Draw_pixel(19, 54);
	LCD_1286_Draw_pixel(18, 52);
	LCD_1286_Draw_pixel(18, 53);
	LCD_1286_Draw_pixel(18, 54);
	LCD_1286_Draw_pixel(18, 51);
	LCD_1286_Draw_pixel(18, 50);
	//---------W-----------------
	LCD_1286_Clean_pixel(2, 52);
	LCD_1286_Clean_pixel(2, 53);
	LCD_1286_Clean_pixel(2, 54);
	LCD_1286_Clean_pixel(3, 55);
	LCD_1286_Draw_pixel(3, 48);
	LCD_1286_Clean_pixel(2, 51);
	LCD_1286_Clean_pixel(2, 50);
	LCD_1286_Draw_pixel(2, 52);
	LCD_1286_Draw_pixel(2, 53);
	LCD_1286_Draw_pixel(3, 54);
	LCD_1286_Draw_pixel(4, 52);
	LCD_1286_Draw_pixel(4, 53);
	LCD_1286_Draw_pixel(4, 51);
	LCD_1286_Draw_pixel(4, 50);
	LCD_1286_Draw_pixel(1, 54);
	LCD_1286_Draw_pixel(0, 52);
	LCD_1286_Draw_pixel(0, 53);
	LCD_1286_Draw_pixel(0, 51);
	LCD_1286_Draw_pixel(0, 50);
	//---------Стрелка-----------------
	//--точка в центре---
	LCD_1286_Draw_pixel(11, 52);	
	if (!strcmp(wind_direction, "N"))
	{
		LCD_1286_Draw_pixel(10, 53);
		LCD_1286_Draw_pixel(10, 54);
		LCD_1286_Draw_pixel(12, 53);
		LCD_1286_Draw_pixel(12, 54);
		LCD_1286_Draw_pixel(11, 51);
		LCD_1286_Draw_pixel(11, 50);
		LCD_1286_Draw_pixel(11, 49);
		LCD_1286_Draw_pixel(11, 48);
		LCD_1286_Draw_pixel(11, 47);
		LCD_1286_Draw_pixel(11, 46);
		LCD_1286_Draw_pixel(10, 47);
		LCD_1286_Draw_pixel(12, 47);
		LCD_1286_Draw_pixel(10, 48);
		LCD_1286_Draw_pixel(9, 48);
		LCD_1286_Draw_pixel(12, 48);
		LCD_1286_Draw_pixel(13, 48);
	}
	else if (!strcmp(wind_direction, "S"))
	{
		LCD_1286_Draw_pixel(10, 50);
		LCD_1286_Draw_pixel(10, 51);
		LCD_1286_Draw_pixel(12, 50);
		LCD_1286_Draw_pixel(12, 51);
		LCD_1286_Draw_pixel(11, 53);
		LCD_1286_Draw_pixel(11, 54);
		LCD_1286_Draw_pixel(11, 55);
		LCD_1286_Draw_pixel(11, 56);
		LCD_1286_Draw_pixel(11, 57);
		LCD_1286_Draw_pixel(11, 58);
		LCD_1286_Draw_pixel(10, 57);
		LCD_1286_Draw_pixel(12, 57);
		LCD_1286_Draw_pixel(10, 56);
		LCD_1286_Draw_pixel(9, 56);
		LCD_1286_Draw_pixel(12, 56);
		LCD_1286_Draw_pixel(13, 56);
	}
	else if (!strcmp(wind_direction, "E"))
	{
		LCD_1286_Draw_pixel(9, 51);
		LCD_1286_Draw_pixel(10, 51);
		LCD_1286_Draw_pixel(9, 53);
		LCD_1286_Draw_pixel(10, 53);
		LCD_1286_Draw_pixel(12, 52);
		LCD_1286_Draw_pixel(13, 52);
		LCD_1286_Draw_pixel(14, 52);
		LCD_1286_Draw_pixel(15, 52);
		LCD_1286_Draw_pixel(16, 52);
		LCD_1286_Draw_pixel(17, 52);
		LCD_1286_Draw_pixel(16, 51);
		LCD_1286_Draw_pixel(16, 53);
		LCD_1286_Draw_pixel(15, 53);
		LCD_1286_Draw_pixel(15, 54);
		LCD_1286_Draw_pixel(15, 51);
		LCD_1286_Draw_pixel(15, 50);
	}
	else if (!strcmp(wind_direction, "W"))
	{
		LCD_1286_Draw_pixel(13, 51);
		LCD_1286_Draw_pixel(12, 51);
		LCD_1286_Draw_pixel(13, 53);
		LCD_1286_Draw_pixel(12, 53);
		LCD_1286_Draw_pixel(10, 52);
		LCD_1286_Draw_pixel(9, 52);
		LCD_1286_Draw_pixel(8, 52);
		LCD_1286_Draw_pixel(7, 52);
		LCD_1286_Draw_pixel(6, 52);
		LCD_1286_Draw_pixel(5, 52);
		LCD_1286_Draw_pixel(6, 51);
		LCD_1286_Draw_pixel(6, 53);
		LCD_1286_Draw_pixel(7, 53);
		LCD_1286_Draw_pixel(7, 54);
		LCD_1286_Draw_pixel(7, 51);
		LCD_1286_Draw_pixel(7, 50);
	}
	else if (!strcmp(wind_direction, "N-E"))
	{
		LCD_1286_Draw_pixel(10, 51);
		LCD_1286_Draw_pixel(9, 52);
		LCD_1286_Draw_pixel(12, 53);
		LCD_1286_Draw_pixel(11, 54);
		LCD_12864_Draw_line(11, 52, 16, 47);
		LCD_1286_Draw_pixel(15, 47);
		LCD_1286_Draw_pixel(14, 47);
		LCD_1286_Draw_pixel(13, 47);
		LCD_1286_Draw_pixel(14, 48);
		LCD_1286_Draw_pixel(16, 48);
		LCD_1286_Draw_pixel(16, 49);
		LCD_1286_Draw_pixel(15, 49);
		LCD_1286_Draw_pixel(16, 50);
	}
	else if (!strcmp(wind_direction, "N-W"))
	{
		LCD_1286_Draw_pixel(12, 51);
		LCD_1286_Draw_pixel(13, 52);
		LCD_1286_Draw_pixel(10, 53);
		LCD_1286_Draw_pixel(11, 54);
		LCD_12864_Draw_line(11, 52, 6, 47);
		LCD_1286_Draw_pixel(7, 47);
		LCD_1286_Draw_pixel(8, 47);
		LCD_1286_Draw_pixel(9, 47);
		LCD_1286_Draw_pixel(8, 48);
		LCD_1286_Draw_pixel(6, 48);
		LCD_1286_Draw_pixel(6, 49);
		LCD_1286_Draw_pixel(6, 50);
		LCD_1286_Draw_pixel(7, 49);
	}
	else if (!strcmp(wind_direction, "S-E"))
	{
		LCD_1286_Draw_pixel(11, 50);
		LCD_1286_Draw_pixel(12, 51);
		LCD_1286_Draw_pixel(10, 53);
		LCD_1286_Draw_pixel(9, 52);
		LCD_12864_Draw_line(11, 52, 16, 57);
		LCD_1286_Draw_pixel(16, 56);
		LCD_1286_Draw_pixel(15, 57);
		LCD_1286_Draw_pixel(15, 55);
		LCD_1286_Draw_pixel(16, 55);
		LCD_1286_Draw_pixel(16, 54);
		LCD_1286_Draw_pixel(14, 56);
		LCD_1286_Draw_pixel(14, 57);
		LCD_1286_Draw_pixel(13, 57);
	}
	else if (!strcmp(wind_direction, "S-W"))
	{
		LCD_1286_Draw_pixel(11, 50);
		LCD_1286_Draw_pixel(10, 51);
		LCD_1286_Draw_pixel(13, 52);
		LCD_1286_Draw_pixel(12, 53);
		LCD_12864_Draw_line(11, 52, 6, 57);
		LCD_1286_Draw_pixel(6, 56);
		LCD_1286_Draw_pixel(6, 55);
		LCD_1286_Draw_pixel(7, 55);
		LCD_1286_Draw_pixel(6, 54);
		LCD_1286_Draw_pixel(7, 57);
		LCD_1286_Draw_pixel(8, 57);
		LCD_1286_Draw_pixel(8, 56);
		LCD_1286_Draw_pixel(9, 57);
	}
	else {}
	
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