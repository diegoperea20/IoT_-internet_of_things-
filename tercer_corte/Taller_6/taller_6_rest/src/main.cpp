#include <Arduino.h>
#include <ArduinoJson.h>

#include <HTTPClient.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>
//LIBRERIAS PARA FECHA Y HORA
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//DEFINICION DE PINES DHT11 
#define DHTPIN 14  // 4 = PIN D4
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);
//potenciometro ph 
const int portPin=34;
int valorPh=0;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

const char* ssid = "*****";//name wifi
const char* password = "*******"; // clave de wifi

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // COLOMBIA -5 , entonces -5*3600 ->  -18000
  timeClient.setTimeOffset(-18000); //Thailand +7 = 25200
}
void setup() {
  Serial.begin(9600); //Serial connection
  setup_wifi(); //WiFi connection
  delay(1500);
}



void loop() {
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
  //temperatura y humedad
  float h= dht.readHumidity();
  float t =dht.readTemperature();
   //potenciometro ph
  valorPh=analogRead(portPin)/292.5;
  //----------------------
  String variable;
  int nodo_numero = 1;
  DynamicJsonDocument doc(1024); //creacion del json
  doc["idnodo"] = nodo_numero;
  doc["temperatura"] = t;
  doc["humedad"] = h;
  doc["ph"]=valorPh;
  doc["fecha"] = dayStamp;
  doc["hora"] = timeStamp;
  

  serializeJson(doc, variable);
  Serial.println("dato a enviar: "+ variable);
  HTTPClient http; //Declare object of class HTTPClient
  WiFiClient client;
  //Specify request destination
  //http.begin(client,"URL DEL SERVIDOR");
  //http.begin(client,"http://192.168.**:3000/"); //para mosquito o mqtt
  http.begin(client,"http://192.168.*.*:3000/datos");// para rest mysql
   //http.begin(client,"http://192.168.*.*:3000/datosm");// mongo rest
  http.addHeader("Content-Type", "application/json"); //Specify contenttype header
  int httpCode = http.POST(variable); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload); //Print request response payload
  http.end(); //Close connection
  delay(5000); //Send a request every 5 seconds
}
