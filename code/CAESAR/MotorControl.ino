// Pin Declarations:
const int PIN_IN1 = 2; // Direction for Motor1
const int PIN_IN2 = 3; // Speed for Motor1
const int PIN_IN3 = 4; // Direction for Motor2
const int PIN_IN4 = 5; // Speed for Motor2

// Settings:
const int ACCEL_DELAY = 0; // Modifies the delay between speed changes (0 = instant change in speed)
const int TURN_SPEED = 255; //speed turns are made.

// Globals:
int leftSpeed  = 0; // Current speed of left motor (range: -255 to 255)
int rightSpeed = 0; // Current speed of right motor (range: -255 to 255)

void motorSetup()
{
  // Set pinModes to OUTPUT:
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);  
  pinMode(PIN_IN4, OUTPUT);  
  
  // Make sure all motors are stopped:
  digitalWrite(PIN_IN1, LOW);  
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  
}

// Performs are "hard" stop by ignoring acceleration values.
void brake()
{
  // Set both motor speeds to zero:
  leftSpeed = 0;
  rightSpeed = 0;
  
  // Stop all motors:
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
 
}

// Set the speed of each motor. (CURRENTLY DOES NOT IMPLEMENT ACCELERATION)
void move(int lSpeed, int rSpeed)
{
  // Make sure speeds are in the correct range:
  leftSpeed = constrain(lSpeed, -255, 255);
  rightSpeed = constrain(rSpeed, -255, 255);
  
  // Case where left speed is negative (backwards):
  if(leftSpeed < 0)
  {
    digitalWrite(PIN_IN1, HIGH); // Set direction to backwards.
    analogWrite(PIN_IN2, -leftSpeed); // Set backwards speed.
  }
  // Case where left speed is negative (backwards):
  else if(leftSpeed > 0)
  {
    digitalWrite(PIN_IN1, LOW); // Set direction to forward.
    analogWrite(PIN_IN2, leftSpeed); // Set forward speed.
  }
  // Case where left speed is zero:
  else
  {
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);
  }
  
  // Case where right speed is negative (backwards):
  if(rightSpeed < 0)
  {
    digitalWrite(PIN_IN3, HIGH); // Set direction to backwards.
    analogWrite(PIN_IN4, -rightSpeed); // Set backwards speed.
  }
  // Case where right speed is negative (backwards):
  else if(rightSpeed > 0)
  {
    digitalWrite(PIN_IN3, LOW); // Set direction to forward.
    analogWrite(PIN_IN4, rightSpeed); // Set forward speed.
  }
  // Case where right speed is zero:
  else
  {
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, LOW);
  }
}

void turnRight(int timeInMilliSecs, int speedAsInt)
{
  //this method's job is to turn the robot to the right 
  //for the given number of seconds at the given speed.
  move(speedAsInt, 0-speedAsInt); //turn left wheel forward and the right one back!
  delay(timeInMilliSecs);
}

void turnLeft(int timeInMilliSecs, int speedAsInt)
{
  //this method's job is to turn the robot to the left 
  //for the given number of seconds at the given speed.
  move(0-speedAsInt, speedAsInt); //turn right wheel forward and the left one back!
  delay(timeInMilliSecs);
}
