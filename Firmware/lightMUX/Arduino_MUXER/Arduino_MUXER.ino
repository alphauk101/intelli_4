
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

  pinMode(COL_ONE, OUTPUT);
  pinMode(COL_TWO, OUTPUT);
  pinMode(COL_THREE, OUTPUT);
  pinMode(COL_FOUR, OUTPUT);

  pinMode(ROW_ONE, OUTPUT);
  pinMode(ROW_TWO, OUTPUT);
  pinMode(ROW_THREE, OUTPUT);
  pinMode(ROW_FOUR, OUTPUT);

  pinMode(LINEZERO, INPUT);
  pinMode(LINEONE, INPUT);

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

void loop() {


  mode = (digitalRead(LINEONE) == HIGH) ? 1 : 0;
  mode |= ( ((digitalRead(LINEZERO) == HIGH) ? 1 : 0) << 1);

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

if (WhiteTime > 0) {
  digitalWrite(COL_ONE, HIGH);
    digitalWrite(COL_THREE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_ONE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_ONE, LOW);
    digitalWrite(ROW_TWO, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_TWO, LOW);
    digitalWrite(ROW_THREE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_THREE, LOW);
    digitalWrite(ROW_FOUR, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_FOUR, LOW);
    digitalWrite(COL_ONE, LOW);
    digitalWrite(COL_THREE, LOW);


    digitalWrite(COL_TWO, HIGH);
    digitalWrite(COL_THREE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_ONE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_ONE, LOW);
    digitalWrite(ROW_TWO, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_TWO, LOW);
    digitalWrite(ROW_THREE, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_THREE, LOW);
    digitalWrite(ROW_FOUR, HIGH);
    delayMicroseconds(WhiteTime);
    digitalWrite(ROW_FOUR, LOW);
    digitalWrite(COL_TWO, LOW);
    digitalWrite(COL_THREE, LOW);
  }

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

  delayMicroseconds(cycle);
}
