#define MESSAGE_LENGTH 7

void setup()
{
  serialSetup();
  rfSetup();
  motorSetup();
}

void loop()
{
  readSerial();
  readRF();
}
