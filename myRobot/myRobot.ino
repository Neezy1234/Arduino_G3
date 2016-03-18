#include <ArduinoUnit.h>

#include <Servo.h>
#include <SPI.h>

Servo servo1;
Servo servo2;

int buttonState = 0;     
boolean power = false;          
boolean obstacle = false;

const int buttonPin = PIN_SW0;    // the number of the pushbutton pin
const int ledPin    = PIN_LED_13; // the number of the LED pin

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT_PULLUP);

  //pinMode(A0, OUTPUT);
  //digitalWrite(A0, HIGH);

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

  buttonState = digitalRead(buttonPin);

  analogReadResolution(8);
  Serial.print(", 8-bit : ");
  Serial.println(analogRead(A0));
  
  if(buttonState == LOW) {
    power = !power;
    if(power == false) Move('p');
    delay(500);
  }

  if(power == true) {
    if(analogRead(A0) > 120 ) {
      obstacle = true;
    }
    else {
      obstacle = false;
    }
    
    if(obstacle == false) {
      Move('z');  
    }
    else {
      Move('p');
    }
  }
  else {}

  
}

