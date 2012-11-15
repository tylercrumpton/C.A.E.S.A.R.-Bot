#define MESSAGE_LENGTH 7

//this flag is to make sure the bot
// waits 5 seconds the first time through.
boolean firstTimeThrough;

const int NORMAL_SPEED = 100; //forward speed while searching
const int MAXIMUM_SPEED = 250; //full speed while attacking!
const int SEARCH_DISTANCE = 50; //sonar dist. usually in cm.

void setup()
{
  firstTimeThrough = true;
  serialSetup();
  rfSetup();
  motorSetup();
}

void loop()
{
  //readSerial();
  //readRF();
  
  //Ready timer 5 seconds THE FIRST TIME IN THE LOOP!
  if(firstTimeThrough)
  {
    firstTimeThrough = false;
    delay(5000);
  }
  
  //now start looking around
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
  move(NORMAL_SPEED, NORMAL_SPEED); 
}

void driveForwardFast()
{
  //this method will start the motors turning forward "fast".
  //"fast" is defined as some maximum speed we determine.
  move(MAXIMUM_SPEED, MAXIMUM_SPEED);
}

void checkForEdge()
{
  //this method will check the edge sensors for the white edge.
  //if found it will turn around the pre-set amount then exit.
  //the first method called in the loop is to drive foward so
  // that's taken care of there.
  //UNLESS the sonar picked up something then don't turn!
  boolean edgeDetected = getEdgeDetect();
  boolean botDetected = checkForOpponent();
  if(edgeDetected && !botDetected)
  {
    turnRight(400, MAXIMUM_SPEED);     
  }
  
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
     return true;
  }
  else
  {
    return false;
  }
}
