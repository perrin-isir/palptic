#include <EEPROM.h>

#define PINa 4
#define PINb 6
#define PINc 8
#define PINd 10
#define PINe 12

#define PERIOD_mode1 360
#define TIMEon_mode1 55
#define PAUSE_mode1 150

#define PERIOD_mode2 300
#define TIMEon_mode2 85
#define PAUSE_mode2 100

const int reference_length = 5;

static int myPins[] = {PINa, PINb, PINc, PINd, PINe};
// or, to test a single Pin:
// static int myPins[] = {PINa};

const int eepromAddress = 0; // EEPROM address to store boolean value
const int length = (sizeof(myPins) / sizeof(myPins[0]));
static int loop_count = 0;
static bool mode1 = true;
static bool change_done = false;

void setup() {
  mode1 = EEPROM.read(eepromAddress); // read saved boolean value from EEPROM
  for (int i=0; i < length; i++) {
    pinMode(myPins[i], OUTPUT);
  }
  EEPROM.write(eepromAddress, !mode1);
}

void loop() {
  int PERIOD = 0;
  int TIMEon = 0;
  int PAUSE = 0;
  if (mode1 == true) {
    PERIOD = PERIOD_mode1;
    TIMEon = TIMEon_mode1;
    PAUSE = random(PAUSE_mode1 * 1/2, PAUSE_mode1 * 3/2);
  }
  else {
    PERIOD = PERIOD_mode2;
    TIMEon = TIMEon_mode2;
    PAUSE = random(PAUSE_mode2 * 1/2, PAUSE_mode2 * 3/2); 
  }

  int true_length = length;
  if (length > reference_length) {
    true_length = reference_length;
  }

  if (loop_count * PERIOD * true_length > 4000 && !change_done) {
    change_done = true;
    EEPROM.write(eepromAddress, mode1);
  }
  loop_count++;

  for (int i=0; i < length; i++) {
    int n = random(0, length);
    // shuffling the Pins
    int temp = myPins[n];
    myPins[n] = myPins[i];
    myPins[i] = temp;
  }

  int intervals_off[true_length + 1];
  intervals_off[0] = 0;
  int tvar_off = 0;
  int tvar_step_off = PERIOD - TIMEon - PAUSE;
  int tvar_delta_off = tvar_step_off * 3 / 10;
  for (int i=0; i < true_length; i++) {
    tvar_off += tvar_step_off;
    intervals_off[i+1] = tvar_off;
  }
  for (int i=1; i < true_length; i++) {
    int delta_off = random(0, 2 * tvar_delta_off + 1);
    intervals_off[i] = intervals_off[i] - tvar_delta_off + delta_off;
  }

  int intervals_on[true_length + 1];
  intervals_on[0] = 0;
  int tvar_on = 0;
  int tvar_step_on = TIMEon;
  int tvar_delta_on = tvar_step_on * 2 / 10;
  for (int i=0; i < true_length; i++) {
    tvar_on += tvar_step_on;
    intervals_on[i+1] = tvar_on;
  }
  for (int i=1; i < true_length; i++) {
    int delta_on = random(0, 2 * tvar_delta_on + 1);
    intervals_on[i] = intervals_on[i] - tvar_delta_on + delta_on;
  }
  
  for (int i=0; i < true_length; i++) {
    digitalWrite(myPins[i], HIGH);
    delay(intervals_on[i + 1] - intervals_on[i]);
    digitalWrite(myPins[i], LOW);
    delay(intervals_off[i + 1] - intervals_off[i]);
  }
  delay(PAUSE * true_length);
}
