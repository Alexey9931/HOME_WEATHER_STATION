/*
 * WeatherStation.h
 *
 * Created: 03.06.2022 19:16:10
 *  Author: Alex2
 */ 


#ifndef WEATHERSTATION_H_
#define WEATHERSTATION_H_

#include "main.h"

void Print_Hello_World();
void Print_Download();
void Print_Home_Page();
void Print_Menu_Page();
void Print_Page_Clock_Settings();
void Print_Page_About();
void Print_Page_Dop_Info();
void Clock (void);
void Convert_to_string_Clock(void);
int RAIN_AMOUNT(char *adc_value);
int V_BAT (char *adc_value);
int wind_speed (char *counter);
void DrawSun(uint8_t *Frame_buffer);
void DrawSunWithClouds(uint8_t *Frame_buffer);
void DrawClouds(uint8_t *Frame_buffer);
void DrawCloudsWithRain(uint8_t *Frame_buffer);
void DrawWeatherVane(uint8_t *Frame_buffer);
void DrawBattery(uint8_t *Frame_buffer);
void sprintf_Home_Weath_Param(void);


#endif /* WEATHERSTATION_H_ */