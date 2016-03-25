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
#include <SPI.h>


//Declaration des variables globales (etats, valeurs...)
int grayScale = 0;

//Declaration des PINs
const int grayScalePin = A0;      //Numéro du PIN du capteur de niveaux de gris

void setup()
{
      Serial.begin(115200); 
}
void loop()
{
      //Change la resolution de la lecture analogue (8 bits)
      analogReadResolution(8);
      grayScale=analogRead(grayScalePin);   
      Serial.println(grayScale);//print the value to serial        
      delay(100);
}
