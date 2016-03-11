#include "ds.h"
#include "bargraph.h"

ds mDSTemp;
bargraph mBarGraph;

#define LED_RED   A0
#define LED_BLUE  A2

#define PIR_PIN   2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Started");

  mBarGraph.init_bargraph(9);

  pinMode(LED_RED,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  
  pinMode(PIR_PIN,INPUT);
  setBlueLED(false);
  
}

void loop() {

  setRedLED(true);
  double tmp = mDSTemp.getTemp();
  mBarGraph.displayTemp(tmp);
  Serial.println(tmp);
  setRedLED(false);
  delay(1000);

  if(digitalRead(PIR_PIN)){
      setBlueLED(true);
      delay(250);
      setBlueLED(false);
  }
}

void setRedLED(bool sts)
{
  if(sts){
    digitalWrite(LED_RED,LOW);
  }else{
    digitalWrite(LED_RED,HIGH);
  }
}

void setBlueLED(bool sts)
{
  if(sts){
    digitalWrite(LED_BLUE,LOW);
  }else{
    digitalWrite(LED_BLUE,HIGH);
  }
}

