/*
 * TWI.c
 *
 * Created: 28.11.2021 19:33:09
 *  Author: Alex2
 */ 
#include "TWI.h"

void I2C_Init(void)
{
	TWBR=0x48; //скорость передачи (при 8 мГц получается 100 кГц)
}
void I2C_StartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
}
void I2C_StopCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
void I2C_SendByte(unsigned char c)
{
	TWDR = c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}
void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
{
    I2C_StartCondition(); // Отправим условие START
	I2C_SendByte(addr); // Отправим в шину адрес устройства + бит чтения-записи
	I2C_SendByte(c);// Отправим байт данных
	I2C_StopCondition();// Отправим условие STOP
}