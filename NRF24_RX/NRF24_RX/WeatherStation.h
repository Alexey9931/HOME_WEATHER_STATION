/*
 * WeatherStation.h
 *
 * Created: 03.06.2022 19:16:10
 *  Author: Alex2
 */ 


#ifndef WEATHERSTATION_H_
#define WEATHERSTATION_H_

#include "main.h"

void Print_Hello_World(uint8_t *Frame_buffer);
void Print_Download(uint8_t *Frame_buffer);
void Print_Home_Page(uint8_t *Frame_buffer);
void Clock (void);
float RAIN_AMOUNT(char *adc_value);
float V_BAT (char *adc_value);
float wind_speed (char *counter);
void DrawSun(void);
void DrawSunWithClouds(void);
void DrawClouds(void);
void DrawCloudsWithRain(void);
void DrawWeatherVane(void);
void DrawBattery(void);


#endif /* WEATHERSTATION_H_ */