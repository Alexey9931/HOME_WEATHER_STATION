/*
 * usart.c
 *
 * Created: 19.11.2021 0:05:26
 *  Author: Alex2
 */ 
#include "usart.h"

extern uint8_t rx_flag;

void USART_Init( unsigned int speed)//������������� ������ USART
{	
  UBRR0H = (unsigned char)(speed>>8);
  UBRR0L = (unsigned char)speed;
  UCSR0B=(1<<RXEN0)|( 1<<TXEN0); //�������� ����� � �������� �� USART
  UCSR0B |= (1<<RXCIE0); //��������� ���������� ��� ������
  UCSR0A |= (1<<U2X0); // ��� 8 ���, �������� ��������
  UCSR0C |= (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);// ���������� ������ � �������� UCSRC (URSEL=1),
  //������������ ����� (UMSEL=0), ��� �������� �������� (UPM1=0 � UPM0=0),
  //2 ����-��� (USBS=1), 8-��� ������� (UCSZ1=1 � UCSZ0=1)
  //UCSRC |= (1<<UPM1);//��������
}
void USART_Transmit( char* data ) //������� �������� ������
{
  uint8_t i;
  uint8_t Flag = 0;
  
  for (i = 0; i < strlen(data); i++)
  {
	  while ( !(UCSR0A & (1<<UDRE0)) )//�������� ����������� ������ ������
	  {
		  if (rx_flag == 1) 
		  {
			  Flag = 1;
			  break;
		  }
	  } 
	  if (Flag == 1)
	  {
		  break;
	  }
	  UDR0 = data[i]; //������ �������� ������
  }
  Flag = 0;
}
