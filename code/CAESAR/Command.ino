void executeCommand(char *message)
{
  char mode = message[0];
  char attribute = message[1];
  bool sign = (message[2] == '+');
  int value = (int)message[3];
  if (!sign)
    value = 0 - value;

  switch (mode)
  {
    case 'M':
    case 'm':
      setMotor(attribute, value);
      break;
    default:
      Serial.println("Error: Invalid command.");
      break;
  }  
}
