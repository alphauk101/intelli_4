/*****************************************
   Timer class allows use of 1-3 timers can use a
   callback but timer must be nudged in order for
   this is function properly.
   Author L. Williams
 *********************************************/

#include "timer.h"


//These identify which timer is being manipulated

volatile unsigned long TIMER_ONE_PERIOD = 0;//Our time in Ms before overrun
volatile unsigned long TIMER_TWO_PERIOD = 0;//Our time in Ms before overrun
volatile unsigned long TIMER_THREE_PERIOD = 0;//Our time in Ms before overrun

volatile unsigned long TIMER_ONE_LASTKNOWN_TIME = 0;//Our time in Ms at the point of starting the timer
volatile unsigned long TIMER_TWO_LASTKNOWN_TIME = 0;//Our time in Ms at the point of starting the timer
volatile unsigned long TIMER_THREE_LASTKNOWN_TIME = 0;//Our time in Ms at the point of starting the timer

//Current staus of each timer
boolean TIMER_ONE_RUNNING = false;
boolean TIMER_TWO_RUNNING = false;
boolean TIMER_THREE_RUNNING = false;

//The callbacks for each timer
static void (*callBackTimer)(int);


/*Allows the initialisation with the given timeout in mills*/
void Timer::init(int whichTimer, unsigned long timeInMillis)
{
  TIMER_ONE_TRIGGERED = false;
  
  switch (whichTimer)
  {
    case TIMER_1:
      TIMER_ONE_PERIOD = timeInMillis;
      TIMER_ONE_RUNNING = false;
      break;
    case TIMER_2:
      TIMER_TWO_PERIOD = timeInMillis;
      TIMER_TWO_RUNNING = false;
      break;
    case TIMER_3:
      TIMER_THREE_PERIOD = timeInMillis;
      TIMER_THREE_RUNNING = false;
      break;
    default:
      /*Do Nothing*/
      break;
  }


}


/*Allows us to start the timers*/
void Timer::startTimer(int whichTimer)
{
  switch (whichTimer)
  {
    case TIMER_1:

      TIMER_ONE_LASTKNOWN_TIME = millis();
      TIMER_ONE_RUNNING = true;
      //We have started our timer.
      break;
    case TIMER_2:
      TIMER_TWO_LASTKNOWN_TIME = millis();
      TIMER_TWO_RUNNING = true;
      break;
    case TIMER_3:
      TIMER_THREE_LASTKNOWN_TIME = millis();
      TIMER_THREE_RUNNING = true;
      break;
    default:
      /*Do Nothing*/
      break;
  }


}

/*Allows us to know that the timer has been stopped by the parent class*/
void Timer::stopTimer(int whichTimer)
{
  switch (whichTimer)
  {
    case TIMER_1:
      TIMER_ONE_RUNNING = false;
      //We have started our timer.
      break;
    case TIMER_2:
      TIMER_TWO_RUNNING = false;
      break;
    case TIMER_3:
      TIMER_THREE_RUNNING = false;
      break;
    default:
      /*Do Nothing*/
      break;
  }
}

boolean Timer::isTimerRunning(int whichTimer)
{
  switch (whichTimer)
  {
    case TIMER_1:
      return TIMER_ONE_RUNNING;
      //We have started our timer.
      break;
    case TIMER_2:
      return TIMER_TWO_RUNNING;
      break;
    case TIMER_3:
      return TIMER_THREE_RUNNING;
      break;
    default:
      /*Do Nothing*/
      break;
  }
}

/*This is important so that we can check this timer regularly*/
volatile unsigned long sampleTime;
void Timer::nudge()
{
  sampleTime = millis();

  if (TIMER_ONE_RUNNING) { //Its only worth doing this if the timer is running
    if ((sampleTime - TIMER_ONE_LASTKNOWN_TIME) > TIMER_ONE_PERIOD)
    {
      //Timer has elasped
      stopTimer(TIMER_1);  
      //if (callBackTimer != NULL)
      //{
        TIMER_ONE_TRIGGERED = true;
        //callBackTimer(TIMER_1);
      //}
    }
  }

  if (TIMER_TWO_RUNNING) { //Its only worth doing this if the timer is running
    if ((sampleTime - TIMER_TWO_LASTKNOWN_TIME) > TIMER_TWO_PERIOD)
    {
      //Timer has elasped
      stopTimer(TIMER_2);
      if (callBackTimer != NULL)
      {
        callBackTimer(TIMER_2);
      }
    }
  }

  if (TIMER_THREE_RUNNING) { //Its only worth doing this if the timer is running
    if ((sampleTime - TIMER_THREE_LASTKNOWN_TIME) > TIMER_THREE_PERIOD)
    {
      //Timer has elasped
      stopTimer(TIMER_3);
      if (callBackTimer != NULL)
      {
        callBackTimer(TIMER_3);
      }
    }
  }


}

void Timer::resetAllTimers()
{
  stopTimer(TIMER_1);
  stopTimer(TIMER_2);
  stopTimer(TIMER_3);
}


//ISR//
/*This registers our callback function for the main code.*/
/*When fired returns which timer was fired*/
void Timer::setCallBack(void (*cb)(int))
{
  callBackTimer = cb;
}











