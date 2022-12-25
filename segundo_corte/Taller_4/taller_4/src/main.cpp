#include <Arduino.h>
#include <ArduinoJson.h>
//LIBRERIAS PARA FECHA Y HORA
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>
//libreria cayene
#include <CayenneMQTTESP32.h> //Librería de Cayenne MQTT 
#define CAYENNE_PRINT Serial


//DEFINICION DE PINES DHT11 
#define DHTPIN 4   // 4 = PIN D4
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);

//CONFIG PARA ----FECHA Y HORA------
// Replace with your network credentials
const char* ssid = "KIRA 1";
const char* wifipassword = "3185171570";

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

//info CAYENE----------
// Parámetros  de conexión a Cayenne. Esto debe obtenerse del Tablero de Cayenne.
char username[] = "5475eb90-28b1-11ed-baf6-35fab7fd0ac8";
char password[] = "46dd0481c83ab7f4ad4aa2654369e7692bc45b50";
char clientID[] = "3c8d0360-2e4c-11ed-baf6-35fab7fd0ac8";
//-----------------

void setup() {
// Initialize Serial Monitor
Serial.begin(9600);
//CODIGO----FECHA Y HORA-----------------------
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, wifipassword);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
// Initialize a NTPClient to get time
timeClient.begin();
// Set offset time in seconds to adjust for your timezone, for example:
// COLOMBIA -5 , entonces -5*3600 ->  -18000
timeClient.setTimeOffset(-18000); //Thailand +7 = 25200


//configuracion CAYENE
Cayenne.begin(username, password, clientID, ssid, wifipassword); 

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
  //doc["Ph"] = valor;
 
      
  serializeJson(doc, variable);
  Serial.println(variable);
  Cayenne.loop();
  delay(1000);
}

// Función de Cayenne para enviar datos del sensor al canal 1.
CAYENNE_OUT(1)
{
  float t =  dht.readTemperature();//Se lee la temperatura y se asigna el valor a "t".
  //Lectura de temperatura se enviara a Cayenne en el canal 1.
  //Envió de lecturas cada 10 segundos.
  Cayenne.virtualWrite(1, t);
  //Se imprimen los siguientes datos en el monitor serie.
  CAYENNE_PRINT.println("Enviando Temperatura a Cayenne:");
  CAYENNE_PRINT.println(t);
}

// Función de Cayenne para enviar datos del sensor al canal 2.
CAYENNE_OUT(2)
{
  float h = dht.readHumidity(); //Se lee la humedad y se asigna el valor a "h"
  //Lectura de Humedad se enviaran a Cayenne en el canal 2.
  //Envió de lecturas cada 10 segundos.
  Cayenne.virtualWrite(2, h);
  //Se imprimen los siguientes datos en el monitor serie.
  CAYENNE_PRINT.println("Enviando Humedad a Cayenne");
  CAYENNE_PRINT.println(h);
}