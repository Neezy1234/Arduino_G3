#include <BlynkApiArduino.h>
#include <BlynkApiParticle.h>
#include <BlynkParticle.h>
#include <BlynkSimpleCC3000.h>
#include <BlynkSimpleEnergiaWiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <BlynkSimpleEsp8266_SSL.h>
#include <BlynkSimpleEthernet.h>
#include <BlynkSimpleEthernet2.h>
#include <BlynkSimpleEthernetV2_0.h>
#include <BlynkSimpleIntelEdisonWiFi.h>
#include <BlynkSimpleLinkItONE.h>
#include <BlynkSimpleMKR1000.h>
#include <BlynkSimpleParticle.h>
#include <BlynkSimpleRBL_CC3200.h>
#include <BlynkSimpleRBL_WiFi_Mini.h>
#include <BlynkSimpleRedBear_Duo.h>
#include <BlynkSimpleSerial.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <BlynkSimpleTinyDuino.h>
#include <BlynkSimpleTI_CC3200_LaunchXL.h>
#include <BlynkSimpleTI_TivaC_Connected.h>
#include <BlynkSimpleUIPEthernet.h>
#include <BlynkSimpleUserDefined.h>
#include <BlynkSimpleWifi.h>
#include <BlynkSimpleWiFiShield101.h>
#include <BlynkSimpleWiFiShield101_SSL.h>
#include <BlynkSimpleWiFly.h>
#include <BlynkSimpleWildFire.h>
#include <BlynkSimpleYun.h>
#include <BlynkWidgets.h>
#include <WidgetBridge.h>
#include <WidgetLCD.h>
#include <WidgetLED.h>
#include <WidgetRTC.h>
#include <WidgetSD.h>
#include <WidgetTerminal.h>

#include <ArduinoUnit.h>

#include <Servo.h>
#include <SPI.h>

Servo servo1;
Servo servo2;
const int buttonPin = PIN_SW0;
int buttonState = 0;              
char input;                       // input du port Serial afin de controller les Servo

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT_PULLUP);

  //"Initialise" les servo 1 et 2
  servo1.attach(16);
  servo2.attach(17);

  //Position des servos à l'arrêt/par défaut
  servo1.write(90);
  servo2.write(90);

  //Initialisation du serial monitor
  Serial.begin(115200);
  while(!Serial){}

}

void loop() {
  // put your main code here, to run repeatedly
  Move('z');  
}

