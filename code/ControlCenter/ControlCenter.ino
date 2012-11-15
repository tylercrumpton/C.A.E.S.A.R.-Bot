#define MESSAGE_LENGTH 7

void setup()
{
  serialSetup();
  rfSetup();
}

void loop()
{
  readSerial();
  readRF();
}
