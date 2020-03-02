#include "FirebaseESP8266.h"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

const int trigPin1 = 4; //D2
const int echoPin1 = 0; //Front D3

const int trigPin2 = 16; //D0
const int echoPin2= 5; //Right D1

const int trigPin3 = 12; //D6
const int echoPin3= 13; //Back D7

const int trigPin4 = 2; //D4
const int echoPin4 = 14; //Left D5

#define FIREBASE_HOST "https://firebird-caa83.firebaseio.com/"
#define FIREBASE_AUTH "uy1FPhVe1FQsoVR7CH8KI5NftWCvd0hz1kwfGFTw"

char ssid[] = "OnePlus 5T";
char pass[] = "devashish2809";
char auth[] = "gUXex9GMM2m5H5MLoOB-Ro6byeMeJNWC";
String path = "/ultrasonic_value";

long durationLeft, durationRight, durationFront, durationBack;
long distanceLeft, distanceRight, distanceFront, distanceBack, initialBackDistance, distanceCovered;
//int t=0;
int i=0,j=0,count=0;
long distances[100];
int pinValue;
FirebaseData firebaseData;
FirebaseJson json;

//BLYNK_WRITE(V0)
//{
//  int pinValue = param.asInt();
//  allSensors();
//  if(pinValue == 1){
//    allSensors();
//    traverse();
//  }
//  else{
//    sendFirebase();
//  }
//}

void sendFirebase()
{
  Serial.println("Done taking values now sending");
  Firebase.setInt(firebaseData,path+"/NumberOfValues",i);
  for(j=0;j<i;j=j+1)
  {
    //Serial.println(distances[j]);
   Firebase.setFloat(firebaseData,path+"/Number"+j,distances[j]);
  }
  Serial.println("Done sending value");
}

void traverse()
{
  if(distanceLeft<distanceRight)
{
  while(distanceLeft>10)
  {
    allSensors();
    Serial.println("Hover towards left wall");
    delay(1000);
    initialBackDistance=distanceBack;
  }
  while(distanceBack<1000)//distanceBack<1000 1==1
  {
    allSensors();
    if((9<=distanceLeft<=15) && (distanceFront>=10))
    {
      Serial.println("Hover forward");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
      delay(1000);
    }
    if((distanceLeft>15)&&(distanceFront>=10))
    {
      distanceCovered = distanceBack-initialBackDistance; //+5
      distances[i]=distanceCovered;
      i=i+1;
      Serial.println("Rotate Left by 90 degree");
      delay(4000);
      allSensors(); //this change
      initialBackDistance = distanceBack;
      Serial.println("Start moving");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
//      Serial.println("initttttt Back dist");
//      Serial.println(initialBackDistance);
      distances[i]=1; //one over here is used to denote that the drone has taken a left turn
      i=i+1;
    }
    if((9<=distanceLeft<=15) && (distanceFront<10))
    {
      distanceCovered = distanceBack-initialBackDistance; //+5
      distances[i]=distanceCovered;
      i=i+1;
      Serial.println("Rotate Right by 90 degree");
      delay(4000);
      allSensors(); //this change
      initialBackDistance = distanceBack;
      Serial.println("Start moving");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
//      Serial.println("inniiiittt Back dist");
//      Serial.println(initialBackDistance);
      distances[i]=0; //zero over here is used to denote that the drone has taken a right turn
      i=i+1;
    }
  }
}

else if(distanceLeft>distanceRight)
{
  while(distanceRight>10)
  {
    allSensors();
    Serial.println("Hover towards right wall");
//    Serial.println(distanceRight);
    delay(1000);
    initialBackDistance=distanceBack;
  }
  while(distanceBack<1000)//1==1 distanceBack<1000
  {
    allSensors();
    if((9<=distanceRight<=15) && (distanceFront>=10))
    {
      Serial.println("Hover forward");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
//      Serial.println("Right Value");
//      Serial.println(distanceRight);
//      Serial.println("Front Value");
//      Serial.println(distanceFront);
      delay(1000);
    }
    if((distanceRight>15)&&(distanceFront>=10)) //only one condition?
    {
      distanceCovered = distanceBack-initialBackDistance+5;
      distances[i]=distanceCovered;
      i=i+1;
      Serial.println("Rotate Right by 90 degree");
      delay(4000);
      allSensors(); //this change
      initialBackDistance = distanceBack;
      Serial.println("Start moving");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
      distances[i]=0; //zero over here is used to denote that the drone has taken a right turn
      i=i+1;
    }
    if((9<=distanceRight<=15) && (distanceFront<10))
    {
      distanceCovered = distanceBack-initialBackDistance+5;
      distances[i]=distanceCovered;
      i=i+1;
      Serial.println("Rotate Left by 90 degree");
      delay(4000);
      allSensors(); //this change
      initialBackDistance = distanceBack;
      Serial.println("Start moving");
//      Serial.println("Back dist");
//      Serial.println(distanceBack);
      distances[i]=1; //one over here is used to denote that the drone has taken a left turn
      i=i+1;
    }
  }
}
}

void allSensors()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  durationFront = pulseIn(echoPin1, HIGH);
  distanceFront=durationFront/58.2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  durationRight = pulseIn(echoPin2, HIGH);
  distanceRight=durationRight/58.2;
  //Serial.print(distanceRight);

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  durationBack = pulseIn(echoPin3, HIGH);
  distanceBack=durationBack/58.2;

  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  durationLeft = pulseIn(echoPin4, HIGH);
  distanceLeft=durationLeft/58.2;
}

void setup() {
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);

pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);

Serial.begin(9600); // connect serial
Serial.println("Ultrasonic Started");
Blynk.begin(auth, ssid, pass);
//WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connecting to Wi-Fi");
  /*while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();*/
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop()
{
  //Blynk.run();
  allSensors();
  traverse();
  sendFirebase();
}
