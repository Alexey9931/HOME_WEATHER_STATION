#include <ArduinoJson.h>
#include <string.h>


#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>                                        
 
#define FIREBASE_HOST "home-weather-station-43ffd-default-rtdb.europe-west1.firebasedatabase.app"              // the project name address from firebase id
#define FIREBASE_AUTH "uHlaA3xpnFKPxL7YNGbE0nO5scWOqyDgVEhsrOIM"       // the secret key generated from firebase
#define WIFI_SSID "Redmi"                                          
#define WIFI_PASSWORD "head2020"                                  
 
String fireStatus = "";                                                     // led status received from firebase
int led = 5;  
void clean_part_array(char * array);
void clean_all_array(char * array);
                                                     
void setup() 
{
  Serial.begin(115200,SERIAL_8N2);
  delay(1000);    
  pinMode(led, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
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
 // Firebase.setString("LED_STATUS", "OFF");                       //send initial string of led status
  Firebase.remove("/sCZoqipNlSMyCOf94rIcWLVT1Il2/");
}
 int counter = 0;
 char data[70] = {0};
 char temp_street[10] = {0};
 char hum_street[10] = {0};
 char wind_speed[10] = {0};
 char rain[10] = {0};
 char VBAT[10] = {0};
 char wind_direct[10] = {0};
 char count[30] = {0};
 int k = 0;
 int i = 0;
 char str[6][60] = {"/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/","/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/","/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/","/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/","/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/","/sCZoqipNlSMyCOf94rIcWLVT1Il2/DATA/"};
      
 
void loop() 
{
    
    if( Serial.available() > 0 ) {
    itoa (counter, count, 10);

    strcat(str[0], "STREET_TEMP/");
    strcat(str[1], "STREET_HUM/");
    strcat(str[2], "WIND_SPEED/");
    strcat(str[3], "RAIN/");
    strcat(str[4], "VBAT/");
    strcat(str[5], "WIND_DIRECT/");
    strcat(str[0],count);
    strcat(str[1],count);
    strcat(str[2],count);
    strcat(str[3],count);
    strcat(str[4],count);
    strcat(str[5],count);
    
    sprintf(data,"%s",Serial.readString().c_str());
    Serial.println(data);
    for (int p = 0; p< strlen(data);p++)
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
        k = 0;
        i++;
        //считываем скор.ветра
        while(data[i] != ' ')
        {
          wind_speed[k] = data[i];
          k++;
          i++; 
        }
        k = 0;
        i++;
        //считываем осадки
        while(data[i] != ' ')
        {
          rain[k] = data[i];
          k++;
          i++; 
        }
        k = 0;
        i++;
        //считываем ул.влажность
        while(data[i] != ' ')
        {
          hum_street[k] = data[i];
          k++;
          i++; 
        }
        k = 0;
        i++;
        //считываем заряд АКБ
        while(data[i] != ' ')
        {
          VBAT[k] = data[i];
          k++;
          i++; 
        }
        k = 0;
        i++;
        //считываем напр.ветра
        while(data[i] != 0)
        {
          wind_direct[k] = data[i];
          k++;
          i++; 
        }
        k = 0;
        i = 0;
        Serial.println(temp_street);
        Serial.println(hum_street);
        Serial.println(wind_speed);
        Serial.println(rain);
        Serial.println(VBAT);
        Serial.println(wind_direct);
        Serial.println("");
    if((strlen(temp_street)!=0)&&(strlen(hum_street)!=0)&&(strlen(wind_speed)!=0)&&(strlen(rain)!=0)&&(strlen(VBAT)!=0)&&(strlen(wind_direct)!=0))
    {
    //Firebase.pushString(str, fireHumid);            //setup path to send Humidity readings
    Firebase.setString(str[0], temp_street);
    Firebase.setString(str[1], hum_street);
    Firebase.setString(str[2], wind_speed);
    Firebase.setString(str[3], rain);
    Firebase.setString(str[4], VBAT);
    Firebase.setString(str[5], wind_direct);


    if (Firebase.failed()) 
    {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
    }
     
     counter++;
    }
    
    }
    
    clean_part_array(str[0]);
    clean_part_array(str[1]);
    clean_part_array(str[2]);
    clean_part_array(str[3]);
    clean_part_array(str[4]);
    clean_part_array(str[5]);

    clean_all_array(temp_street);
    clean_all_array(hum_street);
    clean_all_array(wind_speed);
    clean_all_array(rain);
    clean_all_array(VBAT);
    clean_all_array(wind_direct);
    clean_all_array(data);
    clean_all_array(count);
    
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
  /*
  for (int i = 0; i < strlen(array); i++)
  {
    array[i] = NULL;
  }*/
  memset(array, 0, sizeof(int) * strlen(array));//очистка массива
}

