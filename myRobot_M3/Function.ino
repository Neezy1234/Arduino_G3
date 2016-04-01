boolean detectLine(int grayScale) {

  boolean result;
  
  //On indique si un obstacle est present devant
  if(grayScale < 250 ) {
    result = true;
  }
  else {
    result = false;
  }

  return result;
}

void Move(char input) {
//Move slowly to the right and slowly to the left depending on the input.
//Valid input:
// q(left)
// d(right)
// p(pause)

  switch(input){
      case 'd' :
        // Move right;
        servo1.write(0);
        servo2.write(90);
        break;
      case 'q':
        // Move left;
        servo1.write(89);
        servo2.write(180);
        break;
      case 'p':
        // Pause/Stop both servos
        servo1.write(90);
        servo2.write(90);
        break;
     }
}

boolean switchPower(boolean powerState, int buttonValue){
  
  if(buttonValue == LOW) {
    powerState = !powerState;
    if(powerState == false) Move('p'); //Pause des servos
    delay(500);
  }

  return powerState;
}
