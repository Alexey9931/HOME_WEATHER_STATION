/*
 * NRF24-Test.c
 *
 * Created: 11.02.2022 20:28:22
 * Author : Alex2
 */ 

#include "main.h"

char TIME[10];
char hours[4];
char minutes[4];
char seconds[4];
uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
uint8_t ST7920_width = 128; //Ширина дисплея в пикселях
uint8_t ST7920_height = 64; //Высота дисплея в пикселях
char temp_street[10] = {0};
char hum_street[10] = {0};
char temp_home[10] = {0};	
char hum_home[10] = {0};
char HALL_counter[10] = {0};
char WIND_speed[10] = {0};
char wind_direction[10] = {0};
char adc_value1[10] = {0};
char adc_value2[10] = {0};
char Vbat[10] = {0};
char Rain[10] = {0};
char DATA_TO_UART[50] = {0};
char Press_home[10] = {0};
float temp = 0, hum = 0;
int pressure_home = 0;
uint8_t data[5] = {0};
uint8_t buf1[20] = {0};
uint8_t retr_cnt, dt;
uint16_t i=1,retr_cnt_full;
uint8_t flag_irq = 1;
uint8_t menu_flag = 0;
uint8_t counter = 0;

int8_t cnt=0;

//-------------------------------------------------------------
void timer1_ini(void)//период 4сек
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b01111010; //записываем в регистр число для сравнения
	OCR1AL = 0b00010010;
	TCCR1B |= (1<<CS12)|(1<<CS10);//установим делитель 1024.
}
//-------------------------------------------------------------
void timer0_ini(void) // период 100мкс
{
	TCCR0B |= (1<<WGM01); // устанавливаем режим СТС (сброс по совпадению)
	OCR0A = 0b01100100; //записываем в регистр число для сравнения 100
	TCCR0B |= (1<<CS01); //делитель 8
	TIMSK0 |= (1<<OCIE0A); //устанавливаем бит разрешения прерывания 0-ого счетчика по совпадению с OCR0A
}
//-------------------------------------------------------------
ISR (TIMER1_COMPA_vect)
{
	//if (menu_flag == 1) counter++;
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
	/*if (counter == 3) 
	{
		menu_flag = 0;
		counter = 0;
	}*/
}
//-------------------------------------------------------------
ISR (TIMER0_COMPA_vect)
{
	  static unsigned char new_state=0;
	  static unsigned char old_state=0;
	  
	  new_state = (PINB&0b11000000)>>6;
	 /* if(!(PIND&0b00001000)) 
	  {
		   cnt=0;
	  }*/
	  switch(old_state | new_state)
	  {
		  case 0x01: case 0x0e:
		  cnt++;
		  break;
		  case 0x04: case 0x0b:
		  cnt--;
		  break;
	  }
	  old_state = new_state<<2;
	  if (cnt >= 6){cnt = 0;}
	  else if (cnt <= -2 ){cnt = 4;}
	  else {} 
}
//-------------------------------------------------------------
//прерывания от кнопки энкодера для переключения в окно меню
void enc_interrupt_ini(void)
{
	//включим прерывания INT1 по нисходящему фронту
	MCUCR |= (1<<ISC11);
	//разрешим внешние прерывания INT1
	EIMSK |= (1<<INT1);
}
//-------------------------------------------------------------
//обработчик внешн.прерываний от кнопки энкодера
ISR(INT1_vect)
{
	if ((menu_flag == 1) && (cnt == 4))
	{
		menu_flag = 0;
	}
	else 
	{
		menu_flag = 1;
	}
}
//-------------------------------------------------------------
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
	
	//Инициализация для энкодера
	DDRD &= ~(1<<SW_ENC);
	DDRB &= ~((1<<DT_ENC)||(1<<CLK_ENC));
	PORTD |= (1 << SW_ENC);
	PORTB &= ~((1 << DT_ENC)|(1 << CLK_ENC));
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
//-------------------------------------------------------------
void main(void)
{	
	port_init();
	PORTD |= (1<<LED);
	//Инициализация интерфейсов
	SPI_init();
	I2C_Init();
	USART_Init(8);    //Инициализация модуля USART скорость 115200
	LCD_12864_ini();
	//очистка дисплея
	LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer();
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
	//Вывод приветствия
	Print_Hello_World(Frame_buffer);
	//Инициализация оборудования
	NRF24_ini();
	RTC_init();
	dht22_init();
	BMP180_Calibration();
	// Установка времени для DS3231(делается 1 разv)
	//RTC_write_time(13, 30, 0);
	//RTC_write_date(2, 28, 6, 22);
	//Вывод окна загрузки
	Print_Download(Frame_buffer);
	PORTD &= ~(1<<LED);
	//Print_Static_Home_Page(Frame_buffer);
	//Инициализация таймеров и прерываний
	cli();
	timer1_ini();
	timer0_ini();
	// настраиваем параметры прерывания
	EICRA = (1<<ISC01) | (0<<ISC00);
	EIMSK = (1<<INT0);
	enc_interrupt_ini();
	// и разрешаем его глобально
	sei();
    while (1) 
    {
		if(!menu_flag) 
		{
			Print_Home_Page(Frame_buffer);
		}
		else 
		{
			Print_Menu_Page(Frame_buffer);
		}
    }
}

