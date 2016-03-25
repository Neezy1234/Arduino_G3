
test(wallDetected) 
{
  boolean obstacle = detectObstacle(130);
  assertEqual(true, obstacle);
}

test(wallNotDetected)
{
  boolean obstacle = detectObstacle(90);
  assertEqual(false, obstacle);
}
