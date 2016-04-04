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
      case 'd' :
        // Move right;
        servo1.write(0);
        servo2.write(0);
        break;
      case 'q':
        // Move left;
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

boolean detectObstacle(int sensor) {

  boolean result;
  
  //On indique si un obstacle est present devant
  if(sensor > 120 ) {
    result = true;
  }
  else {
    result = false;
  }

  return result;
}

boolean switchPower(boolean powerState, int buttonValue){
  
  if(buttonValue == LOW) {
    powerState = !powerState;
    if(powerState == false) Move('p'); //Pause des servos
    delay(500);
  }

  return powerState;
}
