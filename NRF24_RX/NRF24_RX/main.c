/*
 * NRF24-Test.c
 *
 * Created: 11.02.2022 20:28:22
 * Author : Alex2
 */ 

#include "main.h"

uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
uint8_t ST7920_width = 128; //Ширина дисплея в пикселях
uint8_t ST7920_height = 64; //Высота дисплея в пикселях



unsigned char sec,min,hour,day,date,month,year,alarmhour,alarmmin;
char TIME[20] = {0};
char temp_street[10] = {0};
char hum_street[10] = {0};
char HALL_counter[10] = {0};
char WIND_speed[10] = {0};
char wind_direction[10] = {0};
char adc_value1[10] = {0};
char adc_value2[10] = {0};
char Vbat[10] = {0};
char Rain[10] = {0};
char DATA_TO_UART[50] = {0};
float temp = 0, hum = 0;
uint8_t buf1[20] = {0};
uint8_t retr_cnt, dt;
uint16_t i=1,retr_cnt_full;
uint8_t flag_irq = 1;


void timer_ini(void)//период 4сек
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b11110100; //записываем в регистр число для сравнения
	OCR1AL = 0b00100100;
	TCCR1B |= (1<<CS12)|(1<<CS10);//установим делитель 256.
}
//——————————————–
ISR (TIMER1_COMPA_vect)
{
	if((strlen(temp_street)!=0)&&(strlen(hum_street)!=0)&&(strlen(WIND_speed)!=0)&&(strlen(Rain)!=0)&&(strlen(Vbat)!=0)&&(strlen(wind_direction)!=0))
	{
		//отправка строки по UART в формате: ул.темп./скор.ветра/осадки/ул.влажность/заряд АКБ/направл.ветра
	    sprintf(DATA_TO_UART,"%s ",temp_street);
		strcat(DATA_TO_UART,WIND_speed);
		strcat(DATA_TO_UART,Rain);
		strcat(DATA_TO_UART,hum_street);
		strcat(DATA_TO_UART,Vbat);
		strcat(DATA_TO_UART,wind_direction);
		USART_Transmit(DATA_TO_UART);
	}

}

void SPI_init(void) //инициализация SPI
{
	DDRB |= ((1<<SS)|(1<<MOSI)|(1<<CE)|(1<<SCK)); //ножки SPI на выход
	PORTB &= ~((1<<SS)|(1<<MOSI)|(1<<SCK)); //низкий уровень
	DDRD &= ~(1<<IRQ);
	PORTD |= (1<<IRQ);
	HIGH_CSN;
	SPCR = ((1<<SPE)|(1<<MSTR));//включим шину, объявим ведущим
}
//-------------------------------------------------------------
void port_init(void)
{
	//инициализация портов для светодиода
	DDRD |= (1 << LED);//led
	PORTD &= ~ (1 << LED);
	
	//инициализация портов для LCD12864
	DDRD |= (1<<RS);//ножка RS на выход для LCD12864
	PORTD &= ~(1<<RS);
	DDRD |= (1<<E);
	PORTD &= ~(1<<E);
	DDRD |= (1<<RW);
	PORTD &= ~(1<<RW);
	//DDRB |= (1<<PSB);//ножка PSB на выход для LCD12864
	//PORTB &= ~(1<<PSB);
	
	 //инициализация портов для SD карты
	/* PORTB|=(1<<SS_SD);
	 DDRB|=(1<<SS_SD);
	 PORTC|=(1<<MISO_SD)|(1<<MOSI_SD);
	 DDRC|=(1<<MOSI_SD)|(1<<SCK_SD);*/
} 
//-------------------------------------------------------------
uint8_t spi_send_recv(uint8_t data) // Передаёт и принимает 1 байт по SPI, возвращает полученное значение
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}
void main(void)
{	
	port_init();
	PORTD |= (1<<LED);
    SPI_init();
	timer_ini();
	I2C_Init();
	RTC_init();
	// Установка времени для DS3231(делается 1 раз)
	//RTC_write_time(17, 37, 0);
	//RTC_write_date(7, 5, 6, 22);
	LCD_12864_ini();
	Print_Hello_World(Frame_buffer);
	USART_Init(16);    //Инициализация модуля USART скорость 115200
    NRF24_ini();
	// настраиваем параметры прерывания
	EICRA = (1<<ISC01) | (0<<ISC00);
	EIMSK = (1<<INT0);
	// и разрешаем его глобально
	sei();
	//Вывод приветствия
	Print_Download(Frame_buffer);
	PORTD &= ~(1<<LED);
	clear_LCD_12864();
	
    while (1) 
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
		//------------------------------------------------------
		setpos_LCD_12864(1,2);
		sprintf(TIME,"%d:%d:%d ", hour, min, sec );
		str_LCD_12864 (TIME);
		setpos_LCD_12864(0,0);
		NRF24L01_Receive();
		str_LCD_12864 (temp_street);
		setpos_LCD_12864(3,0);
	    sprintf(WIND_speed,"%.2f ", wind_speed (HALL_counter));
		str_LCD_12864 (WIND_speed);
		setpos_LCD_12864(6,0);
	    sprintf(Rain,"%.2f ",RAIN_AMOUNT(adc_value2));
		str_LCD_12864 (Rain);
		setpos_LCD_12864(0,1);
		str_LCD_12864 (hum_street);
		setpos_LCD_12864(3,1);
		str_LCD_12864 (wind_direction);
		setpos_LCD_12864(6,1);
	    sprintf(Vbat,"%.2f ",V_BAT(adc_value1));
		str_LCD_12864 (Vbat);
		
		_delay_ms(100);	
    }
}

