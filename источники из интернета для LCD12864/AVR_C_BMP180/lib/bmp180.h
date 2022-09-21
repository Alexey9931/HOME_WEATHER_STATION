	#pragma once
//==========================================================================================
	#define BMP180_READ 			0xEF		// BMP180 адрес для чтения	
	#define BMP180_WRITE 			0xEE		// BMP180 адрес для записи	
	#define BMP180_REFRESH_TIME		10
	#define BMP180_ERROR 			0x7FFFFFFF
	#define BMP180_OSS 				3			// Точность измерений
	#define BMP180_START_ROM 		0xAA		// Адрес начала EEPROM
	#define BMP180_COUNT_ROM		22			// Количество байт в EEPROM
	#define BMP180_REG_CONVERT 		0xF4		// Регистр для начала преобр.температуры и давления
	#define BMP180_REG_RESET 		0xE0		// Регистр для программного сброса
	#define BMP180_SOFT_RESET		0xB6		// Программный сброс
	#define BMP180_CONVERT_T 		0x2E		// Старт измерения температуры
	#define BMP180_CONVERT_P0 		0x34		// Старт измерения давления (oss=0)
	#define BMP180_CONVERT_P1 		0x74		// Старт измерения давления (oss=1)
	#define BMP180_CONVERT_P2 		0xB4		// Старт измерения давления (oss=2)
	#define BMP180_CONVERT_P3 		0xF4		// Старт измерения давления (oss=3)
	#define BMP180_VAL_MSB  		0xF6		// MSB регистр значений ADC BMP085
	#define BMP180_VAL_LSB  		0xF7		// LSB регистр значений ADC BMP085
	#define BMP180_VAL_XLSB  		0xF8		// XLSB регистр значений ADC BMP085
	#define BMP180_AC1				0
	#define BMP180_AC2				1
	#define BMP180_AC3				2
	#define BMP180_AC4				3
	#define BMP180_AC5				4
	#define BMP180_AC6				5
	#define BMP180_B1				6
	#define BMP180_B2				7
	#define BMP180_MB				8
	#define BMP180_MC				9
	#define BMP180_MD				10
//==========================================================================================
	// чтение калибровочных констант из BMP180
	void BMP180_Calibration();

	// сброс BMP180
	void BMP180_SoftReset();

	// инициализация датчика
	void BMP180_Init();

	// чтение показаний BMP180
	void BMP180_Read(int32_t* temperature, uint32_t* pressure);
	
	// вычисление высоты
	//int32_t BMP180_CalcAltitude(int32_t pressure);

