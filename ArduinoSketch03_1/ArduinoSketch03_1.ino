/*
 RFID Reader
 */

#include <SoftwareSerial.h> // Bring in the software serial library 
const int tagLength = 10;    // each tag ID contains 10 bytes 
const int startByte = 0x0A;  // Indicates start of a tag
const int endByte   = 0x0D;  // Indicates end of a tag

char tagID[tagLength + 1];   // array to hold the tag you read 

const int rxpin = 6; // Pin for receiving data from the RFID reader
const int txpin = 7; // Transmit pin; not used
SoftwareSerial rfidPort(rxpin, txpin); // create a Software Serial port 
void setup() {
  // begin serial communication with the computer
  Serial.begin(9600);

  // begin serial communication with the RFID module
  rfidPort.begin(2400);
}

void loop() {
  // read in and parse serial data:
  if (rfidPort.available() > 0) { // 

    if (readTag()) { // 
      Serial.println(tagID);
    }
  }
}

/*
 This method reads the tag, and puts its
 ID in the tagID
 */
boolean readTag() {
  char thisChar = rfidPort.read(); 
  if (thisChar == startByte) {   
    if (rfidPort.readBytesUntil(endByte, tagID, tagLength)) {      
      return true;
    }
  }
  return false;
}

