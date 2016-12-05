
#define COL_ONE   A0
#define COL_TWO   A1
#define COL_THREE A2
#define COL_FOUR  A3

#define ROW_ONE   8
#define ROW_TWO   9
#define ROW_THREE 10
#define ROW_FOUR  11

#define LINEZERO  0
#define LINEONE   1

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(COL_ONE, OUTPUT);
  pinMode(COL_TWO, OUTPUT);
  pinMode(COL_THREE, OUTPUT);
  pinMode(COL_FOUR, OUTPUT);

  pinMode(ROW_ONE, OUTPUT);
  pinMode(ROW_TWO, OUTPUT);
  pinMode(ROW_THREE, OUTPUT);
  pinMode(ROW_FOUR, OUTPUT);
  /*
    pinMode(LINEZERO, INPUT);
    pinMode(LINEONE, INPUT);
  */
  digitalWrite(COL_ONE, LOW);
  digitalWrite(COL_TWO, LOW);
  digitalWrite(COL_THREE, LOW);
  digitalWrite(COL_FOUR, LOW);
  digitalWrite(ROW_ONE, LOW);
  digitalWrite(ROW_TWO, LOW);
  digitalWrite(ROW_THREE, LOW);
  digitalWrite(ROW_FOUR, LOW);


}

#define FULL  750
#define MIN   1
#define OFF   0
unsigned int BlueTime = FULL;
unsigned int WhiteTime = MIN;
unsigned int cycle = 500;

byte mode = 0;

volatile byte inbyte = 0;
void get_serial_data()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    inbyte = Serial.read();
    //First see if its valid and which light
    if ((inbyte & 0x80) == 0x80) { //if the MSB is set then this is a white value
      inbyte &= 0x7F;
      //White
      if (inbyte > 30) inbyte = 30;
      if (inbyte == 0) WhiteTime = 0;
      WhiteTime = map(inbyte, 0, 30, 0, 800);
    } else {
      //blue.
      if (inbyte > 30) inbyte = 30;
      if (inbyte == 0) BlueTime = 0;

      BlueTime = map(inbyte, 0, 30, 0, 800);
    }
  }
}

inline void switchRow(byte r, bool state)
{
  switch (r)
  {
    case 0:
      digitalWrite(ROW_ONE, state);
      break;
    case 1:
      digitalWrite(ROW_TWO, state);
      break;
    case 2:
      digitalWrite(ROW_THREE, state);
      break;
    case 3:
      digitalWrite(ROW_FOUR, state);
      break;
    default:
      break;
  }
}


void loop() {

  /*
    mode = (digitalRead(LINEONE) == HIGH) ? 1 : 0;
    mode |= ( ((digitalRead(LINEZERO) == HIGH) ? 1 : 0) << 1);
    mode = 1;
    switch (mode)
    {
    case 0:
      BlueTime = OFF;
      WhiteTime = OFF;
      break;
      case 1:
      BlueTime = FULL;
      WhiteTime = FULL;
      break;
      case 2:
      BlueTime = FULL;
      WhiteTime = MIN;
      break;
      case 3:
      BlueTime = MIN;
      WhiteTime = MIN;
      break;
    }
  */


  get_serial_data();

  //WhiteTime = 10;

  for (int a = 0; a < 4; a++) {
    /*For each column we do this*/

    switch (a)
    {
      case 0:
        if (WhiteTime > 0) {
          /*Two rows at a time*/
          digitalWrite(COL_ONE, HIGH);

          switchRow(0, true);
          delayMicroseconds(WhiteTime);
          switchRow(0, false);

          switchRow(1, true);
          delayMicroseconds(WhiteTime);
          switchRow(1, false);

          switchRow(2, true);
          delayMicroseconds(WhiteTime);
          switchRow(2, false);

          switchRow(3, true);
          delayMicroseconds(WhiteTime);
          switchRow(3, false);

          digitalWrite(COL_ONE, LOW);
        }
        break;
      case 1:
        if (WhiteTime > 0) {
          /*Two rows at a time*/
          digitalWrite(COL_TWO, HIGH);

          switchRow(0, true);
          delayMicroseconds(WhiteTime);
          switchRow(0, false);

          switchRow(1, true);
          delayMicroseconds(WhiteTime);
          switchRow(1, false);

          switchRow(2, true);
          delayMicroseconds(WhiteTime);
          switchRow(2, false);

          switchRow(3, true);
          delayMicroseconds(WhiteTime);
          switchRow(3, false);

          digitalWrite(COL_TWO, LOW);

        }
        break;
      case 2:
        if (WhiteTime > 0) {
          digitalWrite(COL_THREE, HIGH);
          switchRow(0, true);
          delayMicroseconds(WhiteTime);
          switchRow(0, false);

          switchRow(1, true);
          delayMicroseconds(WhiteTime);
          switchRow(1, false);

          switchRow(2, true);
          delayMicroseconds(WhiteTime);
          switchRow(2, false);

          switchRow(3, true);
          delayMicroseconds(WhiteTime);
          switchRow(3, false);

          digitalWrite(COL_THREE, LOW);
        }
        break;
      case 3:

        if (BlueTime > 0) {
          digitalWrite(COL_FOUR, HIGH);

          switchRow(0, true);
          delayMicroseconds(BlueTime);
          switchRow(0, false);

          switchRow(1, true);
          delayMicroseconds(BlueTime);
          switchRow(1, false);

          switchRow(2, true);
          delayMicroseconds(BlueTime);
          switchRow(2, false);

          switchRow(3, true);
          delayMicroseconds(BlueTime);
          switchRow(3, false);

          digitalWrite(COL_FOUR, LOW);
        }
        break;
      default:
        break;
    }


    delayMicroseconds(cycle);
  }
  /*
    if (BlueTime > 0) {
      //Switch Blue
      //In the blues we shall switch 2 rows instead of 2 columns
      digitalWrite(COL_FOUR, HIGH);
      digitalWrite(ROW_ONE, HIGH);
      digitalWrite(ROW_TWO, HIGH);
      delayMicroseconds(BlueTime);
      digitalWrite(ROW_ONE, LOW);
      digitalWrite(ROW_TWO, LOW);
      digitalWrite(ROW_THREE, HIGH);
      digitalWrite(ROW_FOUR, HIGH);
      delayMicroseconds(BlueTime);
      digitalWrite(ROW_THREE, LOW);
      digitalWrite(ROW_FOUR, LOW);
      digitalWrite(COL_FOUR, LOW);
    }
  */
}
