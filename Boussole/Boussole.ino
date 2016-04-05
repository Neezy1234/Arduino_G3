#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

sensors_event_t old_event;
String state;
int debRT = 0;
float diff = 0;

void setup(void)
{
  Serial.begin(115200);
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  Serial.println("Boussole initialisé...");
}

void loop(void)
{
  //Récupération des données du magnetometre
  sensors_event_t event;
  bno.getEvent(&event);

  //calcul de la différence entre l'état précédent et l'état présent
  
  if(old_event.orientation.x == 0)
    diff = 0;
  else
    diff = event.orientation.x - old_event.orientation.x;
  M
  if(state == "RD" && diff > (float)0.5){
    Serial.print("Rotation de : ");
    Serial.print(event.orientation.x - debRT);
    Serial.println(" Degre sur la droite");
  }
  else if(state == "RG" && diff < (float)-0.5){
    Serial.print("Rotation de : ");
    Serial.print(debRT - event.orientation.x);
    Serial.println(" Degre sur la gauche");
  }
  else if(state != "RD" && diff > 5.0 && event.orientation.x > old_event.orientation.x){
    state = "RD";
    debRT = (float)event.orientation.x;
    Serial.println("Rotation sur la droite en cours");
  }
  else if(state != "RG" && diff < (float)-2.5 && event.orientation.x < old_event.orientation.x){
    state = "RG";
    debRT = (float)event.orientation.x;
    Serial.println("Rotation sur la gauche en cours");
  }

  old_event = event;
   
  delay(100);
}
