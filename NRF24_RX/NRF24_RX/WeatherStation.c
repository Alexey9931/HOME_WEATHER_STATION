/*
 * WeatherStation.c
 *
 * Created: 03.06.2022 19:15:57
 *  Author: Alex2
 */ 
#include "WeatherStation.h"

#define RADIUS 0.09

char temp_street[5];
char hum_street[5];
char temp_home[5];
char hum_home[5];
char WIND_speed[5];
char wind_direction[6];
char Vbat[5];
char Rain[6];
char Press_home[6];
struct Time_Parameters {
	char hours[4];
	char minutes[4];
	char seconds[4];
	char weakday[4];
	char mounthday[4];
	char Mounth[4];
	char Year[4];
} T_Param;
//uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
extern unsigned char sec,min,hour,day,date,month,year,alarmhour,alarmmin;
extern char receive_time[20];
extern char adc_value1[6];
extern char HALL_counter[5];
extern char adc_value2[6];
uint8_t data[5] = {0};
int pressure_home = 0;
extern uint8_t change_flag;
extern int8_t cnt;
extern int8_t add_cnt;
extern uint8_t receive_counter;

//Окно приветсвия на экране дисплея
void Print_Hello_World()
{	
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	LCD_12864_GrapnicMode(1);
	LCD_12864_Print_jpeg(Frame_buffer);
	LCD_12864_Decode_UTF8(40, 0, 0, "ДОМАШНЯЯ", Frame_buffer);
	LCD_12864_Decode_UTF8(30, 7, 0, "МЕТЕОСТАНЦИЯ", Frame_buffer);
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//Окно загрузки
void Print_Download()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	LCD_12864_Draw_rectangle(6, 35, 112, 15, Frame_buffer);
	LCD_12864_Decode_UTF8(3, 1, 0, "Пожалуйста подождите.", Frame_buffer);
	LCD_12864_Decode_UTF8(16, 3, 0, "Идёт загрузка...", Frame_buffer);
	LCD_12864_Draw_bitmap(Frame_buffer);
	for(uint8_t i = 8; i <= 116 ; i = i + 11)
	{
		LCD_12864_Draw_rectangle_filled(i, 37, 9, 11, Frame_buffer);
		LCD_12864_Draw_bitmap(Frame_buffer);
		_delay_ms(500);
	}	
	LCD_12864_GrapnicMode(0);
}
//Главное окно
void Print_Home_Page()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	char TIME[10] = {0};
	
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	//-----------Вывод времени/даты-------------------------------//
	Clock();
	sprintf(TIME,"%s:%s",T_Param.hours, T_Param.minutes);
	LCD_12864_Print_11_16(2, 0, 0, TIME, Frame_buffer);
	LCD_12864_Decode_UTF8(63, 0, 0, T_Param.seconds, Frame_buffer);
	LCD_12864_Decode_UTF8(61, 1, 0, T_Param.weakday, Frame_buffer);
	LCD_12864_Decode_UTF8(73, 1, 0, ",", Frame_buffer);
	LCD_12864_Decode_UTF8(76, 1, 0, T_Param.mounthday, Frame_buffer);
	LCD_12864_Decode_UTF8(88, 1, 0, "/", Frame_buffer);
	LCD_12864_Decode_UTF8(93, 1, 0, T_Param.Mounth, Frame_buffer);
	LCD_12864_Decode_UTF8(111, 1, 0, "/", Frame_buffer);
	LCD_12864_Decode_UTF8(116, 1, 0, T_Param.Year, Frame_buffer);
	//-----------Вывод уровня приема сигнала----------------------//
	LCD_12864_Draw_line(82, 6, 82, 0, Frame_buffer);
	LCD_12864_Draw_line(79, 0, 85, 0, Frame_buffer);
	LCD_12864_Draw_pixel(80, 1, Frame_buffer);
	LCD_12864_Draw_pixel(81, 2, Frame_buffer);
	LCD_12864_Draw_pixel(82, 3, Frame_buffer);
	LCD_12864_Draw_pixel(84, 1, Frame_buffer);
	LCD_12864_Draw_pixel(83, 2, Frame_buffer);
	//if (receive_counter == 6)
	//{
		for (uint8_t k = 1; k < receive_counter+1; k++)
		{
			LCD_12864_Draw_line(82 + 2*k, 6, 82 + 2*k, 7-k, Frame_buffer);
		}
	//}
	//-----------Вывод уличных показателей-----------------------//
	//sprintf(Weath_Param.Rain,"%d",RAIN_AMOUNT(adc_value2));
	LCD_12864_Decode_UTF8(30, 4, 0, "°C", Frame_buffer);
	LCD_12864_Decode_UTF8(58, 4, 0, "%", Frame_buffer);
	LCD_12864_Print_7_11(43, 3, 0, hum_street, Frame_buffer);
	LCD_12864_Print_7_11(1, 3, 0, temp_street, Frame_buffer);
	//sprintf(Weath_Param.Vbat,"%d",V_BAT(adc_value1));
	LCD_12864_Print_4_6(44, 2, 0, Vbat, Frame_buffer);
	//sprintf(Weath_Param.WIND_speed,"%d", wind_speed (HALL_counter));
	LCD_12864_Print_4_6(26, 5, 0, WIND_speed, Frame_buffer);
	LCD_12864_Decode_UTF8(45, 5, 0, "м/с", Frame_buffer);
	LCD_12864_Decode_UTF8(30, 6, 0, "осадки", Frame_buffer);
	LCD_12864_Draw_line(27, 52, 24, 52, Frame_buffer);
	LCD_12864_Draw_line(24, 52, 24, 59, Frame_buffer);
	LCD_12864_Draw_line(24, 59, 28, 59, Frame_buffer);
	LCD_12864_Draw_pixel(27, 58, Frame_buffer);
	LCD_12864_Draw_pixel(27, 60, Frame_buffer);
	LCD_12864_Draw_pixel(26, 57, Frame_buffer);
	LCD_12864_Draw_pixel(26, 61, Frame_buffer);
	if (RAIN_AMOUNT(adc_value2) >= 90)  {LCD_12864_Decode_UTF8(30, 7, 0, "отсутств.", Frame_buffer);}
	else if ((RAIN_AMOUNT(adc_value2) < 90) && (RAIN_AMOUNT(adc_value2) >= 50))  {LCD_12864_Decode_UTF8(30, 7, 0, "слабые", Frame_buffer);}
    else if ((RAIN_AMOUNT(adc_value2) < 50) && (RAIN_AMOUNT(adc_value2) >= 25)) { LCD_12864_Decode_UTF8(30, 7, 0, "умеренные", Frame_buffer);}
	else if ((RAIN_AMOUNT(adc_value2) < 25) && (RAIN_AMOUNT(adc_value2) > 0))  {LCD_12864_Decode_UTF8(30, 7, 0, "сильные", Frame_buffer);}
	//-----------Вывод показателей в доме-----------------------//
	/*if (dht22_GetData(data))
	{
		 //data[1]-младший бит температуры
		 //data[2]-старший бит температуры
		 //data[3]-младший бит влажности
		 //data[4]-старший бит влажности
		 home_temp = ((data[2]<<8)|data[1]);
		 if (((data[2]<<8)|data[1]) & 0x8000) home_temp *= -1;
		 home_hum = ((data[4]<<8)|data[3]) / 10;
	}
	sprintf(Weath_Param.temp_home,"%d",home_temp);
	sprintf(Weath_Param.hum_home,"%d",home_hum);
	pressure_home = BMP180_calculation()*0.0075;
	sprintf(Weath_Param.Press_home,"%d",pressure_home);*/
	LCD_12864_Decode_UTF8(95, 4, 0, "°C", Frame_buffer);
	LCD_12864_Print_7_11(66, 3, 0, temp_home, Frame_buffer);
	LCD_12864_Decode_UTF8(123, 4, 0, "%", Frame_buffer);
	LCD_12864_Print_7_11(108, 3, 0, hum_home, Frame_buffer);
	LCD_12864_Print_4_6(86, 2, 0, Press_home, Frame_buffer);
	LCD_12864_Decode_UTF8(101, 2, 0, "мм", Frame_buffer);
	LCD_12864_Decode_UTF8(114, 2, 0, "Hg", Frame_buffer);
	
	//-----------Вывод разделительных линий-----------------------//
	LCD_12864_Decode_UTF8(2, 2, 0, "улица", Frame_buffer);
	LCD_12864_Decode_UTF8(65, 2, 0, "дом", Frame_buffer);
	LCD_12864_Draw_line(0, 16, 128, 16, Frame_buffer);
	LCD_12864_Draw_line(0, 24, 32, 24, Frame_buffer);
	LCD_12864_Draw_line(32, 17, 32, 24, Frame_buffer);
	LCD_12864_Draw_line(0, 17, 0, 24, Frame_buffer);
	LCD_12864_Draw_line(64, 24, 83, 24, Frame_buffer);
	LCD_12864_Draw_line(83, 17, 83, 24, Frame_buffer);
	LCD_12864_Draw_line(63, 17, 63, 41, Frame_buffer);
	LCD_12864_Draw_line(63, 41, 128, 41, Frame_buffer);
	//-----------Вывод индикатора АКБ-----------------------//
	DrawBattery(Frame_buffer);
	//-----------Вывод индикатора флюгера-----------------------//
	DrawWeatherVane(Frame_buffer);
	//-----------Вывод прогноза погоды-----------------------//
	if ((wind_speed (HALL_counter) == 0) && (RAIN_AMOUNT(adc_value2) >= 90))
	{
		DrawSun(Frame_buffer);
	}
	else if ((wind_speed (HALL_counter) > 1000))
	{
		DrawClouds(Frame_buffer);
	}
	else if ((wind_speed (HALL_counter) > 0) && (RAIN_AMOUNT(adc_value2) >= 90))
	{
		DrawSunWithClouds(Frame_buffer);
	}
	else if ((RAIN_AMOUNT(adc_value2) < 85) && (RAIN_AMOUNT(adc_value2) > 0))
	{
		DrawCloudsWithRain(Frame_buffer);
	}
	else
	{
		DrawSun(Frame_buffer);
	}
	
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//Окно меню
void Print_Menu_Page()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	LCD_12864_Decode_UTF8(30, 0, 1, "ГЛАВНОЕ МЕНЮ", Frame_buffer);
	switch (cnt%4)
	{
		case 0: LCD_12864_Decode_UTF8(15, 2, 1, "Главное инфо-окно", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 3, 0, "Настройка времени", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 4, 0, "Справка", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 5, 0, "Доп.инфо", Frame_buffer);
				break;
		case 1: LCD_12864_Decode_UTF8(15, 2, 0, "Главное инфо-окно", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 3, 1, "Настройка времени", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 4, 0, "Справка", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 5, 0, "Доп.инфо", Frame_buffer);
				break;
		case 2: LCD_12864_Decode_UTF8(15, 2, 0, "Главное инфо-окно", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 3, 0, "Настройка времени", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 4, 1, "Справка", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 5, 0, "Доп.инфо", Frame_buffer);
				break;
		case 3: LCD_12864_Decode_UTF8(15, 2, 0, "Главное инфо-окно", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 3, 0, "Настройка времени", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 4, 0, "Справка", Frame_buffer);
				LCD_12864_Decode_UTF8(15, 5, 1, "Доп.инфо", Frame_buffer);
				break;
	}
	
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//Окно настроек времени
void Print_Page_Clock_Settings()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	Convert_to_string_Clock();
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	
	LCD_12864_Decode_UTF8(15, 0, 1, "НАСТРОЙКА ВРЕМЕНИ", Frame_buffer);
	switch (cnt%7)
	{
		case 0:	if(change_flag)
				{
					hour = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 1, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;	
		case 1: if(change_flag)
				{
					min = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 1, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;
		case 2: if(change_flag)
				{
					day = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 1, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;
		case 3: if(change_flag)
				{
					date = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 1, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;
		case 4: if(change_flag)
				{
					month = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 1, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;
		case 5: if(change_flag)
				{
					year = add_cnt;
				}
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 1, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 0, "Назад в МЕНЮ", Frame_buffer);
				break;
		case 6:
				LCD_12864_Print_11_16(32, 2, 0, T_Param.hours, Frame_buffer);
				LCD_12864_Print_11_16(62, 2, 0, T_Param.minutes, Frame_buffer);
				LCD_12864_Decode_UTF8(28, 5, 0, T_Param.weakday, Frame_buffer);
				LCD_12864_Decode_UTF8(49, 5, 0, T_Param.mounthday, Frame_buffer);
				LCD_12864_Decode_UTF8(70, 5, 0, T_Param.Mounth, Frame_buffer);
				LCD_12864_Decode_UTF8(95, 5, 0, T_Param.Year, Frame_buffer);
				LCD_12864_Decode_UTF8(25, 7, 1, "Назад в МЕНЮ", Frame_buffer);
				break;
	}
	LCD_12864_Decode_UTF8(55, 3, 0, "ч", Frame_buffer);
	LCD_12864_Decode_UTF8(85, 3, 0, "мин", Frame_buffer);
	LCD_12864_Decode_UTF8(42, 5, 0, ",", Frame_buffer);
	LCD_12864_Decode_UTF8(63, 5, 0, "/", Frame_buffer);
	LCD_12864_Decode_UTF8(89, 5, 0, "/", Frame_buffer);

	
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//Окно справки
void Print_Page_About()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	
	LCD_12864_Decode_UTF8(25, 0, 1, "Об устройстве", Frame_buffer);
	LCD_12864_Decode_UTF8(2, 1, 0, "\"Домашняя метеостан-", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 2, 0, "ция (v.1.0)\"-предна-", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 3, 0, "значена для сбора и ", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 4, 0, "обработки информации ", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 5, 0, "о метео условиях за ", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 6, 0, "окном и в помещении.", Frame_buffer);
	LCD_12864_Decode_UTF8(25, 7, 1, "Назад в МЕНЮ", Frame_buffer);
	
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//Окно доп инфо
void Print_Page_Dop_Info()
{
	uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer(Frame_buffer);
	
	LCD_12864_Decode_UTF8(5, 0, 1, "Дополнительная инфо", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 1, 0, "Уличный передатчик:", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 2, 0, "время посл.приема:", Frame_buffer);
	LCD_12864_Decode_UTF8(0, 3, 0, receive_time, Frame_buffer);
	
	LCD_12864_Decode_UTF8(25, 7, 1, "Назад в МЕНЮ", Frame_buffer);
	
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
}
//-----------Графика вспомогательная для главного окна------//
void DrawSun(uint8_t *Frame_buffer)
{
	LCD_12864_Draw_circle_filled(110, 53, 5, Frame_buffer);
	LCD_12864_Draw_line(110, 45, 110, 43, Frame_buffer);
	LCD_12864_Draw_line(118, 53, 120, 53, Frame_buffer);
	LCD_12864_Draw_line(102, 53, 100, 53, Frame_buffer);
	LCD_12864_Draw_line(110, 61, 110, 63, Frame_buffer);
	LCD_12864_Draw_line(104, 48, 102, 46, Frame_buffer);
	LCD_12864_Draw_line(116, 48, 118, 46, Frame_buffer);
	LCD_12864_Draw_line(116, 58, 118, 60, Frame_buffer);
	LCD_12864_Draw_line(104, 58, 102, 60, Frame_buffer);
}
void DrawSunWithClouds(uint8_t *Frame_buffer)
{
	//солнце
	LCD_12864_Draw_circle(110, 53, 5, Frame_buffer);
	LCD_12864_Draw_line(110, 45, 110, 43, Frame_buffer);
	LCD_12864_Draw_line(118, 53, 120, 53, Frame_buffer);
	LCD_12864_Draw_line(110, 61, 110, 63, Frame_buffer);
	LCD_12864_Draw_line(116, 48, 118, 46, Frame_buffer);
	LCD_12864_Draw_line(116, 58, 118, 60, Frame_buffer);
	//облако
	LCD_12864_Draw_line(90, 57, 106, 57, Frame_buffer);
	LCD_12864_Draw_pixel(89, 56, Frame_buffer);
	LCD_12864_Draw_pixel(88, 55, Frame_buffer);
	LCD_12864_Draw_line(87, 52, 87, 54, Frame_buffer);
	/*LCD_12864_Draw_pixel(87, 54, Frame_buffer);
	LCD_12864_Draw_pixel(87, 53, Frame_buffer);
	LCD_12864_Draw_pixel(87, 52, Frame_buffer);*/
	LCD_12864_Draw_pixel(88, 51, Frame_buffer);
	LCD_12864_Draw_line(89, 50, 93, 50, Frame_buffer);
	/*LCD_12864_Draw_pixel(89, 50, Frame_buffer);
	LCD_12864_Draw_pixel(90, 50, Frame_buffer);
	LCD_12864_Draw_pixel(91, 50, Frame_buffer);
	LCD_12864_Draw_pixel(92, 50, Frame_buffer);
	LCD_12864_Draw_pixel(93, 50, Frame_buffer);*/
	LCD_12864_Draw_pixel(94, 51, Frame_buffer);
	LCD_12864_Draw_line(92, 46, 92, 49, Frame_buffer);
	/*LCD_12864_Draw_pixel(92, 49, Frame_buffer);
	LCD_12864_Draw_pixel(92, 48, Frame_buffer);
	LCD_12864_Draw_pixel(92, 47, Frame_buffer);
	LCD_12864_Draw_pixel(92, 46, Frame_buffer);*/
	LCD_12864_Draw_pixel(93, 45, Frame_buffer);
	LCD_12864_Draw_line(94, 44, 100, 44, Frame_buffer);
	/*LCD_12864_Draw_pixel(94, 44, Frame_buffer);
	LCD_12864_Draw_pixel(95, 44, Frame_buffer);
	LCD_12864_Draw_pixel(96, 44, Frame_buffer);
	LCD_12864_Draw_pixel(97, 44, Frame_buffer);
	LCD_12864_Draw_pixel(98, 44, Frame_buffer);
	LCD_12864_Draw_pixel(99, 44, Frame_buffer);
	LCD_12864_Draw_pixel(100, 44, Frame_buffer);*/
	
	LCD_12864_Draw_pixel(101, 45, Frame_buffer);
	LCD_12864_Draw_line(102, 46, 102, 48, Frame_buffer);
	/*LCD_12864_Draw_pixel(102, 46, Frame_buffer);
	LCD_12864_Draw_pixel(102, 47, Frame_buffer);
	LCD_12864_Draw_pixel(102, 48, Frame_buffer);*/
	LCD_12864_Draw_pixel(101, 49, Frame_buffer);
	LCD_12864_Draw_line(102, 48, 106, 48, Frame_buffer);
	/*LCD_12864_Draw_pixel(102, 48, Frame_buffer);
	LCD_12864_Draw_pixel(103, 48, Frame_buffer);
	LCD_12864_Draw_pixel(104, 48, Frame_buffer);
	LCD_12864_Draw_pixel(105, 48, Frame_buffer);
	LCD_12864_Draw_pixel(106, 48, Frame_buffer);*/
	
	LCD_12864_Draw_pixel(107, 56, Frame_buffer);
	LCD_12864_Draw_pixel(108, 55, Frame_buffer);
	LCD_12864_Draw_line(109, 51, 109, 54, Frame_buffer);
	/*LCD_12864_Draw_pixel(109, 54, Frame_buffer);
	LCD_12864_Draw_pixel(109, 53, Frame_buffer);
	LCD_12864_Draw_pixel(109, 52, Frame_buffer);
	LCD_12864_Draw_pixel(109, 51, Frame_buffer);*/
	LCD_12864_Draw_pixel(108, 50, Frame_buffer);
	LCD_12864_Draw_pixel(107, 49, Frame_buffer);
	//очистка куска солнца
	LCD_12864_Clean_pixel(106, 50, Frame_buffer);
	for(uint8_t i = 51; i <= 55;i++)
	{
		LCD_12864_Clean_pixel(105, i, Frame_buffer);
	}
	/*LCD_12864_Clean_pixel(105, 51, Frame_buffer);
	LCD_12864_Clean_pixel(105, 52, Frame_buffer);
	LCD_12864_Clean_pixel(105, 53, Frame_buffer);
	LCD_12864_Clean_pixel(105, 54, Frame_buffer);
	LCD_12864_Clean_pixel(105, 55, Frame_buffer);*/
	LCD_12864_Clean_pixel(106, 56, Frame_buffer);
	LCD_12864_Draw_pixel(106, 48, Frame_buffer);
	LCD_12864_Draw_pixel(105, 48, Frame_buffer);
	//закраска солнца
	for(uint8_t i = 0; i <= 4;i++)
	{
		LCD_12864_Draw_circle(110, 53, i, Frame_buffer);
	}
}
void DrawClouds(uint8_t *Frame_buffer)
{
	//облако№1
	LCD_12864_Draw_line(90, 57, 106, 57, Frame_buffer);
	LCD_12864_Draw_pixel(89, 56, Frame_buffer);
	LCD_12864_Draw_pixel(88, 55, Frame_buffer);
	LCD_12864_Draw_line(87, 52, 87, 54, Frame_buffer);
	/*LCD_12864_Draw_pixel(87, 54, Frame_buffer);
	LCD_12864_Draw_pixel(87, 53, Frame_buffer);
	LCD_12864_Draw_pixel(87, 52, Frame_buffer);*/
	LCD_12864_Draw_pixel(88, 51, Frame_buffer);
	LCD_12864_Draw_line(89, 50, 93, 50, Frame_buffer);
	/*LCD_12864_Draw_pixel(89, 50, Frame_buffer);
	LCD_12864_Draw_pixel(90, 50, Frame_buffer);
	LCD_12864_Draw_pixel(91, 50, Frame_buffer);
	LCD_12864_Draw_pixel(92, 50, Frame_buffer);
	LCD_12864_Draw_pixel(93, 50, Frame_buffer);*/
	LCD_12864_Draw_pixel(94, 51, Frame_buffer);
	LCD_12864_Draw_line(92, 46, 92, 49, Frame_buffer);
	/*LCD_12864_Draw_pixel(92, 49, Frame_buffer);
	LCD_12864_Draw_pixel(92, 48, Frame_buffer);
	LCD_12864_Draw_pixel(92, 47, Frame_buffer);
	LCD_12864_Draw_pixel(92, 46, Frame_buffer);*/
	LCD_12864_Draw_pixel(93, 45, Frame_buffer);
	LCD_12864_Draw_line(94, 44, 100, 44, Frame_buffer);
	/*LCD_12864_Draw_pixel(94, 44, Frame_buffer);
	LCD_12864_Draw_pixel(95, 44, Frame_buffer);
	LCD_12864_Draw_pixel(96, 44, Frame_buffer);
	LCD_12864_Draw_pixel(97, 44, Frame_buffer);
	LCD_12864_Draw_pixel(98, 44, Frame_buffer);
	LCD_12864_Draw_pixel(99, 44, Frame_buffer);
	LCD_12864_Draw_pixel(100, 44, Frame_buffer);*/
	LCD_12864_Draw_pixel(101, 45, Frame_buffer);
	LCD_12864_Draw_line(102, 46, 102, 48, Frame_buffer);
	/*LCD_12864_Draw_pixel(102, 46, Frame_buffer);
	LCD_12864_Draw_pixel(102, 47, Frame_buffer);
	LCD_12864_Draw_pixel(102, 48, Frame_buffer);*/
	LCD_12864_Draw_pixel(101, 49, Frame_buffer);
	LCD_12864_Draw_line(102, 48, 106, 48, Frame_buffer);
	/*LCD_12864_Draw_pixel(102, 48, Frame_buffer);
	LCD_12864_Draw_pixel(103, 48, Frame_buffer);
	LCD_12864_Draw_pixel(104, 48, Frame_buffer);
	LCD_12864_Draw_pixel(105, 48, Frame_buffer);
	LCD_12864_Draw_pixel(106, 48, Frame_buffer);*/
	LCD_12864_Draw_pixel(107, 56, Frame_buffer);
	LCD_12864_Draw_pixel(108, 55, Frame_buffer);
	LCD_12864_Draw_line(109, 51, 109, 54, Frame_buffer);
	/*LCD_12864_Draw_pixel(109, 54, Frame_buffer);
	LCD_12864_Draw_pixel(109, 53, Frame_buffer);
	LCD_12864_Draw_pixel(109, 52, Frame_buffer);
	LCD_12864_Draw_pixel(109, 51, Frame_buffer);*/
	LCD_12864_Draw_pixel(108, 50, Frame_buffer);
	LCD_12864_Draw_pixel(107, 49, Frame_buffer);
	//облако№2
	LCD_12864_Draw_line(110, 55, 121, 55, Frame_buffer);
	LCD_12864_Draw_line(122, 51, 122, 54, Frame_buffer);
	/*LCD_12864_Draw_pixel(122, 54, Frame_buffer);
	LCD_12864_Draw_pixel(122, 53, Frame_buffer);
	LCD_12864_Draw_pixel(122, 52, Frame_buffer);
	LCD_12864_Draw_pixel(122, 51, Frame_buffer);*/
	LCD_12864_Draw_pixel(121, 50, Frame_buffer);
	LCD_12864_Draw_line(118, 49, 120, 49, Frame_buffer);
	/*LCD_12864_Draw_pixel(120, 49, Frame_buffer);
	LCD_12864_Draw_pixel(119, 49, Frame_buffer);
	LCD_12864_Draw_pixel(118, 49, Frame_buffer);*/
	LCD_12864_Draw_pixel(117, 50, Frame_buffer);
	LCD_12864_Draw_line(118, 47, 118, 48, Frame_buffer);
	/*LCD_12864_Draw_pixel(118, 48, Frame_buffer);
	LCD_12864_Draw_pixel(118, 47, Frame_buffer);*/
	LCD_12864_Draw_line(114, 46, 117, 46, Frame_buffer);
	/*LCD_12864_Draw_pixel(117, 46, Frame_buffer);
	LCD_12864_Draw_pixel(116, 46, Frame_buffer);
	LCD_12864_Draw_pixel(115, 46, Frame_buffer);
	LCD_12864_Draw_pixel(114, 46, Frame_buffer);*/
	LCD_12864_Draw_line(113, 47, 113, 49, Frame_buffer);
	/*LCD_12864_Draw_pixel(113, 47, Frame_buffer);
	LCD_12864_Draw_pixel(113, 48, Frame_buffer);
	LCD_12864_Draw_pixel(113, 49, Frame_buffer);*/
	LCD_12864_Draw_pixel(114, 50, Frame_buffer);
	LCD_12864_Draw_line(111, 49, 112, 49, Frame_buffer);
	/*LCD_12864_Draw_pixel(112, 49, Frame_buffer);
	LCD_12864_Draw_pixel(111, 49, Frame_buffer);*/
	LCD_12864_Draw_pixel(110, 50, Frame_buffer);
}
void DrawCloudsWithRain(uint8_t *Frame_buffer)
{
	DrawClouds(Frame_buffer);

	LCD_12864_Draw_line(91, 59, 89, 61, Frame_buffer);
	LCD_12864_Draw_line(94, 59, 92, 61, Frame_buffer);
	LCD_12864_Draw_line(97, 59, 95, 61, Frame_buffer);
	LCD_12864_Draw_line(100, 59, 98, 61, Frame_buffer);
	LCD_12864_Draw_line(103, 59, 101, 61, Frame_buffer);
	LCD_12864_Draw_line(106, 59, 104, 61, Frame_buffer);
	
	LCD_12864_Draw_line(111, 57, 110, 58, Frame_buffer);
	LCD_12864_Draw_line(114, 57, 113, 58, Frame_buffer);
	LCD_12864_Draw_line(117, 57, 116, 58, Frame_buffer);
	LCD_12864_Draw_line(120, 57, 119, 58, Frame_buffer);
}
void DrawWeatherVane(uint8_t *Frame_buffer)
{
	uint8_t i = 0, k = 0;
	LCD_12864_Draw_circle(11, 52, 9, Frame_buffer);
	//вывод букв N S W E
	for(i = 8; i <= 14; i++)
	{
		LCD_12864_Clean_pixel(i, 44, Frame_buffer);
		LCD_12864_Clean_pixel(i, 61, Frame_buffer);
	}
	for(i = 41; i <= 45; i++)
	{
		LCD_12864_Draw_pixel(9, i, Frame_buffer);
		LCD_12864_Draw_pixel(13, i, Frame_buffer);
	}
	LCD_12864_Draw_pixel(10, 42, Frame_buffer);
	LCD_12864_Draw_pixel(11, 43, Frame_buffer);
	LCD_12864_Draw_pixel(12, 44, Frame_buffer);
	LCD_12864_Draw_pixel(9, 60, Frame_buffer);
	LCD_12864_Draw_pixel(9, 63, Frame_buffer);
	for (k = 10; k <= 12; k++)
	{
		for (i = 59; i <= 63; i += 2)
		{
			LCD_12864_Draw_pixel(k, i, Frame_buffer);
		}
	}
	LCD_12864_Draw_pixel(13, 62, Frame_buffer);
	LCD_12864_Draw_pixel(13, 59, Frame_buffer);
	for(i = 50; i <= 54; i++)
	{
		LCD_12864_Clean_pixel(20, i, Frame_buffer);
		LCD_12864_Draw_pixel(18, i, Frame_buffer);
		LCD_12864_Clean_pixel(2, i, Frame_buffer);
	}
	LCD_12864_Clean_pixel(19, 55, Frame_buffer);
	LCD_12864_Draw_pixel(19, 48, Frame_buffer);
	for (k = 19; k <= 22; k++)
	{
		for (i = 50; i <= 54; i += 2)
		{
			LCD_12864_Draw_pixel(k, i, Frame_buffer);
		}
	}
	LCD_12864_Clean_pixel(3, 55, Frame_buffer);
	LCD_12864_Draw_pixel(3, 48, Frame_buffer);
	LCD_12864_Draw_line(2, 52, 2, 53, Frame_buffer);
	/*LCD_12864_Draw_pixel(2, 52, Frame_buffer);
	LCD_12864_Draw_pixel(2, 53, Frame_buffer);*/
	LCD_12864_Draw_pixel(3, 54, Frame_buffer);
	for(i = 50; i <= 53; i++)
	{
		LCD_12864_Draw_pixel(4, i, Frame_buffer);
		LCD_12864_Draw_pixel(0, i, Frame_buffer);
	}
	LCD_12864_Draw_pixel(1, 54, Frame_buffer);
	//---------Стрелка-----------------
	//--точка в центре---
	LCD_12864_Draw_pixel(11, 52, Frame_buffer);
	if (!strcmp(wind_direction, "N"))
	{
		for(i = 46; i <= 51; i++)
		{
			LCD_12864_Draw_pixel(11, i, Frame_buffer);
		}
		LCD_12864_Draw_line(10, 53, 10, 54, Frame_buffer);
		/*LCD_12864_Draw_pixel(10, 53, Frame_buffer);
		LCD_12864_Draw_pixel(10, 54, Frame_buffer);*/
		LCD_12864_Draw_line(12, 53, 12, 54, Frame_buffer);
		/*LCD_12864_Draw_pixel(12, 53, Frame_buffer);
		LCD_12864_Draw_pixel(12, 54, Frame_buffer);*/
		/*LCD_12864_Draw_pixel(11, 51, Frame_buffer);
		LCD_12864_Draw_pixel(11, 50, Frame_buffer);
		LCD_12864_Draw_pixel(11, 49, Frame_buffer);
		LCD_12864_Draw_pixel(11, 48, Frame_buffer);
		LCD_12864_Draw_pixel(11, 47, Frame_buffer);
		LCD_12864_Draw_pixel(11, 46, Frame_buffer);*/
		LCD_12864_Draw_pixel(10, 47, Frame_buffer);
		LCD_12864_Draw_pixel(12, 47, Frame_buffer);
		LCD_12864_Draw_line(9, 48, 10, 48, Frame_buffer);
		LCD_12864_Draw_line(12, 48, 13, 48, Frame_buffer);
		/*LCD_12864_Draw_pixel(10, 48, Frame_buffer);
		LCD_12864_Draw_pixel(9, 48, Frame_buffer);
		LCD_12864_Draw_pixel(12, 48, Frame_buffer);
		LCD_12864_Draw_pixel(13, 48, Frame_buffer);*/
	}
	else if (!strcmp(wind_direction, "S"))
	{
		LCD_12864_Draw_line(10, 50, 10, 51, Frame_buffer);
		/*LCD_12864_Draw_pixel(10, 50, Frame_buffer);
		LCD_12864_Draw_pixel(10, 51, Frame_buffer);*/
		LCD_12864_Draw_line(12, 50, 12, 51, Frame_buffer);
		/*LCD_12864_Draw_pixel(12, 50, Frame_buffer);
		LCD_12864_Draw_pixel(12, 51, Frame_buffer);*/
		for(i = 53; i <= 58; i++)
		{
			LCD_12864_Draw_pixel(11, i, Frame_buffer);
		}
		/*LCD_12864_Draw_pixel(11, 53, Frame_buffer);
		LCD_12864_Draw_pixel(11, 54, Frame_buffer);
		LCD_12864_Draw_pixel(11, 55, Frame_buffer);
		LCD_12864_Draw_pixel(11, 56, Frame_buffer);
		LCD_12864_Draw_pixel(11, 57, Frame_buffer);
		LCD_12864_Draw_pixel(11, 58, Frame_buffer);*/
		LCD_12864_Draw_line(10, 56, 10, 57, Frame_buffer);
		//LCD_12864_Draw_pixel(10, 57, Frame_buffer);
		LCD_12864_Draw_pixel(12, 57, Frame_buffer);
		//LCD_12864_Draw_pixel(10, 56, Frame_buffer);
		LCD_12864_Draw_pixel(9, 56, Frame_buffer);
		LCD_12864_Draw_line(12, 56, 13, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(12, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(13, 56, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "E"))
	{
		LCD_12864_Draw_line(9, 51, 10, 51, Frame_buffer);
		LCD_12864_Draw_line(9, 53, 10, 53, Frame_buffer);
		/*LCD_12864_Draw_pixel(9, 51, Frame_buffer);
		LCD_12864_Draw_pixel(10, 51, Frame_buffer);
		LCD_12864_Draw_pixel(9, 53, Frame_buffer);
		LCD_12864_Draw_pixel(10, 53, Frame_buffer);*/
		for(i = 12; i <= 17; i++)
		{
			LCD_12864_Draw_pixel(i, 52, Frame_buffer);
		}
		/*LCD_12864_Draw_pixel(12, 52, Frame_buffer);
		LCD_12864_Draw_pixel(13, 52, Frame_buffer);
		LCD_12864_Draw_pixel(14, 52, Frame_buffer);
		LCD_12864_Draw_pixel(15, 52, Frame_buffer);
		LCD_12864_Draw_pixel(16, 52, Frame_buffer);
		LCD_12864_Draw_pixel(17, 52, Frame_buffer);*/
		LCD_12864_Draw_pixel(16, 51, Frame_buffer);
		LCD_12864_Draw_line(15, 53, 16, 53, Frame_buffer);
		//LCD_12864_Draw_pixel(16, 53, Frame_buffer);
		//LCD_12864_Draw_pixel(15, 53, Frame_buffer);
		LCD_12864_Draw_pixel(15, 54, Frame_buffer);
		LCD_12864_Draw_line(15, 50, 15, 51, Frame_buffer);
		//LCD_12864_Draw_pixel(15, 51, Frame_buffer);
		//LCD_12864_Draw_pixel(15, 50, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "W"))
	{
		LCD_12864_Draw_line(12, 51, 13, 51, Frame_buffer);
		LCD_12864_Draw_line(12, 53, 13, 53, Frame_buffer);
		/*LCD_12864_Draw_pixel(13, 51, Frame_buffer);
		LCD_12864_Draw_pixel(12, 51, Frame_buffer);
		LCD_12864_Draw_pixel(13, 53, Frame_buffer);
		LCD_12864_Draw_pixel(12, 53, Frame_buffer);*/
		for(i = 5; i <= 10; i++)
		{
			LCD_12864_Draw_pixel(i, 52, Frame_buffer);
		}
		/*LCD_12864_Draw_pixel(10, 52, Frame_buffer);
		LCD_12864_Draw_pixel(9, 52, Frame_buffer);
		LCD_12864_Draw_pixel(8, 52, Frame_buffer);
		LCD_12864_Draw_pixel(7, 52, Frame_buffer);
		LCD_12864_Draw_pixel(6, 52, Frame_buffer);
		LCD_12864_Draw_pixel(5, 52, Frame_buffer);*/
		LCD_12864_Draw_pixel(6, 51, Frame_buffer);
		LCD_12864_Draw_line(6, 53, 7, 53, Frame_buffer);
		//LCD_12864_Draw_pixel(6, 53, Frame_buffer);
		//LCD_12864_Draw_pixel(7, 53, Frame_buffer);
		LCD_12864_Draw_pixel(7, 54, Frame_buffer);
		LCD_12864_Draw_line(7, 50, 7, 51, Frame_buffer);
		//LCD_12864_Draw_pixel(7, 51, Frame_buffer);
		//LCD_12864_Draw_pixel(7, 50, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "N-E"))
	{
		LCD_12864_Draw_pixel(10, 51, Frame_buffer);
		LCD_12864_Draw_pixel(9, 52, Frame_buffer);
		LCD_12864_Draw_pixel(12, 53, Frame_buffer);
		LCD_12864_Draw_pixel(11, 54, Frame_buffer);
		LCD_12864_Draw_line(11, 52, 16, 47, Frame_buffer);
		LCD_12864_Draw_line(13, 47, 15, 47, Frame_buffer);
		/*LCD_12864_Draw_pixel(15, 47, Frame_buffer);
		LCD_12864_Draw_pixel(14, 47, Frame_buffer);
		LCD_12864_Draw_pixel(13, 47, Frame_buffer);*/
		LCD_12864_Draw_pixel(14, 48, Frame_buffer);
		LCD_12864_Draw_pixel(16, 48, Frame_buffer);
		LCD_12864_Draw_line(15, 49, 16, 49, Frame_buffer);
		//LCD_12864_Draw_pixel(16, 49, Frame_buffer);
		//LCD_12864_Draw_pixel(15, 49, Frame_buffer);
		LCD_12864_Draw_pixel(16, 50, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "N-W"))
	{
		LCD_12864_Draw_pixel(12, 51, Frame_buffer);
		LCD_12864_Draw_pixel(13, 52, Frame_buffer);
		LCD_12864_Draw_pixel(10, 53, Frame_buffer);
		LCD_12864_Draw_pixel(11, 54, Frame_buffer);
		LCD_12864_Draw_line(11, 52, 6, 47, Frame_buffer);
		LCD_12864_Draw_line(7, 47, 9, 47, Frame_buffer);
		/*LCD_12864_Draw_pixel(7, 47, Frame_buffer);
		LCD_12864_Draw_pixel(8, 47, Frame_buffer);
		LCD_12864_Draw_pixel(9, 47, Frame_buffer);*/
		LCD_12864_Draw_pixel(8, 48, Frame_buffer);
		LCD_12864_Draw_line(6, 48, 6, 50, Frame_buffer);
		/*LCD_12864_Draw_pixel(6, 48, Frame_buffer);
		LCD_12864_Draw_pixel(6, 49, Frame_buffer);
		LCD_12864_Draw_pixel(6, 50, Frame_buffer);*/
		LCD_12864_Draw_pixel(7, 49, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "S-E"))
	{
		LCD_12864_Draw_pixel(11, 50, Frame_buffer);
		LCD_12864_Draw_pixel(12, 51, Frame_buffer);
		LCD_12864_Draw_pixel(10, 53, Frame_buffer);
		LCD_12864_Draw_pixel(9, 52, Frame_buffer);
		LCD_12864_Draw_line(11, 52, 16, 57, Frame_buffer);
		//LCD_12864_Draw_pixel(16, 56, Frame_buffer);
		LCD_12864_Draw_pixel(15, 57, Frame_buffer);
		LCD_12864_Draw_pixel(15, 55, Frame_buffer);
		LCD_12864_Draw_line(16, 54, 16, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(16, 55, Frame_buffer);
		//LCD_12864_Draw_pixel(16, 54, Frame_buffer);
		LCD_12864_Draw_line(14, 56, 14, 57, Frame_buffer);
		/*LCD_12864_Draw_pixel(14, 56, Frame_buffer);
		LCD_12864_Draw_pixel(14, 57, Frame_buffer);*/
		LCD_12864_Draw_pixel(13, 57, Frame_buffer);
	}
	else if (!strcmp(wind_direction, "S-W"))
	{
		LCD_12864_Draw_pixel(11, 50, Frame_buffer);
		LCD_12864_Draw_pixel(10, 51, Frame_buffer);
		LCD_12864_Draw_pixel(13, 52, Frame_buffer);
		LCD_12864_Draw_pixel(12, 53, Frame_buffer);
		LCD_12864_Draw_line(11, 52, 6, 57, Frame_buffer);
		LCD_12864_Draw_line(6, 54, 6, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(6, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(6, 55, Frame_buffer);
		LCD_12864_Draw_pixel(7, 55, Frame_buffer);
		//LCD_12864_Draw_pixel(6, 54, Frame_buffer);
		LCD_12864_Draw_line(7, 57, 9, 57, Frame_buffer);
		//LCD_12864_Draw_pixel(7, 57, Frame_buffer);
		//LCD_12864_Draw_pixel(8, 57, Frame_buffer);
		LCD_12864_Draw_pixel(8, 56, Frame_buffer);
		//LCD_12864_Draw_pixel(9, 57, Frame_buffer);
	}
}
void DrawBattery(uint8_t *Frame_buffer)
{
	LCD_12864_Draw_line(34, 28, 40, 28, Frame_buffer);
	LCD_12864_Draw_line(34, 19, 34, 27, Frame_buffer);
	LCD_12864_Draw_line(40, 19, 40, 27, Frame_buffer);
	LCD_12864_Draw_line(34, 19, 36, 19, Frame_buffer);
	LCD_12864_Draw_line(38, 19, 40, 19, Frame_buffer);
	LCD_12864_Draw_line(36, 18, 36, 19, Frame_buffer);
	LCD_12864_Draw_line(38, 18, 38, 19, Frame_buffer);
	LCD_12864_Draw_line(36, 18, 38, 18, Frame_buffer);
	uint8_t v_count;
	if (V_BAT(adc_value1) >= 400) {
		v_count = 6;
		/*LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
		LCD_12864_Draw_line(36, 25, 38, 25, Frame_buffer);
		LCD_12864_Draw_line(36, 24, 38, 24, Frame_buffer);
		LCD_12864_Draw_line(36, 23, 38, 23, Frame_buffer);
		LCD_12864_Draw_line(36, 22, 38, 22, Frame_buffer);
		LCD_12864_Draw_line(36, 21, 38, 21, Frame_buffer);*/
	}
	else if ((V_BAT(adc_value1) >= 390) && (V_BAT(adc_value1) < 400)) {
		v_count = 5;
		/*LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
		LCD_12864_Draw_line(36, 25, 38, 25, Frame_buffer);
		LCD_12864_Draw_line(36, 24, 38, 24, Frame_buffer);
		LCD_12864_Draw_line(36, 23, 38, 23, Frame_buffer);
		LCD_12864_Draw_line(36, 22, 38, 22, Frame_buffer);*/
	}
	else if ((V_BAT(adc_value1) >= 380) && (V_BAT(adc_value1) < 390)) {
		v_count = 4;
		/*LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
		LCD_12864_Draw_line(36, 25, 38, 25, Frame_buffer);
		LCD_12864_Draw_line(36, 24, 38, 24, Frame_buffer);
		LCD_12864_Draw_line(36, 23, 38, 23, Frame_buffer);*/
	}
	else if ((V_BAT(adc_value1) >= 370) && (V_BAT(adc_value1) < 380)) {
		v_count = 3;
		//LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
		//LCD_12864_Draw_line(36, 25, 38, 25, Frame_buffer);
		//LCD_12864_Draw_line(36, 24, 38, 24, Frame_buffer);
	}
	else if ((V_BAT(adc_value1) >= 360) && (V_BAT(adc_value1) < 370)) {
		v_count = 2;
		//LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
		//LCD_12864_Draw_line(36, 25, 38, 25, Frame_buffer);
	}
	else if ((V_BAT(adc_value1) >= 350) && (V_BAT(adc_value1) < 360)) {
		v_count = 1;
		//LCD_12864_Draw_line(36, 26, 38, 26, Frame_buffer);
	}
	else {v_count = 0;}
	for (uint8_t i = 0; i < v_count; i++)
	{
		LCD_12864_Draw_line(36, 26 - i, 38, 26 - i, Frame_buffer);
	}
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
	
	Convert_to_string_Clock();
}
void Convert_to_string_Clock(void)
{
	if ((sec >= 0) && (sec <= 9)) {
		sprintf(T_Param.seconds,"0%d",sec);
	}
	else {
		sprintf(T_Param.seconds,"%d",sec);
	}
	if ((min >= 0) && (min <= 9)) {
		sprintf(T_Param.minutes,"0%d",min);
	}
	else {
		sprintf(T_Param.minutes,"%d",min);
	}
	if ((hour >= 0) && (hour <= 9)) {
		sprintf(T_Param.hours,"0%d",hour);
	}
	else {
		sprintf(T_Param.hours,"%d",hour);
	}
	if ((date >= 0) && (date <= 9)) {
		sprintf(T_Param.mounthday,"0%d",date);
	}
	else {
		sprintf(T_Param.mounthday,"%d",date);
	}
	if ((year >= 0) && (year <= 9)) {
		sprintf(T_Param.Year,"0%d",year);
	}
	else {
		sprintf(T_Param.Year,"%d",year);
	}
	switch (day)
	{
		case 1:
		sprintf(T_Param.weakday,"Пн");
		break;
		case 2:
		sprintf(T_Param.weakday,"Вт");
		break;
		case 3:
		sprintf(T_Param.weakday,"Ср");
		break;
		case 4:
		sprintf(T_Param.weakday,"Чт");
		break;
		case 5:
		sprintf(T_Param.weakday,"Пт");
		break;
		case 6:
		sprintf(T_Param.weakday,"Сб");
		break;
		case 7:
		sprintf(T_Param.weakday,"Вс");
		break;
		default:
		break;
	}
	switch (month)
	{
		case 1:
		sprintf(T_Param.Mounth,"Янв");
		break;
		case 2:
		sprintf(T_Param.Mounth,"Фев");
		break;
		case 3:
		sprintf(T_Param.Mounth,"Мар");
		break;
		case 4:
		sprintf(T_Param.Mounth,"Апр");
		break;
		case 5:
		sprintf(T_Param.Mounth,"Май");
		break;
		case 6:
		sprintf(T_Param.Mounth,"Июн");
		break;
		case 7:
		sprintf(T_Param.Mounth,"Июл");
		break;
		case 8:
		sprintf(T_Param.Mounth,"Авг");
		break;
		case 9:
		sprintf(T_Param.Mounth,"Сен");
		break;
		case 10:
		sprintf(T_Param.Mounth,"Окт");
		break;
		case 11:
		sprintf(T_Param.Mounth,"Ноя");
		break;
		case 12:
		sprintf(T_Param.Mounth,"Дек");
		break;
		default:
		break;
	}
}
//Вычисление кол-ва осадков
int RAIN_AMOUNT(char *adc_value)
{
	int RAIN;
	int R;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &R);
	}
	else
	{
		R = 0;
	}
	RAIN = R*0.144;
	
	return RAIN;
}
//Вычисление уровня заряда АКБ
int V_BAT (char *adc_value)
{
	int VBAT;
	int V;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &V);
	}
	else
	{
		V = 0;
	}
	VBAT = V*0.72;
	
	return VBAT;
}
//Вычисление скорости ветра
int wind_speed (char *counter)
{
	int speed = 0;
	int n;
	if (strlen(counter) != 0)
	{
		sscanf(counter, "%d", &n);
	}
	else
	{
		n = 0;
	}
	speed = 2*314*RADIUS*n/4; //период 2 сек+2 магнита
	
	return speed;
}
void sprintf_HOME_Weath_Param(void)
{
	int home_temp, home_hum;
	/*sprintf(Weath_Param.Rain,"%d",RAIN_AMOUNT(adc_value2));
	sprintf(Weath_Param.Vbat,"%d",V_BAT(adc_value1));
	sprintf(Weath_Param.WIND_speed,"%d", wind_speed (HALL_counter));*/
	if (dht22_GetData(data))
	{
		//data[1]-младший бит температуры
		//data[2]-старший бит температуры
		//data[3]-младший бит влажности
		//data[4]-старший бит влажности
		home_temp = ((data[2]<<8)|data[1]);
		if (((data[2]<<8)|data[1]) & 0x8000) home_temp *= -1;
		home_hum = ((data[4]<<8)|data[3]) / 10;
	}
	sprintf(temp_home,"%d.%d",home_temp/10, home_temp%10);
	sprintf(hum_home,"%d",home_hum);
	pressure_home = BMP180_calculation()*0.0075;
	sprintf(Press_home,"%d",pressure_home);
}