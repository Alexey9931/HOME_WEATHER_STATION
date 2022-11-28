#include <ArduinoJson.h>
#include <string.h>


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "home-weather-station-ivnya-default-rtdb.europe-west1.firebasedatabase.app"              // the project name address from firebase id
#define FIREBASE_AUTH "nKdcsAHzFGyJOxKtOaHKZedfZ1RyjmA1865OYzJe"       // the secret key generated from firebase
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "head2020"

String fireStatus = "";                                                     // led status received from firebase
int led = 5;
void clean_part_array(char * array);
void clean_all_array(char * array);


int counter = 0;
char data[300] = {0};
char temp_street[10] = {0};
char temp_home[10] = {0};
char hum_street[10] = {0};
char hum_home[10] = {0};
char pressure[10] = {0};
char wind_speed[10] = {0};
char rain[10] = {0};
char VBAT[10] = {0};
char wind_direct[10] = {0};
char receive_time[20] = {0};
char count[10] = {0};
int k = 0;
int i = 0;
char str[10][80] = {"/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/", "/IorkSzYb2gSID163x2MMzbOX6F83/DATA/"};


void setup()
{
  Serial.begin(115200, SERIAL_8N2);
  delay(1000);
  pinMode(led, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.write("1");
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
  //Firebase.setString("LED_STATUS", "OFF");                       //send initial string of led status
  Firebase.remove("/WzPP08rZcBXwEucCSpsI8EWnpo23/");
}
void loop()
{
    if( Serial.available() > 0 ) 
    {
      //Передача инфо о подключении к wifi
      if(WiFi.status() == WL_CONNECTED)
      {
        //Serial.println(WIFI_SSID);
      }     
      itoa (counter, count, 10);

      strcat(str[0], "STREET_TEMP/");
      strcat(str[1], "HOME_TEMP/");
      strcat(str[2], "STREET_HUM/");
      strcat(str[3], "HOME_HUM/");
      strcat(str[4], "PRESSURE/");
      strcat(str[5], "RAIN/");
      strcat(str[6], "VBAT/");
      strcat(str[7], "WIND_SPEED/");
      strcat(str[8], "WIND_DIRECT/");
      strcat(str[9], "TIME/");
      
      strcat(str[0],count);
      strcat(str[1],count);
      strcat(str[2],count);
      strcat(str[3],count);
      strcat(str[4],count);
      strcat(str[5],count);
      strcat(str[6],count);
      strcat(str[7],count);
      strcat(str[8],count);
      strcat(str[9],count);
    

      sprintf(data,"%s",Serial.readString().c_str());
      Serial.println(data);
      for (int p = 0; p < strlen(data);p++)
      {
      Serial.print(data[p]);
      }
      Serial.println("");
      //считываем ул.темпер.
      while(data[i] != ' ')
      {
        temp_street[k] = data[i];
        k++;
        i++;
      }
      Serial.println(temp_street);
      //Firebase.setString(str[0], temp_street);
      k = 0;
      i++;
      //считываем дом.темпер.
      while(data[i] != ' ')
      {
        temp_home[k] = data[i];
        k++;
        i++;
      }
      Serial.println(temp_home);
      //Firebase.setString(str[1], temp_home);
      k = 0;
      i++;
      //считываем ул.влажность
      while(data[i] != ' ')
      {
        hum_street[k] = data[i];
        k++;
        i++;
      }
      Serial.println(hum_street);
      //Firebase.setString(str[2], hum_street);
      k = 0;
      i++;
      //считываем дом.влажность
      while(data[i] != ' ')
      {
        hum_home[k] = data[i];
        k++;
        i++;
      }
      Serial.println(hum_home);
      //Firebase.setString(str[3], hum_home);
      k = 0;
      i++;
      //считываем давление
      while(data[i] != ' ')
      {
        pressure[k] = data[i];
        k++;
        i++;
      }
      Serial.println(pressure);
      //Firebase.setString(str[4], pressure);
      k = 0;
      i++;
      //считываем осадки
      while(data[i] != ' ')
      {
        rain[k] = data[i];
        k++;
        i++;
      }
      Serial.println(rain);
      //Firebase.setString(str[5], rain);
      k = 0;
      i++;
      //считываем заряд АКБ
      while(data[i] != ' ')
      {
        VBAT[k] = data[i];
        k++;
        i++;
      }
      Serial.println(VBAT);
      //Firebase.setString(str[6], VBAT);
      k = 0;
      i++;
      //считываем скор.ветра
      while(data[i] != ' ')
      {
        wind_speed[k] = data[i];
        k++;
        i++;
      }
      Serial.println(wind_speed);
      //Firebase.setString(str[7], wind_speed);
      k = 0;
      i++;
      //считываем напр.ветра
      while(data[i] != ' ')
      {
        wind_direct[k] = data[i];
        k++;
        i++;
      }
      Serial.println(wind_direct);
      //Firebase.setString(str[8], wind_direct);
      k = 0;
      i++;
      //считываем дату
      while(data[i] != ' ')
      {
        receive_time[k] = data[i];
        k++;
        i++;
      }
      Serial.println(receive_time);
      //Firebase.setString(str[9], receive_time);
      
      k = 0;
      i = 0;
      Firebase.setString(str[0], temp_street);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[0], temp_street);
        //return;
      }
      delay(500);
      Firebase.setString(str[1], temp_home);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[1], temp_home);
        //return;
      }
      delay(500);
      Firebase.setString(str[2], hum_street);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[2], hum_street);
        //return;
      }
      delay(500);
      Firebase.setString(str[3], hum_home);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[3], hum_home);
        //return;
      }
      delay(500);
      Firebase.setString(str[4], pressure);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[4], pressure);
        //return;
      }
      delay(500);
      Firebase.setString(str[5], rain);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[5], rain);
        //return;
      }
      delay(500);
      Firebase.setString(str[6], VBAT);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[6], VBAT);
        //return;
      }
      delay(500);
      Firebase.setString(str[7], wind_speed);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[7], wind_speed);
        //return;
      }
      delay(500);
      Firebase.setString(str[8], wind_direct);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[8], wind_direct);
        //return;
      }
      delay(500);
      Firebase.setString(str[9], receive_time);
      if (Firebase.failed())
      {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        Firebase.setString(str[9], receive_time);
        //return;
      }
      counter++;

      //очистка счетчика если время переваливает за сутки
      if (counter == 290)
      {
        counter = 0;
      }
      
      clean_part_array(str[0]);
      clean_part_array(str[1]);
      clean_part_array(str[2]);
      clean_part_array(str[3]);
      clean_part_array(str[4]);
      clean_part_array(str[5]);
      clean_part_array(str[6]);
      clean_part_array(str[7]);
      clean_part_array(str[8]);
      clean_part_array(str[9]);
      

      clean_all_array(receive_time);
      clean_all_array(temp_street);
      clean_all_array(temp_home);
      clean_all_array(hum_street);
      clean_all_array(hum_home);
      clean_all_array(wind_speed);
      clean_all_array(rain);
      clean_all_array(pressure);
      clean_all_array(VBAT);
      clean_all_array(wind_direct);
      clean_all_array(data);
      clean_all_array(count);
    }
    else
    {
      //Serial.println("No data");
    }
}

void clean_part_array(char * array)
{
  for (int i = 35; i < strlen(array); i++)
  {
    array[i] = NULL;
  }
}
void clean_all_array(char * array)
{
  memset(array, 0, sizeof(char) * strlen(array));//очистка массива
}

