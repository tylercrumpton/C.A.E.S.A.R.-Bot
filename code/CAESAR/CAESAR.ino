#define MESSAGE_LENGTH 7
#define USE_SONAR 0 //Set to 1 if the sonar is to be used, else 0

const int NORMAL_SPEED = 75; //forward speed while searching
const int MAXIMUM_SPEED = 75; //full speed while attacking!
const int SEARCH_DISTANCE = 50; //sonar dist. usually in cm.
const int TURN_SPEED = 75; //speed turns are made.

unsigned int sensorValues[1];

void setup()
{
  serialSetup();
//rfSetup();
  motorSetup();
  calibrateLineSensor();
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  
  //Ready timer 5 seconds THE FIRST TIME IN THE LOOP!
  Serial.println("Waiting...");
  delay(5000);
  Serial.println("Go!");
}

void loop()
{
  // Read any commands from the serial buffer
  //readSerial();
  
  // Read any commands from the RF buffer
  //readRF();
  
  // Begin moving forward
  Serial.print("Driving forward, ");
  driveForward();
  
  // If edge is found then turn about 30 degrees and continue 
  checkForEdge();
  
  // If opponent is visible go after them!
  if(checkForOpponent())
  {
    driveForwardFast(); 
  }

  Serial.print("Line sensor value: ");
  Serial.println(sensorValues[0]);
}

//Sets the current drive speed to "normal speed, forward"
void driveForward()
{
  moveForward(NORMAL_SPEED);
}

//Sets the current drive speed to "max speed, forward"
void driveForwardFast()
{
  moveForward(MAXIMUM_SPEED);
}

//Checks for the white ring by reading the line sensors. If 
//found, it will turn around a certain amount then continue,
//UNLESS the sonar picked up something - then don't turn!
void checkForEdge()
{
  boolean edgeDetected = getEdgeDetect();
  boolean botDetected = checkForOpponent();
  if(edgeDetected && !botDetected)
  {
    Serial.println("Found edge! Turning around.");
    brake(); //stop
    delay(1000); //wait 1 sec
    move(0-MAXIMUM_SPEED, 0-MAXIMUM_SPEED); //back up fast
    delay(500); //wait half a sec
    turnRight(400, TURN_SPEED);  //turn right a little bit   
  }
  else
  {
    Serial.println("No edge was found. OR enemy was detected!");
  }
}

//Checks for any object detected by the sonar sensor within 
//a certain distance. It will return true if it finds 
//something.
boolean checkForOpponent()
{
  bool result = false;
#if USE_SONAR == 1
  int sonarDist = getSonarDist();
  if(sonarDist <= SEARCH_DISTANCE)
  {
     //something was found!
     Serial.println("ENEMY DETECTED!");
     result = true;
  }
#endif // #if USE_SONAR == 1
  return result;
}
