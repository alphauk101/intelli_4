#include "ds.h"


OneWire Comms(7);//pn 6 is our ds temperature sensor.


double ds::getTemp()
{
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  //get address
  if ( !Comms.search(addr)) {
    Comms.reset_search();
  }
  Comms.reset();
  Comms.select(addr);
  Comms.write(0x44,1); //begin temp reading

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = Comms.reset();
  Comms.select(addr);    
  Comms.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = Comms.read();
  }

  //we have our two bytes of temoerature readings
  byte LSB = data[0];
  byte MSB = data[1];
  /*
  int tempInt = ((MSB << 8) | LSB);
   tempInt = (6 * tempInt) + tempInt / 4;
   
   int frac = tempInt % 100;
   tempInt = tempInt / 100;
   
   String tempStr = String(tempInt);
   String fracStr = String(frac);
   tempStr = "Water: " + tempStr + "." + fracStr + degreeSymbol+"C";
   screen.screenManager(tempStr, "No Alerts");
   */
  int tempInt = ((MSB << 8) | LSB);
  float tempD = ((6 * tempInt) + tempInt / 4);
  tempD = tempD / 100;
  //Serial.println(tempInt);
  return tempD;
}
