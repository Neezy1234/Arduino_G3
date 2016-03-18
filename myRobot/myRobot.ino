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

void Move(char input) {
//Move forward, backward, right and left depending on the input.
//Valid input:
// z(forward)
// s(backward)
// q(left)
// d(right)

  switch(input){
      case 'z' :
        // Move forward;
        servo1.write(0);
        servo2.write(180);
        break;
      case 's':
        // Move backward;
        servo1.write(180);
        servo2.write(0);
        break;
      case 'q' :
        // Move left;
        servo1.write(0);
        servo2.write(0);
        break;
      case 'd':
        // Move right;
        servo1.write(180);
        servo2.write(180);
        break;
      case 'p':
        // Pause/Stop both servos
        servo1.write(90);
        servo2.write(90);
        break;
    }
}

void serialMove() {
//Read the serial inputs and call the move function to move accordingly

  if(Serial.available()) {   
    input = Serial.read();
    Serial.println(input);
    Move(input);
   }
}

void loop() {
  // put your main code here, to run repeatedly

  serialMove();
  
}

