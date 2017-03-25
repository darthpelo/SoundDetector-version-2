#include <Helper.h>
#include "DFRobotDFPlayerMini.h"

Helper::Helper()
// Base library type
{
}

/*
  Store microphone samples data

  @param value1 the first sample value
  @param value2 the second sample value
*/
void Helper::setValues(int value1, int value2) {
  first = value1;
  second = value2;
}

/*
  Return the difference between the second sample and the first.

  @return the difference
*/
int Helper::diff() {
  return second - first;
}

/*
  Return the difference between the first sample and the second.

  @return the difference
*/
int Helper::invertDiff() {
  return first-second;
}

bool Helper::getFlag() {
  return flag;
}

void Helper::setFlag(bool value) {
  flag = value;
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
