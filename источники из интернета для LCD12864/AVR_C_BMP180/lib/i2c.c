	#include <avr/io.h>
	#include <compat/twi.h>
	#include "i2c.h"
//==========================================================================================
void I2C_Init()
{
	TWSR = ((0 << TWPS0)|(0 << TWPS1));
	TWBR = (uint8_t)I2C_TWBR;
}
//==========================================================================================
// return 0 = device accessible, 1= failed to access device
uint8_t I2C_Start(uint8_t address)
{
	uint8_t twst;
	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;
	// send device address
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	return 0;	
}
//==========================================================================================
void I2C_Stop()
{
	// send stop condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));
}
//==========================================================================================
// 0 write successful           1 write failed
uint8_t I2C_SendByte(uint8_t data)
{
	uint8_t   twst;
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));
	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}
//==========================================================================================
uint8_t I2C_ReceiveByteACK()
{
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
//==========================================================================================
uint8_t I2C_ReceiveByteNACK()
{
	TWCR = (1 << TWINT)|(1 << TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
