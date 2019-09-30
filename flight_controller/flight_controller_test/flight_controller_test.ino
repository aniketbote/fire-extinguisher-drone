#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.
BlynkTimer timer;

//DECLARATIONS

char auth[] = "GTxIh_t7NxIUOD2Pqn5ZwcK3_J9ZJfqU"; //Authentication key
char ssid[] = "OnePlus6"; //Wifi name
char pass[] = "aniket12"; //wifi password

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z, gyro_x, gyro_y, gyro_z, temperature, accelerometer_x2, accelerometer_y2, accelerometer_z2;
int xAng2,yAng2,zAng2;
int minVal=265; 
int maxVal=402;
int pinValue = 0;
int timerId;
int flagx = 0;
int flagy = 0;
char high[] = "HIGH";
char low[] = "LOW";
char tmp_str[7];
bool hover_state;
double x2, y2, z2, x, y, z;



//FUNCTIONS

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void left(){
Serial.println("LEFT");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(high);
Serial.print("Fan3 = ");Serial.println(high);
Serial.print("Fan4 = ");Serial.println(low); 
}

void right(){
Serial.println("RIGHT");
Serial.print("Fan1 = ");Serial.println(high);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(high); 
}

void forward(){
Serial.println("FORWARD");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(high);
Serial.print("Fan4 = ");Serial.println(high); 
}

void backward(){
Serial.println("BACKWARD");
Serial.print("Fan1 = ");Serial.println(high);
Serial.print("Fan2 = ");Serial.println(high);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(low); 
}

void up(){
Serial.println("UP");
Serial.print("Fan1 = ");Serial.println(high);
Serial.print("Fan2 = ");Serial.println(high);
Serial.print("Fan3 = ");Serial.println(high);
Serial.print("Fan4 = ");Serial.println(high); 
}

void down(){
Serial.println("DOWN");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(low); 
}
void constant(){
Serial.println("CONSTANT");
Serial.print("Fan1 = same");Serial.println("");
Serial.print("Fan2 = same");Serial.println("");
Serial.print("Fan3 = same");Serial.println("");
Serial.print("Fan4 = same");Serial.println(""); 
}

void one(){
Serial.println("one");
Serial.print("Fan1 = ");Serial.println(high);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(low); 
}

void two(){
Serial.println("two");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(high);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(low); 
}
void three(){
Serial.println("three");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(high);
Serial.print("Fan4 = ");Serial.println(low); 
}

void four(){
Serial.println("four");
Serial.print("Fan1 = ");Serial.println(low);
Serial.print("Fan2 = ");Serial.println(low);
Serial.print("Fan3 = ");Serial.println(low);
Serial.print("Fan4 = ");Serial.println(high); 
}


void hover(int x,int y){
  flagx = 0;
  flagy = 0;
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  accelerometer_x2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z2 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L) 
  xAng2 = map(accelerometer_x2,minVal,maxVal,-90,90);
  yAng2 = map(accelerometer_y2,minVal,maxVal,-90,90);
  zAng2 = map(accelerometer_z2,minVal,maxVal,-90,90);
  x2= RAD_TO_DEG * (atan2(-yAng2, -zAng2)+PI);
  y2= RAD_TO_DEG * (atan2(-xAng2, -zAng2)+PI);
  z2= RAD_TO_DEG * (atan2(-yAng2, -xAng2)+PI);

  Serial.print("AngleX= "); Serial.println(x2);
  Serial.print("AngleY= "); Serial.println(y2);
  Serial.print("AngleZ= "); Serial.println(z2);
  if(x2 > 180){
    x2 = 360 - x2;
    flagx = 1;
  }
  if(y2 > 180){
    y2 = 360 - y2;
    flagy = 1;
  }
  int xd,yd;
  xd = x2 - x;
  yd = y2 - y;
  if(xd <= 20 && yd <= 20){
    constant();
  }
  else if(xd >20 && yd <= 20){
    if(flagx == 1)
    forward();
    else
    backward();
  }
  else if(yd >20 && xd <= 20){
    if(flagy == 1)
    right();
    else
    left();
  }
  else if(yd > 20 && xd > 20){
    if(flagx == 1 && flagy == 1){
      four();
    }
    else if(flagx == 1 && flagy == 0){
      three();
    }
    else if(flagx == 0 && flagy == 1){
      one();
    }
    else if(flagx == 0 && flagy == 0){
      two();
    }
  }
  Serial.println(" ");
  //delay(1000);
}




void checkLogic() {
  if (pinValue == 1) {
    hover(0,0);
  } else
    Serial.println("Hover stopped");
}




//SETUP
void setup()
{
  //MPU
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  //Blynk
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //timer.setInterval(1000L, checkLogic);
}

//BUTTONS
BLYNK_WRITE(V0) // V0 is the number of Virtual Pin  
{
  if (param.asInt()) //button pushed
  {
    left();
  } 
  else { //button released
  }  
}
BLYNK_WRITE(V1)   
{
  if (param.asInt())
  {
    right();
  } 
  else {
  } 
}
BLYNK_WRITE(V2)  
{
  if (param.asInt())
  {
    forward();
  } 
  else {
  } 
}
BLYNK_WRITE(V3)  
{
  if (param.asInt())
  {
    backward();
  } 
  else {
  }
}
BLYNK_WRITE(V4)  
{
  if (param.asInt())
  {
    up();
  } 
  else {
  }
}

BLYNK_WRITE(V5)  
{
  if (param.asInt())
  {
    down();
  } 
  else {
  }
}

BLYNK_WRITE(V6)  
{
  pinValue = param.asInt();
  if(pinValue == 1){
  timerId = timer.setInterval(1000L, checkLogic);
  timer.enable(timerId);
  }
  else{
    timer.disable(timerId);
  }
}


//LOOP

void loop()
{
  Blynk.run();
  timer.run();
}
