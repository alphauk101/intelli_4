
#define COL_ONE   A0
#define COL_TWO   A1
#define COL_THREE A2
#define COL_FOUR  A3

#define ROW_ONE   8
#define ROW_TWO   9
#define ROW_THREE 10
#define ROW_FOUR  11

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


  digitalWrite(COL_ONE, LOW);
  digitalWrite(COL_TWO, LOW);
  digitalWrite(COL_THREE, LOW);
  digitalWrite(COL_FOUR, LOW);
  digitalWrite(ROW_ONE, LOW);
  digitalWrite(ROW_TWO, LOW);
  digitalWrite(ROW_THREE, LOW);
  digitalWrite(ROW_FOUR, LOW);

}

void loop() {


  digitalWrite(COL_TWO, HIGH);
  digitalWrite(COL_ONE, HIGH);
  delayMicroseconds(750);
  digitalWrite(ROW_ONE, HIGH);
  delayMicroseconds(750);
  digitalWrite(ROW_ONE, LOW);
  digitalWrite(ROW_TWO, HIGH);
  delayMicroseconds(750);
  digitalWrite(ROW_TWO, LOW);
  digitalWrite(ROW_THREE, HIGH);
  delayMicroseconds(750);
  digitalWrite(ROW_THREE, LOW);
  digitalWrite(ROW_FOUR, HIGH);
  delayMicroseconds(750);
  digitalWrite(ROW_FOUR, LOW);
  digitalWrite(COL_ONE, LOW);
  digitalWrite(COL_TWO, LOW);


  digitalWrite(COL_FOUR, HIGH);
  digitalWrite(COL_THREE, HIGH);
  delayMicroseconds(750);;
  digitalWrite(ROW_ONE, HIGH);
  delayMicroseconds(750);;
  digitalWrite(ROW_ONE, LOW);
  digitalWrite(ROW_TWO, HIGH);
  delayMicroseconds(750);;
  digitalWrite(ROW_TWO, LOW);
  digitalWrite(ROW_THREE, HIGH);
  delayMicroseconds(750);;
  digitalWrite(ROW_THREE, LOW);
  digitalWrite(ROW_FOUR, HIGH);
  delayMicroseconds(750);;
  digitalWrite(ROW_FOUR, LOW);
  digitalWrite(COL_THREE, LOW);
  digitalWrite(COL_FOUR, LOW);

}
