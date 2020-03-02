//NodeMCU  https://roboindia.com/tutorials/dht11-nodemcu-arduino/
// + --> vin
// - --> GND
// out --> D3

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define WIFI_SSID "jio-2g"
#define WIFI_PASSWORD "aniket12"
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);

void setup(void)
{
  dht.begin();
  Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Serial.println("Humidity and temperature\n\n");
  delay(700);

}
void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JsonArray& values = JSONencoder.createNestedArray("values");


  
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    values.add(h);
    values.add(t);


    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

    HTTPClient http;

    http.begin("http://127.0.0.1:5000/ard");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection

    } else {
 
    Serial.println("Error in WiFi connection");
 
  }
//    //Serial.print("Current humidity = ");
//    Serial.print(h);
//    Serial.print(",");
//    //Serial.print("temperature = ");
//    Serial.print(t);
//    Serial.println("");
  delay(5000);
}
