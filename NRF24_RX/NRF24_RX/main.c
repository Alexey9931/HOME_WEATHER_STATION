/*
 * NRF24-Test.c
 *
 * Created: 11.02.2022 20:28:22
 * Author : Alex2
 */ 

#include "main.h"

struct Weather_Parameters {
	char temp_street[5];
	char hum_street[5];
	char temp_home[5];
	char hum_home[5];
	char WIND_speed[5];
	char wind_direction[6];
	char Vbat[5];
	char Rain[6];
	char Press_home[6];
} Weath_Param;
struct Time_Parameters {
	char hours[4];
	char minutes[4];
	char seconds[4];
	char weakday[4];
	char mounthday[4];
	char Mounth[4];
	char Year[4];
} T_Param;
unsigned char sec,min,hour,day,date,month,year,alarmhour,alarmmin;
unsigned char clock_change_mode;
char receive_time[20] = "приема не было!";
//uint8_t Frame_buffer[1024] = { 0 }; //Буфер кадра
uint8_t ST7920_width = 128; //Ширина дисплея в пикселях
uint8_t ST7920_height = 64; //Высота дисплея в пикселях
char DATA_TO_UART[57] = {0};
uint8_t menu_flag = 0;
uint8_t change_flag = 0;
int8_t add_cnt;
int8_t cnt;
uint8_t enc_int_flag = 0;
uint8_t timer2_flag = 0;
uint8_t timer1_flag = 0;
extern uint8_t rx_flag;
extern uint8_t receive_counter;

//-------------------------------------------------------------
void timer2_ini(void)//период 8мс
{	
	TCCR2A |= (1<<WGM21); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK2 |= (1<<OCIE2A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR2A = 0b11111010; //записываем в регистр число для сравнения 250
	TCCR2B |= (1<<CS22)|(1<<CS21);//установим делитель 256.
}
//-------------------------------------------------------------
void timer1_ini(void)//период 2сек
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK1 |= (1<<OCIE1A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b11110100; //записываем в регистр число для сравнения 62500
	OCR1AL = 0b00100100;
	TCCR1B |= (1<<CS12);//установим делитель 256.
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
ISR (TIMER2_COMPA_vect)
{ 
	if (timer2_flag == 0) 
	{
		timer2_flag = 1;
	}
	else 
	{
		timer2_flag = 0;
	}
}
//-------------------------------------------------------------
ISR (TIMER1_COMPA_vect)
{
	if (timer1_flag == 0) 
	{
		timer1_flag = 1;
	}
	else 
	{
		timer1_flag = 0;
	}		
}
//-------------------------------------------------------------
ISR (TIMER0_COMPA_vect)
{
	  static unsigned char new_state=0;
	  static unsigned char old_state=0;
	  
		  new_state = (PINB&0b11000000)>>6;
		  
		  switch(old_state | new_state)
		  {
			  case 0x01: case 0x0e:
			  if (change_flag) {add_cnt++;}
			  else {cnt++; PORTD |= (1<<LED);}
			  break;
			  case 0x04: case 0x0b:
			  if (change_flag) add_cnt--;
			  else {cnt--; PORTD |= (1<<LED);}
			  break;
		  }
		  old_state = new_state<<2;
		  //ограничение диапазона cnt
		  if (cnt >= 120){cnt = 0;}
		  else if (cnt <= -1){cnt = 119;}
		  //ограничение диапазона add_cnt
		  switch(cnt%7)
		  {
			  case 0:	if (add_cnt >= 24){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 23;}
			  break;
			  case 1: if (add_cnt >= 60){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 59;}
			  break;
			  case 2: if (add_cnt >= 8){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 7;}
			  break;
			  case 3: if (add_cnt >= 32){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 31;}
			  break;
			  case 4: if (add_cnt >= 13){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 12;}
			  break;
			  case 5: if (add_cnt >= 100){add_cnt = 0;}
			  else if (add_cnt <= -1){add_cnt = 99;}
			  break;
		  }
		  PORTD &= ~(1<<LED);
}
//-------------------------------------------------------------
//прерывания от кнопки энкодера для переключения в окно меню
void enc_interrupt_ini(void)
{
	//включим прерывания INT1 по нисходящему фронту
	EICRA |= (1<<ISC11);
	//разрешим внешние прерывания INT1
	EIMSK |= (1<<INT1);
}
//-------------------------------------------------------------
//обработчик внешн.прерываний от кнопки энкодера
ISR(INT1_vect)
{
	//enc_int_flag = 1;
	switch (menu_flag)
	{
		case 0: menu_flag = 1;
		//cnt = 0;
		break;
		case 1:	switch(cnt%4)
		{
			case 0:	menu_flag = 0;
			break;
			case 1:	menu_flag = 2;
			break;
			case 2:	menu_flag = 3;
			break;
			case 3:	menu_flag = 4;
			break;
		}
		//cnt = 0;
		break;
		case 2:	switch(cnt%7)
		{
			case 0:	if(!change_flag)
			{
				add_cnt = hour;
				change_flag = 1;
			}
			else
			{
				hour = add_cnt;
				clock_change_mode = 1;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 1:	if(!change_flag)
			{
				add_cnt = min;
				change_flag = 1;
			}
			else
			{
				min = add_cnt;
				clock_change_mode = 2;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 2:	if(!change_flag)
			{
				add_cnt = day;
				change_flag = 1;
			}
			else
			{
				day = add_cnt;
				clock_change_mode = 6;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 3:	if(!change_flag)
			{
				add_cnt = date;
				change_flag = 1;
			}
			else
			{
				date = add_cnt;
				clock_change_mode = 3;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 4:	if(!change_flag)
			{
				add_cnt = month;
				change_flag = 1;
			}
			else
			{
				month = add_cnt;
				clock_change_mode = 4;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 5:	if(!change_flag)
			{
				add_cnt = year;
				change_flag = 1;
			}
			else
			{
				year = add_cnt;
				clock_change_mode = 5;
				ModifyRTC();
				change_flag = 0;
			}
			break;
			case 6:	clock_change_mode = 0;
			menu_flag = 1;
			//cnt = 1;
			break;
		}
		break;
		case 3: menu_flag = 1;
		//cnt = 0;
		break;
		case 4: menu_flag = 1;
		//cnt = 0;
		break;
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
int main(void)
{	
	port_init();
	PORTD |= (1<<LED);
	//Инициализация интерфейсов
	SPI_init();
	I2C_Init();
	USART_Init(8);    //Инициализация модуля USART скорость 115200
	LCD_12864_ini();
	//очистка дисплея
	/*LCD_12864_GrapnicMode(1);
	LCD_12864_Clean_Frame_buffer();
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);*/
	//Вывод приветствия
	//Print_Hello_World();
	//Инициализация оборудования
	NRF24_ini();
	RTC_init();
	dht22_init();
	BMP180_Calibration();
	// Установка времени для DS3231(делается 1 разv)
	//RTC_write_time(13, 30, 0);
	//RTC_write_date(2, 28, 6, 22);
	//Вывод окна загрузки
	//Print_Download();
	PORTD &= ~(1<<LED);
	//Инициализация таймеров и прерываний
	timer2_ini();
	timer1_ini();
	timer0_ini();
	// настраиваем параметры прерывания
	EICRA |= (1<<ISC01) | (0<<ISC00);
	EIMSK |= (1<<INT0);
	enc_interrupt_ini();
	// и разрешаем его глобально
	sei();
	//Начальная конфигурация
	Weath_Param.temp_street[0] = '0';
	Weath_Param.temp_street[1] = '0';
	Weath_Param.temp_street[2] = '.';
	Weath_Param.temp_street[3] = '0';
	Weath_Param.hum_street[0] = '0';
	Weath_Param.hum_street[1] = '0';
	Weath_Param.Vbat[0] = '0';
	Weath_Param.Vbat[1] = '.';
	Weath_Param.Vbat[2] = '0';
	Weath_Param.Vbat[3] = '0';
	Weath_Param.temp_home[0] = '0';
	Weath_Param.temp_home[1] = '0';
	Weath_Param.temp_home[2] = '.';
	Weath_Param.temp_home[3] = '0';
	Weath_Param.hum_home[0] = '0';
	Weath_Param.hum_home[1] = '0';
	Weath_Param.WIND_speed[0] = '0';
	Weath_Param.WIND_speed[1] = '.';
	Weath_Param.WIND_speed[2] = '0';
	Weath_Param.WIND_speed[3] = '0';
	Weath_Param.Press_home[0] = '0';
    //Weath_Param.wind_direction[0] = '-';
    while (1) 
    {
		if (rx_flag == 1)
		{
			_delay_us(300);
			PORTD |= (1<<LED);
			_delay_us(300);
			PORTD &= ~(1<<LED);
			NRF24L01_Receive();
			Clock ();
			sprintf(receive_time,"%s:%s:%s,%s/%s/%s", T_Param.hours, T_Param.minutes, T_Param.seconds, T_Param.mounthday, T_Param.Mounth, T_Param.Year);
		}
		if(timer2_flag == 1)
		{
			switch (menu_flag)
			{
				case 0:	Print_Home_Page();
						break;
				case 1:	Print_Menu_Page();
						break;
				case 2:	Print_Page_Clock_Settings();
						break;
				case 3:	Print_Page_About();
						break;
				case 4:	Print_Page_Dop_Info();
						break;
			}
		}
		if(timer1_flag == 1)
		{
			sprintf_HOME_Weath_Param();
			//отправка строки по UART в формате: ул.темп./дом.темп./ул.влажность/дом.влажн./давление/осадки/заряд АКБ/скор.ветра/направл.ветра
			sprintf(DATA_TO_UART,"%s %s %s %s %s %s %s %s %s ",Weath_Param.temp_street, Weath_Param.temp_home, Weath_Param.hum_street, Weath_Param.hum_home, Weath_Param.Press_home, Weath_Param.Rain, Weath_Param.Vbat, Weath_Param.WIND_speed, Weath_Param.wind_direction);
			USART_Transmit(DATA_TO_UART);
			memset(DATA_TO_UART, 0, sizeof(char) * strlen(DATA_TO_UART));//очистка массива
		}	
    }
}

