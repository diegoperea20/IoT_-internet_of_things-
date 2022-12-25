#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>
//DEFINICION DE PINES DHT11 
#define DHTPIN 4   // 4 = PIN D4
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);
//codigo de https://help.ubidots.com/en/articles/937072-build-a-tank-volume-reader-in-under-30-using-esp32?_gl=1*gypb4x*_ga*MTMzMjUxNzE3NS4xNjYyOTA3Mjk5*_ga_VEME7QQ5EZ*MTY2MjkwNzI5OC4xLjEuMTY2MjkwOTMzOC4wLjAuMA..
#include <PubSubClient.h>





/*
namespace {
  const char * WIFISSID = "******"; // Put your WifiSSID here
  const char *  PASSWORD = "********"; // Put your wifi password here
  const char * TOKEN = "BBFF-baawaxKZeBQm3NHX7k0IlKxBDtWgVc"; // Put your Ubidots' TOKEN
  const char * MQTT_CLIENT_NAME = "192.16*.*.*"; // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
  const char * VARIABLE_LABEL_2 = "humidity"; // Assign the variable label
  const char * VARIABLE_LABEL_3 = "temperature"; // Assign the variable label
  const char * DEVICE_LABEL = "esp32"; // Assign the device label
  const char * MQTT_BROKER = "industrial.api.ubidots.com";  
 

}




char payload[300];
char topic[150];

char str_sensor[10];
char str_TempSensor[10];
char str_HumSensor[10];


WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}




void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFISSID, PASSWORD);

 

  Serial.println();
  Serial.print("Wait for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(MQTT_BROKER, 1883);
  client.setCallback(callback);  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  
 
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  


 
  
  dtostrf(humidity, 4, 2, str_HumSensor);
  dtostrf(temperature, 4, 2, str_TempSensor);
  
  
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\": %s,", VARIABLE_LABEL_2, str_sensor); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_3, str_TempSensor); // Adds the variable label
    
  //sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); 

  
  Serial.println("Publishing values to Ubidots Cloud");
  Serial.print("Humidity = ");
  Serial.println(humidity);
  Serial.print("Temperature = ");
  Serial.println(temperature);
  
  
   client.publish(topic, payload);
  client.loop();
  delay(1000);
}*/


//codigo de https://help.ubidots.com/en/articles/748067-connect-an-esp32-devkitc-to-ubidots-over-mqtt

#include <UbidotsEsp32Mqtt.h>
const char *UBIDOTS_TOKEN = "BBFF-baawaxKZeBQm3NHX7k0IlKxBDtWgVc";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "****";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "*****";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "temperatura"; // Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;


Ubidots ubidots(UBIDOTS_TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
}

void loop()
{
  
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(int ( millis() - timer)) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    int variable=30;
    
    ubidots.add(VARIABLE_LABEL, variable); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}