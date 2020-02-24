/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>


char auth[] = "07X4pmFJnek8d9gzeD7m_p56qpg3L8mW";
char ssid[] = "Firebird";
char pass[] = "123456789";
Servo servo;


//V3 pin of NodeMCU
BLYNK_WRITE(V3) 
{
servo.write(param.asInt());
}


void setup() 
{
Blynk.begin(auth, ssid, pass);
servo.attach(15); // 15 means D8 pin of ESP8266
}


void loop()
{
Blynk.run(); // You can inject your own code or combine it with other sketches.
}
