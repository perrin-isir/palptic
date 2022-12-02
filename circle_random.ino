#define PINa 2
#define PINb 4
#define PINc 6
#define PINd 9
#define PINe 12
#define PERIOD 1200
#define TIMEon 300
#define PAUSE 100

void setup() {
  // put your setup code here, to run once

  pinMode(PINa, OUTPUT);
  pinMode(PINb, OUTPUT);
  pinMode(PINc, OUTPUT);
  pinMode(PINd, OUTPUT);
  pinMode(PINe, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly

  int myPins[] = {PINa, PINb, PINc, PINd, PINe};
  // or, to test a single Pin:
  // int myPins[] = {PINc};

  int length = (sizeof(myPins) / sizeof(myPins[0]));
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
    tvar = tvar + tvar_step;
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
