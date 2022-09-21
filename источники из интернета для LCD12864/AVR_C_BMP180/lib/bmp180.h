	#pragma once
//==========================================================================================
	#define BMP180_READ 			0xEF		// BMP180 ����� ��� ������	
	#define BMP180_WRITE 			0xEE		// BMP180 ����� ��� ������	
	#define BMP180_REFRESH_TIME		10
	#define BMP180_ERROR 			0x7FFFFFFF
	#define BMP180_OSS 				3			// �������� ���������
	#define BMP180_START_ROM 		0xAA		// ����� ������ EEPROM
	#define BMP180_COUNT_ROM		22			// ���������� ���� � EEPROM
	#define BMP180_REG_CONVERT 		0xF4		// ������� ��� ������ ������.����������� � ��������
	#define BMP180_REG_RESET 		0xE0		// ������� ��� ������������ ������
	#define BMP180_SOFT_RESET		0xB6		// ����������� �����
	#define BMP180_CONVERT_T 		0x2E		// ����� ��������� �����������
	#define BMP180_CONVERT_P0 		0x34		// ����� ��������� �������� (oss=0)
	#define BMP180_CONVERT_P1 		0x74		// ����� ��������� �������� (oss=1)
	#define BMP180_CONVERT_P2 		0xB4		// ����� ��������� �������� (oss=2)
	#define BMP180_CONVERT_P3 		0xF4		// ����� ��������� �������� (oss=3)
	#define BMP180_VAL_MSB  		0xF6		// MSB ������� �������� ADC BMP085
	#define BMP180_VAL_LSB  		0xF7		// LSB ������� �������� ADC BMP085
	#define BMP180_VAL_XLSB  		0xF8		// XLSB ������� �������� ADC BMP085
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
	// ������ ������������� �������� �� BMP180
	void BMP180_Calibration();

	// ����� BMP180
	void BMP180_SoftReset();

	// ������������� �������
	void BMP180_Init();

	// ������ ��������� BMP180
	void BMP180_Read(int32_t* temperature, uint32_t* pressure);
	
	// ���������� ������
	//int32_t BMP180_CalcAltitude(int32_t pressure);

