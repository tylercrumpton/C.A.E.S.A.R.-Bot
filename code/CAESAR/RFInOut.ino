#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t readPipe = 0xF0F0F0F0E1LL;
const uint64_t writePipe = 0xF0F0F0F0D2LL;

void rfSetup()
{
  radio.begin();
  
  //Increase the delay between retries & # of retries
  radio.setRetries(15,15);
  
  radio.openReadingPipe(1,readPipe);
  radio.openWritingPipe(writePipe);
  radio.startListening();
}
void readRF()
{
  // if there is data ready
  if (radio.available())
  {
    // Char array to store the message
    char commandString[MESSAGE_LENGTH];
    
    // Dump the payloads until we've gotten everything
    bool done = false;
    while (!done)
    {
      // Fetch the payload, and see if this was the last one.
      done = radio.read(&commandString, MESSAGE_LENGTH);
      
      // Print the message to Serial:
      Serial.print("Received RF command: ");
      for(int i=0; i<MESSAGE_LENGTH; i++)
      {
        Serial.print(commandString[i]);
      }
      Serial.print("\r\n");
      
      // Run the command we received:
      executeCommand(commandString);
    }
  }
}
void sendRF(char* payload, int length)
{
  // First, stop listening so we can talk.
  radio.stopListening();
  
  // Send the string payload.  This will block until complete
  bool ok = radio.write(payload, length);
  
  if (ok)
  {
    Serial.print("Message sent: ");
    for(int i=0; i<length; i++)
    {
      Serial.print(payload[i]);
    }
    Serial.print("\r\n");
  }
  else
  {
    Serial.print("Message failed to send: ");
    for(int i=0; i<length; i++)
    {
      Serial.print(payload[i]);
    }
    Serial.print("\n");
  }

  // Now, continue listening
  radio.startListening();
}
