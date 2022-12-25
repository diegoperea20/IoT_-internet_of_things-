#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>
//LIBRERIAS PARA FECHA Y HORA
#include <NTPClient.h>
#include <WiFiUdp.h>
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;


//DEFINICION DE PINES DHT11 
#define DHTPIN 4   // 4 = PIN D4
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);







const char* ssid = "**name*wifi***"; //El SSID de la red wifi a la que se conectará
const char* password = "**your*password*"; //El password para conectarse a la red inalambrica


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
  //JSON DE FECHA Y HORA no enviar
  String variable_fecha_y_hora;
  DynamicJsonDocument doc1(1024);
  doc1["Fecha"] = dayStamp;
  doc1["Hora"] = timeStamp;
  serializeJson(doc1, variable_fecha_y_hora);

  //JSON Humedad y temperatura a enviar platafoma IoT
  String variable;
  DynamicJsonDocument doc(1024); //creacion del json
  doc["temperatura(°C)"] = t;
  doc["humedad(%)"] = h;
  

  serializeJson(doc, variable);
  Serial.println("dato a enviar: "+ variable);
  Serial.println("dato no enviar: "+ variable_fecha_y_hora);
  HTTPClient http; //Declare object of class HTTPClient
  WiFiClient client;
  //Specify request destination
  //http.begin(client, "URL A INGRESAR");
  //http.begin(client, "http://192.16*.*.*:3000/datos/"); LOCAL URL
  //http.begin(client, "http://things.ubidots.com/api/v1.6/devices/name_device/?token=your_token_api_credentials");
  http.begin(client, "http://things.ubidots.com/api/v1.6/devices/esp32/?token=BBFF-baawaxKZeBQm3NHX7k0IlKxBDtWgVc");
  http.addHeader("Content-Type", "application/json"); //Specify contentype header
  int httpCode = http.POST(variable); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(httpCode); //Print HTTP return code
  Serial.println(payload); //Print request response payload
  http.end(); //Close connection
  delay(5000); //Send a request every 5 seconds
}

//PARA POSTMAN GET:http://things.ubidots.com/api/v1.6/devices/esp32/temperatura-degc/values?token=BBFF-baawaxKZeBQm3NHX7k0IlKxBDtWgVc
//PARA POSTMAN POST:  http://things.ubidots.com/api/v1.6/devices/esp32/?token=BBFF-baawaxKZeBQm3NHX7k0IlKxBDtWgVc
