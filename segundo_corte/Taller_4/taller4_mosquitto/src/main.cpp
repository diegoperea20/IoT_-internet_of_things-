#include <Arduino.h>

#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
//LIBRERIAS PARA DHT11 (TEMPERATURA Y HUMEDAD)
#include <Adafruit_Sensor.h>
#include <DHT.h>
//LIBRERIAS PARA FECHA Y HORA
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//DEFINICION DE PINES DHT11 
#define DHTPIN 4   // 4 = PIN D4
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

#define mqttUser ""
#define mqttPass ""
#define mqttPort 1883
const char* ssid = "******";//name wifi
const char* password = "****"; // clave de wifi
char mqttBroker[] = "192.168****"; //ip del servidor
char mqttClientId[] = "topico1"; //cualquier nombre
char inTopic[] = "topico1";//topcico a suscribirse


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
  Serial.print((char)payload[i]);
}
  Serial.println();
}
WiFiClient BClient;
PubSubClient client(BClient);
void reconnect() {
// Loop until we're reconnected
  while (!client.connected()) {
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (client.connect("", mqttUser, mqttPass)) {
  Serial.println("connected");
  // Once connected, publish an announcement...
 // Once connected, publish an announcement...
  float h= dht.readHumidity();
  float t =dht.readTemperature();
  //potenciometro ph
  valorPh=analogRead(portPin)/292.5;
  //----------------------
  String variable;
  StaticJsonDocument<256> doc;

  doc["Fecha"] = dayStamp;
  doc["Hora"] = timeStamp;
  doc["temperatura"] = t;
  doc["humedad"] = h;
  doc["idnodo"] = 1;
  doc["Ph"]=valorPh;
  

  serializeJson(doc, variable);
  int lon = variable.length()+1;
  Serial.println(variable);
  char datojson[lon];
  variable.toCharArray(datojson, lon);
  client.publish(inTopic,datojson);
  client.disconnect();
  delay(5000);
  // ... and resubscribe
  //client.subscribe("topic2");
  } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
}
}
}

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

void setup()
{
  Serial.begin(9600); //Serial connection
  setup_wifi(); //WiFi connection
  client.setServer(mqttBroker, mqttPort );
  client.setCallback( callback );
  Serial.println("Setup done");
  delay(1500);
}

  
void loop(){
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
    if (!client.connected()) {
    reconnect();
    }
    client.loop();
}
