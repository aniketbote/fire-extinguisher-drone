void setup() {
  Serial.begin(9600);
}

void loop() {

  float sensor_volt;
  float RS_gas;
  float ratio;
  float R0 = 0.93;

  int sensorValue = analogRead(A0);
  sensor_volt = ((float)sensorValue / 1024) * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module


  ratio = RS_gas / R0; // ratio = RS/R0
  Serial.println(ratio);
  delay(1000);
}
