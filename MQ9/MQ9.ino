/* 
 
  MQ9 
 
  modified on 19 Feb 2019 
  by Saeed Hosseini 
  https://electropeak.com/learn/ 
 
*/ 
 
/*const int LED = 2;*/ 
const int DO = 8; 
 
void setup() { 
  Serial.begin(9600); 
  /*pinMode(LED, OUTPUT);*/ 
  pinMode(DO, INPUT); 
} 
 
void loop() { 
 
  int alarm = 0; 
  float sensor_volt; 
  float RS_gas; 
  float ratio; 
 //-Replace the name "R0" with the value of R0 in the demo of First Test -/ 
  float R0 = 0.93; 
 
  int sensorValue = analogRead(A0); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
 RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module 
 
 
  ratio = RS_gas / R0; // ratio = RS/R0 
 //------------------------------------------------------------/ 
 
  /*Serial.print("sensor_volt = "); 
  Serial.println(sensor_volt);*/ 
  /*Serial.print("RS_ratio = "); 
  Serial.println(RS_gas); 
  Serial.print("Rs/R0 = ");*/ 
  Serial.println(ratio);
  
if (ratio >=1.6) {
   Serial.println("CO PPM = 200");
   Serial.println("LPG PPM = 400");
   Serial.println("CH4 PPM = 500");
}
else if (ratio >= 1.1) {
   Serial.println("CO PPM = 500");
   Serial.println("LPG PPM = 700");
   Serial.println("CH4 PPM = 1000");
else if (ratio >= 0.85) {
   Serial.println("CO PPM = 800");
   Serial.println("LPG PPM = 1000");
   Serial.println("CH4 PPM = 2500");
else if (ratio >= 0.8) {
   Serial.println("CO PPM = 1000");
   Serial.println("LPG PPM = 2800");
   Serial.println("CH4 PPM = 3500");
else if (ratio >= 0.6) {
   Serial.println("CO PPM = 2000");
   Serial.println("LPG PPM = 4000");
   Serial.println("CH4 PPM = 5500");
   else if (ratio >= 0.5) {
   Serial.println("CO PPM = 3000");
   Serial.println("LPG PPM = 5000");
   Serial.println("CH4 PPM = 7000");
else if (ratio >= 0.38) {
   Serial.println("CO PPM = 5000");
   Serial.println("LPG PPM = 7000");
   Serial.println("CH4 PPM = 10000");
else (ratio >= 0.26) {
   Serial.println("CO PPM = 10000");
   Serial.println("LPG PPM = 12000");
   Serial.println("CH4 PPM = 15000");
}

  /*Serial.print("\n\n");*/ 
 
  alarm = digitalRead(DO); 
  /*if (alarm == 1) digitalWrite(LED, HIGH); 
  else if (alarm == 0) digitalWrite(LED, LOW);*/ 
 
  delay(1000); 
 
}
