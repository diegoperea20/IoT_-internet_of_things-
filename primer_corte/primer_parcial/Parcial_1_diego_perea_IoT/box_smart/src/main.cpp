#include <Arduino.h>
#include <ArduinoJson.h>
//LIBRERIAS PARA FECHA Y HORA
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>

//DEFINICION DE PINES DHT11 
#define DHTPIN 14   // 4 = PIN D4
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);

//CONFIG PARA ----FECHA Y HORA------
// Replace with your network credentials
const char* ssid = "**you*name*wifi*";//name wifi 
const char* password = "*you*password*wifi"; // clave de wifi
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;


//potenciometro ph 
const int portPin=34;
int valor=0;


void setup() {
// Initialize Serial Monitor
Serial.begin(9600);
//CODIGO----FECHA Y HORA-----------------------
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
// Initialize a NTPClient to get time
timeClient.begin();
// Set offset time in seconds to adjust for your timezone, for example:
// COLOMBIA -5 , entonces -5*3600 ->  -18000
timeClient.setTimeOffset(-18000); //Thailand +7 = 25200

}



void loop() {
while(!timeClient.update()) {
timeClient.forceUpdate();
}
// The formattedDate comes with the following format:
// 2018-05-28T16:00:13Z
// We need to extract date and time
formattedDate = timeClient.getFormattedDate();
// Extract date
int splitT = formattedDate.indexOf("T");
dayStamp = formattedDate.substring(0, splitT);
//Serial.print("DATE: ");
//Serial.println(dayStamp);
// Extract time
timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
//Serial.print("HOUR: ");
//Serial.println(timeStamp);

//CODIGO----TEMPERATURA Y HUMEDAD---------------
float h= dht.readHumidity();
float t =dht.readTemperature();
//potenciometro ph
  valor=analogRead(portPin)/292.5;
  //----------------------


//----CODIGO JSON---------------
  String variable;
  
  DynamicJsonDocument doc(1024);
  


  doc["Fecha"] = dayStamp;
  doc["Hora"] = timeStamp;
  doc["Temperatura(°C)"] = t;
  doc["Humedad(%)"] = h;
  doc["Ph"] = valor;
 
      
  serializeJson(doc, variable);
  Serial.println(variable);
  delay(1000);
}