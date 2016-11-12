#include "bargraph.h"

//These are the values I found work best with the RC network on the PWM filtering for the bargraph
const int segment[] = {0, 10, 15, 20, 27, 33, 39, 45, 53, 60, 65, 75, 83, 86, 95, 100, 105, 115, 120, 128, 140};

void bargraph::init_bargraph(int pin)
{
  this->BGPIN = pin;
  this->spin();
  this->setSegment(0);
  
}
void bargraph::turnOff()
{
  this->setSegment(0);
}

int tmpSeg;
void bargraph::displayTemp(double temp)
{
  //We need to reference the temperature on graph.
  //We know there is 20 segments on the display 
  //The upper and lower limits are 30C and 10C anthing
  //beyond these limits mean deads fishys.
  //so we have a degree per segment, easy! We must makesure our water falls in the
  //the optimum temperature in the four green segments on the display 22 to 26 

  temp-=10; //Strip off the 10 degrees we dont care about 
  tmpSeg = (unsigned int)temp;
  this->setSegment(tmpSeg);
}

void bargraph::setSegment(int seg) {
  if(seg <= 20){
    analogWrite(this->BGPIN, segment[seg]);
  }
}

void bargraph::allOn(){
  this->setSegment(20);
}

void bargraph::spin()
{
  for (int b = 0; b < 21; b++) {
    this->setSegment(b);
    delay(50);
  }
}

