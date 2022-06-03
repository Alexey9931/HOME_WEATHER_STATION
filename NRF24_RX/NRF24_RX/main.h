/*
 * main.h
 *
 * Created: 03.02.2022 17:52:19
 *  Author: Alex2
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LED PORTD4

#include "NRF24.h"
#include "TWI.h"
#include "usart.h"
#include "LCD_12864.h"
#include "SD.h"
#include "pff.h"
#include "diskio.h"
#include "integer.h"
#include "WeatherStation.h"

#endif /* MAIN_H_ */