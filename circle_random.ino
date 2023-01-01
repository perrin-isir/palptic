#include <EEPROM.h>

#define PINa 2
#define PINb 4
#define PINc 6
#define PINd 9
#define PINe 12
#define PERIOD_mode1 1800
#define TIMEon_mode1 350
#define PAUSE_mode1 100
#define PERIOD_mode2 1000
#define TIMEon_mode2 500
#define PAUSE_mode2 200

const int eepromAddress = 0; // EEPROM address to store boolean value
static int myPins[] = {PINa, PINb, PINc, PINd, PINe};
// or, to test a single Pin:
// static int myPins[] = {PINe};
const int length = (sizeof(myPins) / sizeof(myPins[0]));
static int loop_count = 0;
static bool mode1 = true;
static bool change_done = false;

void setup() {
  // put your setup code here, to run once

  mode1 = EEPROM.read(eepromAddress); // read saved boolean value from EEPROM
  for (int i=0; i < length; i++) {
    pinMode(myPins[i], OUTPUT);
  }
  EEPROM.write(eepromAddress, !mode1);
}

void loop() {
  // put your main code here, to run repeatedly

  int PERIOD = 0;
  int TIMEon = 0;
  int PAUSE = 0;
  if (mode1 == true) {
    PERIOD = PERIOD_mode1;
    TIMEon = TIMEon_mode1;
    PAUSE = PAUSE_mode1;
  }
  else {
    PERIOD = PERIOD_mode2;
    TIMEon = TIMEon_mode2;
    PAUSE = PAUSE_mode2;    
  }

  if (loop_count * PERIOD > 4000 && !change_done) {
    change_done = true;
    EEPROM.write(eepromAddress, mode1);
  }
  loop_count++;

  int intervals[length + 1];
  intervals[0] = 0;
  int tvar = 0;
  int tvar_step = (PERIOD - TIMEon - PAUSE) / length;
  int tvar_delta = tvar_step * 4 / 10;
  for (int i=0; i < length; i++) {
    int n = random(0, length);
    // shuffling the Pins
    int temp = myPins[n];
    myPins[n] = myPins[i];
    myPins[i] = temp;
    tvar += tvar_step;
    intervals[i+1] = tvar;
  }
  for (int i=1; i < length; i++) {
    int delta = random(0, 2 * tvar_delta + 1);
    intervals[i] = intervals[i] - tvar_delta + delta;
  }
  for (int i=0; i < length; i++) {
    digitalWrite(myPins[i], HIGH);
    delay(TIMEon / length);
    digitalWrite(myPins[i], LOW);
    delay(intervals[i + 1] - intervals[i]);
  }
  delay(PAUSE);
}
