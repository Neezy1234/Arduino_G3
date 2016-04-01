/*
 * Projet Agilite/Application embarque
 * IUT Informatique - Aix-en-Provence
 * 
 * MISSION 3 - SUIVRE UNE LIGNE BLANCHE SUR SOL FONCÉ 
 * 
 * Groupe 3 :
 * Yasmine AMAR, Valentin COURDY,
 * Sandro ENCISO, Justin FAYARD
 * Hafid HOUT, Alexis MARTIN
 * 
 */


#include <ArduinoUnit.h>
#include <SPI.h>
#include <Servo.h>
#include <WiFi101.h>
#include <BlynkSimpleWiFiShield101.h>

//Declaration des servos 1 et 2
Servo servo1;
Servo servo2;

char auth[] = "33ea8e08e9614f4d920db366e20ce38c"; // Put your Auth Token here. (see Step 3 above)

//Declaration des variables globales (etats, valeurs...)
int grayScale = 0;
boolean power = false;   
int buttonState = 0;       

//Declaration des PINs
const int buttonPin = PIN_SW0;    // Numero du pin du bouton
const int ledPin    = PIN_LED_13; // Numero du pin de la LED
const int grayScalePin = A4;      //Numéro du PIN du capteur de niveaux de gris

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);

  //"Initialise" les servo 1 et 2
  servo1.attach(16); //roue 
  servo2.attach(17); //roue  

  //Position des servos à l'arret/par défaut
  servo1.write(90);
  servo2.write(90);

  //Initialisation du serial monitor
  Serial.begin(115200);
  while(!Serial){}
  
}
void loop()
{
  //On lit l'etat du bouton (appuye ou pas)
  buttonState = digitalRead(buttonPin);

  //Si le bouton est appuye on change le boolean "power"

  power = switchPower(power, buttonState);

  //Si "power" est true on effectue le code sinon on fait rien
  if(power == true) 
  {
      grayScale=analogRead(grayScalePin);  

      Serial.println(grayScale);
      
      if (detectLine(grayScale))
      {
           Move('d');
      }
      else
      {
           Move('q');
      }
      
      delay(100);
  }
}
