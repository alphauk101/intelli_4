#include "DS1307RTC.h"
tmElements_t tmp_time;

#define LIGHT_FULL 30
#define LIGHT_HALF 15
#define LIGHT_OFF  0

//our light level output to the main class sett using the time
byte light_lvls[2] {0,0};

void setup() {
  //This will be an init part of the class
  Serial.begin(9600);
  /*If we lose power we will lose our time to make setting easier will 
  shall default to 20:00:00  so it simplete power cycle at 8pm fixes the time*/
  tmp_time.Hour = 20;
  tmp_time.Minute = 0;
  tmp_time.Second = 0;

  RTC.write(tmp_time);//Set the time

}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

byte light[2];
void loop() {
  // put your main code here, to run repeatedly:
  getLightLevel(&light[0]);

  light[0] |= 0x80;
  light[1] &= 0x7F;

  Serial.write(light[0]);
  Serial.write(light[1]);
  
  
  delay(500);
}

//Gets the time from the rtc and delivers a light setting based on this time
int light_count;
byte tmp_min;
void getLightLevel(byte * buff){

  //byte 1 = white -> 2 = blue
  /*First get light level*/
  if (RTC.read(tmp_time)){
    //First check the main areas
    if((tmp_time.Hour >= 8) && (tmp_time.Hour < 20)){
      //The time is mid day ie 8am > 8pm
      //Light is full white and partial blue
      *buff = LIGHT_FULL;
      *(buff+1) = LIGHT_HALF;
    }else if ((tmp_time.Hour > 20) && (tmp_time.Hour <= 23)){
      //Its between 8pm and midnight
      *buff = LIGHT_OFF;
      *(buff+1) = LIGHT_FULL;
    }else if(tmp_time.Hour == 20){
      //its the hour of 8 so lets do the dawn
      if(tmp_time.Minute == 0){ 
        light_count = 0;
        tmp_min = 0;
      };

      if(tmp_time.Minute != tmp_min){
        if( (tmp_time.Minute & 0x01) != 0x01){
          //its even
          light_count++;
        }
        tmp_min = tmp_time.Minute;
      }
      //Slowly toggle between the 2 lights every 2 minutes
      *buff = (LIGHT_FULL - light_count);
      *(buff+1) = light_count; 
    }else{
      /*Its bassically silly oclcok so lights off.*/
        *buff = LIGHT_OFF;
        *(buff+1) = LIGHT_OFF;
    }
  }
}

