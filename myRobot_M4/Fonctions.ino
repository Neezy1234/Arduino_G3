/* sortirLabComplique(int n, char sens) {
  // z == devant s == derrière d == droite  q == gauche
  // si sens choisi == q Verification == 1         si sens choisi == d Verification == 0

  // on a besoin du sens inverse choisi (le char d ou q)
  // && si sens choisi == d on doit vérifier la présence à gauche && inversement
  char sensInverse;
  int coteVerification;
  if ('q' == sens) {
    sensInverse = 'd';
    coteVerification = 1
  }
  else
    sensInverse = 'q';

  // On lit les valeurs des capteurs
  frontSensor = analogRead(frontSensorPin);
  //backSensor  = analogRead(backSensorPin);
  leftSensor  = analogRead(leftSensorPin);
  rightSensor = analogRead(rightSensorPin);

  if (n == 0 && obstacleFront == false) {
    Move('z'); //Avance
  }
  else if (n == 0 && obstacleFront == false) {
    Move(sens);
    --n;
  }
  else if (coteVerification) {

  }
  }

  //On lit les valeurs des capteurs

  frontSensor = analogRead(frontSensorPin);
  //backSensor  = analogRead(backSensorPin);
  leftSensor  = analogRead(leftSensorPin);
  rightSensor = analogRead(rightSensorPin);


  obstacleFront = detectObstacle(frontSensor);
  obstacleLeft = detectObstacle(leftSensor);
  obstacleRight = detectObstacle(RightSensor);
  //obstacle1 = detectObstacle(frontSensor);

  return n;
  }*/
void Move(char input) {
  //Move forward, backward, right and left depending on the input.
  //Valid input:
  // z(forward)
  // s(backward)
  // q(left)
  // d(right)

  switch (input) {
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

boolean detectObstacle(int sensor, int sensibilite) {

  boolean result;

  //On indique si un obstacle est present devant
  if (sensor > sensibilite ) {
    result = true;
  }
  else {
    result = false;
  }

  return result;
}
int sens = 120;

void sortirLab() {
  // On lit les valeurs des capteurs

  obstacleFront = detectObstacle(frontSensor, sens);
  obstacleLeft = detectObstacle(leftSensor, sens);
  obstacleRight = detectObstacle(rightSensor, sens);
  //obstacleBack = detectObstacle(backSensor, sens);

  frontSensor = analogRead(frontSensorPin);
  //backSensor  = analogRead(backSensorPin);
  leftSensor  = analogRead(leftSensorPin);
  rightSensor = analogRead(rightSensorPin);

  /*
    Serial.println("Front:");
    Serial.println(frontSensor);
    Serial.println("Right:");
    Serial.println(rightSensor);
    Serial.println("Left:");
    Serial.println(leftSensor);
  */

/*
  if (obstacleFront == true) {
     if (obstacleLeft == false) {
       Move('q');
     }
     else {
       Move('d');
     }
    }
    else if (obstacleLeft == true) {
     if (obstacleRight == false) {
       Move('d');
     }
     else {
       Move('z');
     }
    }
    else if (obstacleRight == false){
     Move('d');
    }
    else {
     Move('z');
    }
    }

*/ 
  if (obstacleRight == true) {
    if (obstacleFront == false) {
      sens = 120;
      Move('z');
    }
    else {
      sens = 110;
      Move('q');
    }
  }

  else if (obstacleFront == true) {
    if (obstacleRight == true) {
      sens = 110;
      Move('q');
    }
    else {
      sens = 110;
      Move('d');
    }
  }

  else if (obstacleRight == false) {
    sens = 110;
    Move('d');
  }
}
