#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Helper.h"
#include "Player.hpp"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int micPin = A0;

int micValue0 = 0;
int micValue1 = 0;

Helper helper(0,0);

typedef Singleton<Player> PlayerSingleton;   // Global declaration

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  PlayerSingleton::Instance()->finished();

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
}

void loop()
{
  if (PlayerSingleton::Instance()->isPlaying() == false) {
    micValue0 = analogRead(micPin);
    delay(1);
    micValue1 = analogRead(micPin);
    helper.setValues(micValue0, micValue1);
  } else {
    helper.setValues(0, 0);
  }

  if (helper.equal(2) && PlayerSingleton::Instance()->isPlaying() == false) {
    PlayerSingleton::Instance()->startPlay();

    myDFPlayer.play(helper.randint(29) + 1);
  }

  if (myDFPlayer.readType() == DFPlayerPlayFinished) {
    PlayerSingleton::Instance()->finished();
    myDFPlayer.pause();
  }

  if (myDFPlayer.available()) {
    //Print the detail message from DFPlayer to handle different errors and states.
    printDetail(myDFPlayer.readType(), myDFPlayer.read());
  }
}
