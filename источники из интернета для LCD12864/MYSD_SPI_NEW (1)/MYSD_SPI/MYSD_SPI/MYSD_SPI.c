#include "main.h"
//----------------------------------------
#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2
//----------------------------------------
//char buffer[512] ="Sel...ия";
char buffer2[512]={};//Буфер данных для чтения
//----------------------------------------
void port_ini(void)
{
 	PORTD=0x00;
 	DDRD=0xFF;
 	PORTB|=(1<<SS)|(1<<MISO)|(1<<MOSI);
 	DDRB|=(1<<SS)|(1<<MOSI)|(1<<SCK);
}
//----------------------------------------
int main(void)
{
	FATFS fs; //указатель на объект
	FRESULT res; //результат выполнения
	WORD s1;
	
	port_ini(); //инициализируем порты
	LCD_ini();  //инициализируем дисплей
	clearlcd();//очистим дисплей
	setpos(0,0);
	str_lcd("Mount SD... ");
	res=pf_mount(&fs);
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,3);
    str_lcd("Open file... ");
	res=pf_open("/123.txt"); //Попытка открыть файл 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,2);
    str_lcd("Move pointer... ");
	res=pf_lseek(0); //Установим курсор чтения на 0 в 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,3);
    str_lcd("Read file... ");
	res=pf_read(buffer2,128,&s1);
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(2000);
    clearlcd();//очистим дисплей
    setpos(0,0);
    str_lcd(buffer2);
    _delay_ms(1000);
    setpos(0,1);
    str_lcd("Unmout SD... ");
    res=pf_mount(0x00);//Демонтируем файловую систему карты
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,2);
    str_lcd("Mount SD... ");
    res=pf_mount(&fs);
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,3);
    str_lcd("Open file... ");
    res=pf_open("/123.txt"); //Попытка открыть файл 123.txt, чтобы в него записать данные
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(2000);
    sprintf(buffer2,"World Hello!");
    clearlcd();//очистим дисплей
    setpos(0,0);
    str_lcd("Write data... ");
    res=pf_write(buffer2,strlen(buffer2),&s1);//Запишем текст из buffer2 в файл 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,1);
    str_lcd("Finalise... ");
    res=pf_write(0,0,&s1);//Финализируем файл 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,2);
    str_lcd("Unmout SD... ");
    res=pf_mount(0x00);//Демонтируем файловую систему карты
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,3);
    str_lcd("Mount SD... ");
    res=pf_mount(&fs);
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(2000);
    clearlcd();//очистим дисплей
    setpos(0,0);
    str_lcd("Open file... ");
    res=pf_open("/123.txt"); //Попытка открыть файл 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,1);
    str_lcd("Move pointer... ");
    res=pf_lseek(0); //Установим курсор чтения на 0 в 123.txt
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,2);
    str_lcd("Read file... ");
    res=pf_read(buffer2,128,&s1);
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    _delay_ms(1000);
    setpos(0,3);
    str_lcd(buffer2);
    _delay_ms(3000);
    clearlcd();//очистим дисплей
    setpos(0,0);
    str_lcd("Unmout SD... ");
    res=pf_mount(0x00);//Демонтируем файловую систему карты
    if(res==FR_OK) str_lcd("Done");
    else str_lcd("Error");
    while(1)
	{
	}
}