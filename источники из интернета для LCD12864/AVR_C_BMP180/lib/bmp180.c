	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
//	#include <math.h>
	#include "i2c.h"
	#include "bmp180.h"

	static int16_t 		BMP180_Calibration_Values[11];
//==========================================================================================
// чтение 16-битного значения из BMP180
uint16_t BMP180_ReadShort(uint8_t address)
{
	I2C_Start(BMP180_WRITE);
	I2C_SendByte(address);
	I2C_Start(BMP180_READ);
	uint16_t msb = I2C_ReceiveByteACK();
	uint16_t lsb = I2C_ReceiveByteNACK();
	I2C_Stop();
	uint16_t data = (msb << 8) + lsb;
	return data;
}
//==========================================================================================
// чтение 32-битного значения из BMP180
uint32_t BMP180_ReadLong(uint8_t address)
{
	I2C_Start(BMP180_WRITE);
	I2C_SendByte(address);
	I2C_Start(BMP180_READ);
	uint32_t msb = I2C_ReceiveByteACK();
	uint32_t lsb = I2C_ReceiveByteNACK();
	uint32_t xlsb = I2C_ReceiveByteNACK();
	I2C_Stop();
	uint32_t data = ((msb << 16) + (lsb << 8) + xlsb) >> (8 - BMP180_OSS);
	return data;
}
//==========================================================================================
// чтение калибровочных констант из BMP180
void BMP180_Calibration()
{
	uint8_t i = 11;
	uint8_t address = 0xBE; // BMP180_MD address
	for(i = 11; i; --i){
		BMP180_Calibration_Values[i-1] = BMP180_ReadShort(address);
		address-=2;
	}
}
//==========================================================================================
void BMP180_SoftReset()
{
	I2C_Start(BMP180_WRITE);
	I2C_SendByte(BMP180_REG_RESET);
	I2C_SendByte(BMP180_SOFT_RESET);
	I2C_Stop();
}
//==========================================================================================
void BMP180_Init()
{
	BMP180_Calibration();
	BMP180_SoftReset();
}
//==========================================================================================
// чтение сырых показаний температуры из BMP180
int32_t BMP180_ReadTemp()
{
	I2C_Start(BMP180_WRITE);
	I2C_SendByte(BMP180_REG_CONVERT);
	I2C_SendByte(BMP180_CONVERT_T);
	I2C_Stop();
	// ожидание измерения давления
	_delay_ms(5);
	int32_t temperature = BMP180_ReadShort(BMP180_VAL_MSB);
	return temperature;
}
//==========================================================================================
// чтение сырых показаний давления из BMP180
int32_t BMP180_ReadPressure()
{
	I2C_Start(BMP180_WRITE);
	I2C_SendByte(BMP180_REG_CONVERT);
	I2C_SendByte(BMP180_CONVERT_P0 + (BMP180_OSS << 6));
	I2C_Stop();
	// ожидание измерения давления
	_delay_ms(25);
	int32_t pressure = BMP180_ReadLong(BMP180_VAL_MSB);
	return pressure;		
}
//==========================================================================================
void BMP180_Read(int32_t* temperature, uint32_t* pressure)
{
	int32_t ut=0;
	int32_t up=0;
	int32_t x1, x2, b5, b6, x3, b3, p;
	uint32_t b4, b7;

	ut = BMP180_ReadTemp();
	up = BMP180_ReadPressure();
	x1 = ((int32_t)ut - (int32_t)BMP180_Calibration_Values[BMP180_AC6]) * (int32_t)BMP180_Calibration_Values[BMP180_AC5] >> 15;
	x2 = ((int32_t)BMP180_Calibration_Values[BMP180_MC] << 11) / (x1 + BMP180_Calibration_Values[BMP180_MD]);
	b5 = x1 + x2;
	*temperature = (b5 + 8) >> 4;
	b6 = b5 - 4000;
	x1 = (BMP180_Calibration_Values[BMP180_B2] * ((b6 * b6) >> 12)) >> 11;
	x2 = (BMP180_Calibration_Values[BMP180_AC2] * b6) >> 11;
	x3 = x1 + x2;
	b3 = (((((int32_t) BMP180_Calibration_Values[BMP180_AC1]) * 4 + x3)<<BMP180_OSS) + 2)>> 2;
	x1 = (BMP180_Calibration_Values[BMP180_AC3] * b6) >> 13;
	x2 = (BMP180_Calibration_Values[BMP180_B1] * ((b6 * b6) >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = ((uint16_t)BMP180_Calibration_Values[BMP180_AC4] * (uint32_t) (x3 + 32768)) >> 15;
	b7 = ((uint32_t) (up - b3) * (50000 >> BMP180_OSS));
	if (b7 < 0x80000000)
	{
		p = (b7 << 1) / b4;
	}
	else
	{ 
		p = (b7 / b4) << 1;
	}
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	*pressure = p + ((x1 + x2 + 3791) >> 4);
}
//==========================================================================================
/*
int32_t bmp180CalcAltitude(int32_t pressure){
	float temp;
	int32_t altitude;
	temp = (float) pressure/101325;
	temp = 1-pow(temp, 0.19029);
	//altitude = round(44330*temp*10);
	altitude = 44330*temp*100;
	//get altitude in dm
	return altitude;
}
*/
