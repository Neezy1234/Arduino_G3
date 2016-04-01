/*
//TESTS DE DETECTION D'OBSTACLES
test(obstacleDetected) 
{
  //Test "Obstacle detecte"
  boolean obstacle = detectObstacle(130);
  assertEqual(true, obstacle);
}

test(noObstacleDetected)
{
  //Test "Pas d'obstacle"
  boolean obstacle = detectObstacle(90);
  assertEqual(false, obstacle);
}

//TESTS DE CHANGEMENT ALLUME/ETEIND
test(switchOff) 
{
  //Test "Allume -> Eteind"
  boolean power = switchPower(true, LOW);
  assertEqual(false, power);
}

test(switchOn)
{
  //Test "Eteind -> Allume"
  boolean power = switchPower(false, LOW);
  assertEqual(true, power);
}

//TESTS DE DEPLACEMENT
test(moveForward)
{
  //Test "Avance"
  Move('z');

  assertEqual(0, servo1.read());
  assertEqual(180, servo2.read());
}

test(moveBackward)
{
  //Test "Recule"
  Move('s');

  assertEqual(180, servo1.read());
  assertEqual(0, servo2.read());
}

test(turnLeft)
{
  //Test "Tourne a gauche"
  Move('q');

  assertEqual(180, servo1.read());
  assertEqual(180, servo2.read());
  Move('p'); //pause les servo après le test
}

test(turnRight)
{
  //Test "Tourne a droite"
  Move('d');

  assertEqual(0, servo1.read());
  assertEqual(0, servo2.read());
  Move('p'); //pause les servo après le test
}*/
