#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define WIFI_SSID "jio-2g"
#define WIFI_PASSWORD "aniket12"
void setup () {
 
  Serial.begin(9600);
  Serial.println("Connecting .. ");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting .. ");
  }
  Serial.println("Connected to wifi network");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.29.242:8090/helloesp"); //Specify request destination
 
    int httpCode = http.GET(); //Send the request
    Serial.println(httpCode);
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }else Serial.println("An error ocurred");
 
    http.end();   //Close connection
 
  }
 
  delay(10000);    //Send a request every 10 seconds
 
}
