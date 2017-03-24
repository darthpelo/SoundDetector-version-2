#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Helper.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int micPin = A0;

int micValue0 = 0;
int micValue1 = 0;

bool isPlaying = false;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Configure Microphone----
  pinMode(micPin, INPUT);

  //----Read imformation----
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(myDFPlayer.readVolume()); //read current volume
  Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
}

void loop()
{
  micValue0 = analogRead(micPin);
  delay(1);
  micValue1 = analogRead(micPin);

  if (((micValue1-micValue0>3) || (micValue0-micValue1>3)) &&
       isPlaying == false ) {
    isPlaying = true;
    myDFPlayer.play(4);
  }

  if (myDFPlayer.readType() == DFPlayerPlayFinished) {
    isPlaying = false;
  }

  if (myDFPlayer.available()) {
    //Print the detail message from DFPlayer to handle different errors and states.
    printDetail(myDFPlayer.readType(), myDFPlayer.read());
  }
}
