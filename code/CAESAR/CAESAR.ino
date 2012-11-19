#define MESSAGE_LENGTH 7

//this flag is to make sure the bot
// waits 5 seconds the first time through.
boolean firstTimeThrough;

const int NORMAL_SPEED = 75; //forward speed while searching
const int MAXIMUM_SPEED = 75; //full speed while attacking!
const int SEARCH_DISTANCE = 50; //sonar dist. usually in cm.
const int TURN_SPEED = 75; //speed turns are made.

unsigned int sensorValues[1];

void setup()
{
  firstTimeThrough = true;
  serialSetup();
//  rfSetup();
  motorSetup();
  calibrateLineSensor();
<<<<<<< HEAD
=======
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
>>>>>>> Changes made at TEDxYouth
}

void loop()
{
  //readSerial();
  //readRF();
  
  //Ready timer 5 seconds THE FIRST TIME IN THE LOOP!
  if(firstTimeThrough)
  {
    Serial.println("Waiting...");
    firstTimeThrough = false;
    delay(5000);
    Serial.println("Go!");
  }
  
  Serial.print("line sensor value: ");
  Serial.println(sensorValues[0]);
  
  //now start looking around
  Serial.print("Driving forward, ");
  driveForward();
  
  //if edge found then turn 30 degrees and continue searching
  checkForEdge();
  
  //look left and right for opponent??
  
  //if opponent found go after them!
  if(checkForOpponent())
  {
    driveForwardFast(); 
  }
  
} //end loop()

void driveForward()
{
  //this method makes the bot drive forward a normal speed while looking around.
  moveForward(NORMAL_SPEED);
}

void driveForwardFast()
{
  //this method will start the motors turning forward "fast".
  //"fast" is defined as some maximum speed we determine.
  moveForward(MAXIMUM_SPEED);
}

void checkForEdge()
{
  //this method will check the edge sensors for the white edge.
  //if found it will turn around the pre-set amount then exit.
  //the first method called in the loop is to drive foward so
  // that's taken care of there.
  //UNLESS the sonar picked up something then don't turn!
  boolean edgeDetected = getEdgeDetect();
  //boolean botDetected = checkForOpponent();
  boolean botDetected = false; //disable for now.
  if(edgeDetected && !botDetected)
  {
    Serial.println("Found edge! Turning around.");
<<<<<<< HEAD
    turnRight(400, MAXIMUM_SPEED);     
  }
  else
  {
    Serial.println("No edge was found.");
  }
=======
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
>>>>>>> Changes made at TEDxYouth
}

boolean checkForOpponent()
{
  //this method will check for any object the sonar picks up
  //within the given distance.  It will then return true if
  // it finds something!
  int sonarDist = getSonarDist();
  if(sonarDist <= SEARCH_DISTANCE)
  {
     //something was found!
     Serial.println("ENEMY DETECTED!");
     return true;
  }
  else
  {
    Serial.println("no enemies sighted.");
    return false;
  }
}
