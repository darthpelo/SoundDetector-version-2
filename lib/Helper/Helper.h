#ifndef HELPER_h  /* Include guard */
#define HELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

class Helper {
public:
  Helper();

  void setValues(int value1, int value2);

  int diff();

  int invertDiff();

  void printDetail(uint8_t type, int value);
  
private:
  int first, second;
};

#endif // HELPER_H_
