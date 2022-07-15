/*
 * NRF24.c
 *
 * Created: 11.02.2022 20:29:40
 *  Author: Alex2
 */ 
#include "NRF24.h"
//-------------------------------------------------------------
#define TX_ADR_WIDTH 3//ширина адреса
#define TX_PLOAD_WIDTH 5// величина пакета(кол-во байт в пакете)
uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0xb3,0xb4,0x01};//адрес
uint8_t RX_BUF[TX_PLOAD_WIDTH] = {0};//буффер для пакетов
extern char temp_street[10];
extern char hum_street[10];
extern float temp,hum;
extern char HALL_counter[10];
extern char wind_direction[10];
extern char adc_value1[10];
extern char adc_value2[10];
uint8_t ErrCnt_Fl = 0;//для подсчета ошибок
extern uint8_t flag_irq;
volatile uint8_t rx_flag = 0;
extern uint8_t Frame_buffer[1024];
extern char receive_time[20];
uint8_t receive_counter = 0;
char hours[4];
char minutes[4];
char seconds[4];
char mounthday[4];
char Mounth[6];
char Year[4];

//-------------------------------------------------------------
void NRF24_ini(void)
{
	LOW_CE;
	_delay_ms(5);
	nRF_write_register(CONFIG, 0x0a); // Set PWR_UP bit, enable CRC(1 byte) &Prim_RX:0 (Transmitter)
	_delay_ms(5);
	nRF_write_register(EN_AA, 0x02); // Enable Pipe1
	nRF_write_register(EN_RXADDR, 0x02); // Enable Pipe1
	nRF_write_register(SETUP_AW, 0x01); // Setup address width=3 bytes
	nRF_write_register(SETUP_RETR, 0x5F); // // 1500us, 15 retrans
	NRF24_ToggleFeatures();
	nRF_write_register(FEATURE, 0);
	nRF_write_register(DYNPD, 0);
	nRF_write_register(STATUS, 0x70);//Reset flags for IRQ
	nRF_write_register(RF_CH, 76); // частота 2476 MHz
	nRF_write_register(RF_SETUP, 0x06); //TX_PWR:0dBm, Datarate:1Mbps
	NRF24_Write_Buf(TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	NRF24_Write_Buf(RX_ADDR_P1, TX_ADDRESS, TX_ADR_WIDTH);
	nRF_write_register(RX_PW_P1, TX_PLOAD_WIDTH); //Number of bytes in RX payload in data pipe 1
	//пока уходим в режим приёмника
	NRF24L01_RX_Mode();
}
//-------------------------------------------------------------
/*void NRF24L01_Receive(void)
{
	uint8_t status=0x01;
	uint16_t dt=0;
	while(flag_irq == 1);
    status = nRF_read_register(STATUS);
	_delay_us(1);
	PORTD |= (1<<PORTD1);
	_delay_ms(100);
	PORTD &= ~(1<<PORTD1);
    if(status & 0x40)
    {
	    NRF24_Read_Buf(R_RX_PAYLOAD,RX_BUF,TX_PLOAD_WIDTH);
	    dt = *(int16_t*)RX_BUF;
	    clearlcd();
		setpos(0,0);
		sendchar(dt/100+'0');
        sendchar((dt/10)%10+'0');
		sendchar(dt%10+'0');
	    dt = *(int16_t*)(RX_BUF+2);
	    sendchar(dt/100+'0');
	    sendchar((dt/10)%10+'0');
	    sendchar(dt%10+'0');
	    nRF_write_register(STATUS, 0x40);
    }
    flag_irq = 1;
}*/
void NRF24L01_Receive(void)
{
	uint16_t dt=0;
	uint8_t n = 0;
	uint16_t T = 0;
	
	uint8_t byte1 = 0;
	uint8_t byte2 = 0;
	if(rx_flag==1)
	{
		//--------------------------------------
		//получение температуры
		if (RX_BUF[0] == 1)
		{
		  memset(temp_street, 0, sizeof(int) * strlen(temp_street));//очистка массива
		  byte1 = RX_BUF[1];//младший бит температуры
		  byte2 = RX_BUF[2];//старший бит температуры
		  temp = (float)(((byte2<<8)|byte1) / 10.0);
		  if (((byte2<<8)|byte1) & 0x8000) temp *= -1.0;
		  sprintf(temp_street,"%.1f",temp);
		}
		//--------------------------------------
		//получение влажности
		if (RX_BUF[0] == 5)
		{
			memset(hum_street, 0, sizeof(int) * strlen(hum_street));//очистка массива
			byte1 = RX_BUF[1];//младший бит температуры
			byte2 = RX_BUF[2];//старший бит температуры
			hum = (float)(((byte2<<8)|byte1) / 10.0);
			sprintf(hum_street,"%d",(int)hum);
		}
		//--------------------------------------
		//получение скорости ветра
		 if(RX_BUF[0] == 2)
		{
		  memset(HALL_counter, 0, sizeof(int) * strlen(HALL_counter));//очистка массива
		  for ( n = 0; n < strlen(RX_BUF)-1; n++)
		  {
			 HALL_counter[n] = RX_BUF[n+1];
		  }
		}
		//--------------------------------------
		//получение направления ветра
		if(RX_BUF[0] == 3)
		{
			memset(wind_direction, 0, sizeof(int) * strlen(wind_direction));//очистка массива
			for ( n = 0; n < strlen(RX_BUF)-1; n++)
			{
				wind_direction[n] = RX_BUF[n+1];
			}
			wind_direction[n+1] = ' ';
		}
		//--------------------------------------
		//получение заряда аккумулятора
		if(RX_BUF[0] == 4)
		{
			memset(adc_value1, 0, sizeof(int) * strlen(adc_value1));//очистка массива
			for ( n = 0; n < strlen(RX_BUF)-1; n++)
			{
				adc_value1[n] = RX_BUF[n+1];
			}
		}
		//--------------------------------------
		//получение кол-ва осадков
		if(RX_BUF[0] == 6)
		{
			memset(adc_value2, 0, sizeof(int) * strlen(adc_value2));//очистка массива
			for ( n = 0; n < strlen(RX_BUF)-1; n++)
			{
				adc_value2[n] = RX_BUF[n+1];
			}
		}
		//--------------------------------------
		//memset(RX_BUF, 0, sizeof(int) * strlen(RX_BUF));//очистка массива
		rx_flag = 0;
	}
}
ISR(INT0_vect)
{
	uint8_t status=0x01;
	uint8_t pipe;
	_delay_us(300);
	PORTD |= (1<<LED);
	_delay_us(300);
	PORTD &= ~(1<<LED);
	status = nRF_read_register(STATUS);
	if(status & 0x40)
	{
		NRF24_Read_Buf(R_RX_PAYLOAD,RX_BUF,TX_PLOAD_WIDTH);
		nRF_write_register(STATUS, 0x40);
	}
	 rx_flag = 1;
	 NRF24L01_Receive();
	 if(receive_counter == 6)
	 {
		 receive_counter = 0;
	 }
	 receive_counter++;
	 sprintf(receive_time,"%s:%s:%s,%s/%s/%s", hours, minutes, seconds, mounthday, Mounth, Year);
}
//-------------------------------------------------------------
void NRF24_Transmit(uint8_t addr,uint8_t *pBuf,uint8_t bytes)
{
	LOW_CE;
	LOW_CSN;
	spi_send_recv(addr);//отправим адрес в шину
	_delay_us(1);
	while (bytes--)//отправим данные в буфер
	{
		spi_send_recv(*(pBuf++));
	}
	HIGH_CSN;
	HIGH_CE;
}
//-------------------------------------------------------------
uint8_t NRF24L01_Send(uint8_t *pBuf)
{
	uint8_t status=0x00, regval=0x00; //количество повторных попыток передачи, а также количество потерянных пакетов
	NRF24L01_TX_Mode(pBuf);//перевод в режим передатчика
	regval = nRF_read_register(CONFIG);
	//если модуль ушел в спящий режим, то разбудим его, включив бит PWR_UP и выключив PRIM_RX
	regval |= (1<<PWR_UP);
	regval &= ~(1<<PRIM_RX);
	nRF_write_register(CONFIG,regval);
	_delay_us(150); //Задержка минимум 130 мкс
	//Отправим данные в воздух
	NRF24_Transmit(W_TX_PAYLOAD, pBuf, TX_PLOAD_WIDTH);
	HIGH_CE;
	_delay_us(15); //minimum 10us high pulse (Page 21)
	LOW_CE;
	while(flag_irq == 1) {}
	status = nRF_read_register(STATUS);
	if(status&TX_DS) //tx_ds == 0x20
	{
		nRF_write_register(STATUS, 0x20);
	}
	else if(status&MAX_RT)
	{
		nRF_write_register(STATUS, 0x10);
		NRF24_FlushTX();
	}
	regval = nRF_read_register(OBSERVE_TX);
	//Уходим в режим приёмника
	NRF24L01_RX_Mode();
    flag_irq = 1;
	return regval;
}
//-------------------------------------------------------------
void NRF24L01_TX_Mode(uint8_t *pBuf)  //функция перехода в режим передатчика
{
	NRF24_Write_Buf(TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	LOW_CE;
	// Flush buffers
	NRF24_FlushRX();
	NRF24_FlushTX();
}
//-------------------------------------------------------------
void NRF24_FlushRX(void)
{
	LOW_CSN;
	spi_send_recv(FLUSH_RX);
	_delay_us(1);
	HIGH_CSN;
}
//-------------------------------------------------------------
void NRF24_FlushTX(void)
{
	LOW_CSN;
	spi_send_recv(FLUSH_TX);
	_delay_us(1);
	HIGH_CSN;
}
//-------------------------------------------------------------
void NRF24L01_RX_Mode(void) // включение режима приема
{
	uint8_t regval = 0x00;
	regval = nRF_read_register(CONFIG);
	//разбудим модуль и переведём его в режим приёмника, включив биты PWR_UP и PRIM_RX
	regval |= (1<<PWR_UP)|(1<<PRIM_RX);
	nRF_write_register(CONFIG,regval);
	HIGH_CE;
	_delay_us(150); //Задержка минимум 130 мкс
	// Flush buffers
	NRF24_FlushRX();
	NRF24_FlushTX();
}
//-------------------------------------------------------------
void NRF24_ToggleFeatures(void)
{
	LOW_CSN;
	spi_send_recv(ACTIVATE);
	_delay_us(1);
	spi_send_recv(0x73);
	HIGH_CSN;
}
//-------------------------------------------------------------
void NRF24_Read_Buf(uint8_t addr,uint8_t *pBuf,uint8_t bytes)
{
	LOW_CSN;
    spi_send_recv(addr);//отправим данные в буфер
	while (bytes--) 
	{
	  *(pBuf++) = spi_send_recv(0xFF);
	}
	HIGH_CSN;
}
//-------------------------------------------------------------
void NRF24_Write_Buf(uint8_t addr,uint8_t *pBuf,uint8_t bytes)
{
	addr |= W_REGISTER;//включим бит записи в адрес
	LOW_CSN;
	spi_send_recv(addr);//отправим адрес в шину
	_delay_us(1);
	while (bytes--)
    {
	   spi_send_recv(*(pBuf++));
	}
	HIGH_CSN;
}
//-------------------------------------------------------------
void nRF_command(uint8_t command)
{
	LOW_CSN;
	spi_send_recv(command);
	HIGH_CSN;
}
//-------------------------------------------------------------
void nRF_write_register(uint8_t reg, uint8_t data_out)
{
	reg |= W_REGISTER;
	LOW_CSN;
	spi_send_recv(reg);
	spi_send_recv(data_out);
	HIGH_CSN;
}
//-------------------------------------------------------------
uint8_t nRF_read_register(uint8_t reg)
{
	uint8_t data_in;
	LOW_CSN;
	data_in = spi_send_recv(reg);
	if(reg != STATUS)
	{
		data_in = spi_send_recv(NOP);
	}
	HIGH_CSN;
	return data_in;
}
//-------------------------------------------------------------