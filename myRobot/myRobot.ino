/*
 * Projet Agilite/Application embarque
 * IUT Informatique - Aix-en-Provence
 * 
 * Groupe 3 :
 * Yasmine AMAR, Valentin COURDY,
 * Sandro ENCISO, Justin FAYARD
 * Hafid HOUT, Alexis MARTIN
 * 
 */


#include <ArduinoUnit.h>
#include <Servo.h>
#include <SPI.h>

//Declaration des servos 1 et 2
Servo servo1;
Servo servo2;

//Declaration des variables globales (etats, valeurs...)
int buttonState = 0;   
int frontSensor = 0;
int backSensor = 0;
int leftSensor = 0;
int rightSensor = 0;

boolean power = false;          
boolean obstacle = false;


//Declaration des PINs
const int buttonPin = PIN_SW0;    // Numero du pin du bouton
const int ledPin    = PIN_LED_13; // Numero du pin de la LED
const int frontSensorPin = A0;    // Numero du pin du capteur avant
const int backSensorPin  = A1;    // Numero du pin du capteur arriere
const int leftSensorPin  = A2;    // Numero du pin du capteur gauche
const int rightSensorPin = A3;    // Numero du pin du capteur droit

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT_PULLUP);

  //"Initialise" les servo 1 et 2
  servo1.attach(16);
  servo2.attach(17);

  //Position des servos à l'arret/par défaut
  servo1.write(90);
  servo2.write(90);

  //Initialisation du serial monitor
  Serial.begin(115200);
  while(!Serial){}

}

void loop() {
  // put your main code here, to run repeatedly

  //On lit l'etat du bouton (appuye ou pas
  buttonState = digitalRead(buttonPin);

  //Si le bouton est appuye on change le boolean "power"
  if(buttonState == LOW) {
    power = !power;
    if(power == false) Move('p'); //Pause des servos
    delay(500);
  }

  //Si "power" est true on effectue le code sinon on fait rien
  if(power == true) {

    //Change la resolution de la lecture analogue (8 bits)
    analogReadResolution(8);

    //On lit les valeurs des capteurs
    frontSensor = analogRead(frontSensorPin);
    /*
    backSensor  = analogRead(backSensorPin);
    leftSensor  = analogRead(leftSensorPin);
    rightSensor = analogRead(rightSensorPin);
    */
    
    //On affiche les valeurs des capteurs
    Serial.print("Front sensor : ");
    Serial.println(frontSensor);
    /*
    Serial.print("Back sensor : ");
    Serial.println(backSensor);
    Serial.print("Left sensor : ");
    Serial.println(leftSensor);
    Serial.print("Right sensor : ");
    Serial.println(rightSensor);
    */

    //On indique si un obstacle est present devant
    if(frontSensor > 120 ) {
      obstacle = true;
    }
    else {
      obstacle = false;
    }

    //Si il y a un obstacle on s'arrete sinon on avance
    if(obstacle == false) {
      Move('z'); //Avance
    }
    else {
      Move('p'); //Pause
    }
  }

}

