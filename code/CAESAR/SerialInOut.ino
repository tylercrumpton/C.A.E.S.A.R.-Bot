void serialSetup()
{
  Serial.begin(9600);
}
void readSerial()
{
  if (Serial.available()){
    delay(10); // Pause to get all data
    char mode = Serial.read(); // Get the command modes
    char attribute = Serial.read(); // Get the command attribute
    int value = readValue(); // Read in the integer value

  }
}

int readValue()
{     
  char buffer[5]; // Received number as string
  int i=0; // Counter for five-digit values
  // Read each digit and add to buffer:
  while(i<5){
    buffer[i] = Serial.read();
    i++;
  }  
  Serial.flush(); // Discard everything else
  
  return atoi(buffer); // Convert string to integer
}

void setMotor(int attribute, char value)
{
  switch(attribute)
  {
    case 'S':
    case 's':
      brake();
      break;
    case 'L':
    case 'l':
      move(value, rightSpeed);
      break;
    case 'R':
    case 'r':
      move(leftSpeed, value);
      break;
    case 'F':
    case 'f':
      move(value, value);
      break;
    default:
      Serial.println("Error: Invalid attribute.");
  }
  Serial.print("Left Motor Speed:");
  Serial.println(leftSpeed);
  Serial.print("Right Motor Speed:");
  Serial.println(rightSpeed);
}
