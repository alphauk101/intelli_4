#ifndef __BGF__
#define __BGF__

#include "Arduino.h"

class bargraph
{
  public:
    void init_bargraph(int);
    void spin(void);
    void displayTemp(double);
    void turnOff(void);
    void allOn(void);
  private:
    int BGPIN;
    void setSegment(int);
};
#endif
