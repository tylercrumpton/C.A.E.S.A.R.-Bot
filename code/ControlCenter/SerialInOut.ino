void serialSetup()
{
  Serial.begin(9600);
}

void readSerial()
{
  if (Serial.available()){
    delay(10); // Pause to get all data
    char buf[MESSAGE_LENGTH];
    buf[0] = Serial.read(); // Get the command mode
    buf[1] = Serial.read(); // Get the command attribute
    int i = 2;
    while(i<MESSAGE_LENGTH){
      buf[i] = Serial.read();
      i++;
    }  
    Serial.flush(); // Discard everything else
    sendRF(buf, MESSAGE_LENGTH); // Send message
  }
}
