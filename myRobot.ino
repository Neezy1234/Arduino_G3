#include <Servo.h>

Servo servo1;
Servo servo2;
const int buttonPin = PIN_SW0;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:

  //pinMode(/**/, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  servo1.attach(16);
  servo2.attach(17);

  servo1.write(90);
  servo2.write(90);
  
  Serial.begin(115200);
  while(!Serial) ;
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
    char input = Serial.read();
    Move(input);
   }
}

void remoteMove() {
//Read inputs received on the webserver and call the move function to move accordingly 

  //char input = ??;
  
  //Move(input);
}

void loop() {
  // put your main code here, to run repeatedly
  serialMove();
}
