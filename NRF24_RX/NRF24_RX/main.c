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

char temp_street[100] = {0};
char hum_street[100] = {0};
char HALL_counter[100] = {0};
char WIND_speed[50] = {0};
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
int flag_irq = 1;

float RADIUS = 0.09;

float wind_speed (char *counter)
{
	float speed = 0;
	int n;
	if (strlen(counter) != 0)
	{
		sscanf(counter, "%d", &n);
	}
	else
	{
        n = 0;
	}
	speed = 2*3.14*RADIUS*n/4; //период 2 сек+2 магнита
	
	return speed;
}
float V_BAT (char *adc_value)
{
	float VBAT;
	int V;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &V);
	}
	else
	{
		V = 0;
	}
	VBAT = V*2.45*3/1024;
	
	return VBAT;
}
float RAIN_AMOUNT(char *adc_value)
{
	float RAIN;
	int R;
	if (strlen(adc_value) != 0)
	{
		sscanf(adc_value, "%d", &R);
	}
	else
	{
		R = 0;
	}
    RAIN = 3*R*2.45/5120;
	
	return RAIN;	
}
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

SPI_init(void) //инициализация SPI
{
	DDRB |= ((1<<SS)|(1<<MOSI)|(1<<CE)|(1<<SCK)); //ножки SPI на выход
	PORTB &= ~((1<<SS)|(1<<MOSI)|(1<<SCK)); //низкий уровень
	DDRD &= ~(1<<IRQ);
	PORTD |= (1<<IRQ);
	HIGH_CSN;
	SPCR = ((1<<SPE)|(1<<MSTR));//включим шину, объявим ведущим
}
//-------------------------------------------------------------
port_init(void)
{
	DDRD |= (1 << LED);//led
	PORTD &= ~ (1 << LED);
	
	DDRD |= (1<<RS);//ножка RS на выход для LCD12864
	PORTD &= ~(1<<RS);
	DDRD |= (1<<E);
	PORTD &= ~(1<<E);
	DDRD |= (1<<RW);
	PORTD &= ~(1<<RW);
	//DDRB |= (1<<PSB);//ножка PSB на выход для LCD12864
	//PORTB &= ~(1<<PSB);
} 
//-------------------------------------------------------------
uint8_t spi_send_recv(uint8_t data) // Передаёт и принимает 1 байт по SPI, возвращает полученное значение
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}
int main(void)
{
	port_init();
	PORTD |= (1<<LED);
    SPI_init();
	timer_ini();
	I2C_Init();
	LCD_ini();
	
	LCD_12864_ini();
	//setpos_LCD_12864(2,2);
	//str_LCD_12864 ("Hello world");
	LCD_12864_GrapnicMode(1);
	//LCD_1286_Draw_pixel(100, 60);
	ST7920_Draw_rectangle(0, 0, 127, 63);
	LCD_12864_Draw_bitmap(Frame_buffer);
	LCD_12864_GrapnicMode(0);
	
	USART_Init(16);    //Инициализация модуля USART скорость 115200
	_delay_ms(1000);
    NRF24_ini();
	clearlcd();
	setpos(0,0);
	str_lcd ("hello");
	_delay_ms(1000);
	clearlcd();
	setpos(0,0);
	// настраиваем параметры прерывания
	EICRA = (1<<ISC01) | (0<<ISC00);
	EIMSK = (1<<INT0);
	// и разрешаем его глобально
	sei();
	_delay_ms(1000);
	PORTD &= ~(1<<LED);
    while (1) 
    {
		clearlcd();
		setpos(0,0);
		setpos_LCD_12864(0,0);
		NRF24L01_Receive();
		str_lcd(temp_street);
		str_LCD_12864 (temp_street);
		setpos(6,0);
		setpos_LCD_12864(3,0);
	    sprintf(WIND_speed,"%.2f ", wind_speed (HALL_counter));
		str_lcd(WIND_speed);
		str_LCD_12864 (WIND_speed);
		setpos(12,0);
		setpos_LCD_12864(6,0);
	    sprintf(Rain,"%.2f ",RAIN_AMOUNT(adc_value2));
		str_lcd(Rain);
		str_LCD_12864 (Rain);
		setpos(0,1);
		setpos_LCD_12864(0,1);
		str_lcd(hum_street);
		str_LCD_12864 (hum_street);
		setpos(6,1);
		setpos_LCD_12864(3,1);
		str_lcd(wind_direction);
		str_LCD_12864 (wind_direction);
		setpos(10,1);
		setpos_LCD_12864(6,1);
	    sprintf(Vbat,"%.2f ",V_BAT(adc_value1));
		str_lcd(Vbat);
		str_LCD_12864 (Vbat);
		
		_delay_ms(100);	
    }
}

