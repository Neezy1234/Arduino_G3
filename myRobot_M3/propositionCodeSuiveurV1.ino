
#include<SPI.h>


const int lightSensorPin = A4;    // Numero de pin du capteur suiveur de ligne
int lightSensor= 0;


boolean detectLigne(int sensor){
  boolean result;
  if (sensor > 340)
    result=true;
  else
    result=false;
}

void suiveurLigne(int sensor){

  if (detectLigne(lightSensorPin)){
    move('z');
  }
  else{
   move('q');
   delay(300);
   move('z);
   delay(100);
  }  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSensor=analogRead(lightSensorPin);
  grayScale=analogRead(grayScalePin);
  suiveurLigne();
  }
