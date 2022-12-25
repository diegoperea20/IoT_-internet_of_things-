#include <dht.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

#define temperatura A0

dht DHT;
void setup(){
 
  Serial.begin(9600);
  setTime(5,16,0,15,11,2022);  // setTime(hr,min,sec,day,mnth,yr); 
  delay(1000);
  analogReference(INTERNAL);
 
}
String dato(int digit){
  String cosa=String("0")+digit;
  return cosa.substring(cosa.length()-2);
}
 
void loop(){

    DHT.read11(temperatura);
    //fecha y hora 
    String tiempo = String(hour()) + ":" + dato(minute()) + ":" +dato(second());
    String fecha = String (year()) + "-" + dato(month()) +"-"+dato(day());
    //--------------------------
    
    String variable;
  
    DynamicJsonDocument doc(1024);

    doc["Fecha"] = fecha;
    doc["Hora"] = tiempo;
    doc["Temperatura"] = DHT.temperature;
    doc["Humedad"] = DHT.humidity; 
    
       
    serializeJson(doc, variable);
    Serial.println(variable);
    delay(500);
}




