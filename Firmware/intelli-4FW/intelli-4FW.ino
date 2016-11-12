#include "timer.h"
#include "ds.h"
#include "bargraph.h"



ds mDSTemp;
bargraph mBarGraph;
Timer timer;//Our timer class

volatile bool TIMER_TRIGGERED = false;
unsigned long timeout = 0;
volatile int state_one, state_zero;
volatile bool prev_realy_state, relay_state, red, blue;

#define LED_RED   A0
#define LED_BLUE  A2
#define PIR_PIN   2
#define PIN_RELAY 6

#define DAY_MODE    0
#define NIGHT_MODE  1
#define LOW_MODE    2
#define OFF         3

/*
  unsigned long DAYMODE_LENGTH =   1800000;
  unsigned long DAWNMODE_LENGTH =  36000000;
  unsigned long NIGHTMODE_LENGTH = 36000000;
*/


unsigned long DAYMODE_LENGTH =   1800000;
unsigned long DAWNMODE_LENGTH =  3600000;
unsigned long NIGHTMODE_LENGTH = 1800000;

#define TIMER_1 1
#define TIMER_2 2
#define TIMER_3 3

volatile byte MODE = 0;
bool PIR_REC = false;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //Serial.println("Started");

  mBarGraph.init_bargraph(9);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  //Setup pin outs for lighting MCU
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
  prev_realy_state = false;

  //pinMode(PIR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), pir_int, RISING);

  
  setBlueLED(false);

  setLightingMode();
  //We dont init our timers until we need them but we should set our call back
  timer.setCallBack(TimerISR);

  MODE = DAY_MODE;//Preset our mode
  setLightingMode();

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop() {

  if (MODE != OFF) {
    //if (1) {
    double tmp = mDSTemp.getTemp();
    mBarGraph.displayTemp(tmp);
    //Serial.println(tmp);
  } else {
    mBarGraph.turnOff();
  }

  //if (digitalRead(PIR_PIN)) {
  if(PIR_REC){
    mBarGraph.allOn();
    delay(150);
    mBarGraph.turnOff();
    MODE = DAY_MODE;
    setLightingMode();
    PIR_REC = false;
  }
  delay(10);//Slow the 16Mhz of raging power a tad.
  timer.nudge();//This is important to ensure out timer keeps turning


  if (timer.TIMER_ONE_TRIGGERED) {
    setLightingMode();
    timer.TIMER_ONE_TRIGGERED = false;
  }
}

inline void setRedLED(bool sts)
{
  if (sts) {
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_RED, HIGH);
  }
}

inline void setBlueLED(bool sts)
{
  if (sts) {
    digitalWrite(LED_BLUE, LOW);
  } else {
    digitalWrite(LED_BLUE, HIGH);
  }
}


void setLightingMode()
{
  state_one = 0;
  state_zero = 0;
  relay_state = false;
  red = false;
  blue = false;
  switch (MODE)
  {
    case DAY_MODE:
      red = true;
      blue = true;
      relay_state = true;
      state_one = LOW;
      state_zero = HIGH;
      timeout = DAYMODE_LENGTH;
      MODE = NIGHT_MODE;//Set up the next mode
      break;
    case NIGHT_MODE:
      red = true;
      blue = false;
      relay_state = true;
      state_zero = LOW;
      state_one = HIGH;
      timeout = DAWNMODE_LENGTH;
      MODE = LOW_MODE;
      break;
    case LOW_MODE:
      red = false;
      blue = true;
      relay_state = false;
      state_zero = HIGH;
      state_one = HIGH;
      timeout = DAWNMODE_LENGTH;
      MODE = OFF;
      break;
    case OFF:
      red = false;
      blue = false;
      relay_state = false;
      state_zero = LOW;
      state_one = LOW;
      timeout = NIGHTMODE_LENGTH;
      MODE = OFF;
      break;
  }
  
  if(relay_state != prev_realy_state){
    //Because when the relay fires it causes an interrupt we need to make sure we dont acknowledge it    
    digitalWrite(PIN_RELAY, relay_state);
    prev_realy_state = relay_state;
    delay(200);
    TIMER_TRIGGERED = false;
  }
  digitalWrite(0, state_zero);
  digitalWrite(1, state_one);
  setRedLED(red);
  setBlueLED(blue);

  //  timer.resetAllTimers();
  //  timer.init(TIMER_1, timeout);//This tells us to chenge what were displaying
  timer.init(TIMER_1, timeout);
  timer.startTimer(TIMER_1);
}

bool last_state;
inline void switchRelay(bool state) {
  if (state != last_state) {
    if (state) {
      digitalWrite(PIN_RELAY, HIGH);
    } else {
      digitalWrite(PIN_RELAY, LOW);
    }
    last_state = state;
  }
}

static void pir_int()
{
  PIR_REC = true;
}

//Timer callback returns which timer was fired
static void TimerISR(int timer)
{
  TIMER_TRIGGERED = true;
}

