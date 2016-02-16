#include "ds.h"
#include "bargraph.h"

ds mDSTemp;
bargraph mBarGraph;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");

  mBarGraph.init_bargraph(9);
  
}

void loop() {

  double tmp = mDSTemp.getTemp();
  mBarGraph.displayTemp(tmp);
  Serial.println(tmp);
  delay(1000);
}
