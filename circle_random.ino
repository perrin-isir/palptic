#define PINa 2
#define PINb 4
#define PINc 6
#define PINd 9
#define PINe 12
#define PERIOD 1000
#define TIMEon 300
#define PAUSE 50

void setup() {
  // put your setup code here, to run once:
  pinMode(PINa, OUTPUT);
  pinMode(PINb, OUTPUT);
  pinMode(PINc, OUTPUT);
  pinMode(PINd, OUTPUT);
  pinMode(PINe, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int myPins[] = {PINa, PINb, PINc, PINd, PINe};
  // to test a single Pin:
  // int myPins[] = {PINe};
  int length = (sizeof(myPins) / sizeof(myPins[0]));
  // shuffling the Pins
  for (int i=0; i < length; i++) {
    int n = random(0, length);
    int temp = myPins[n];
    myPins[n] = myPins[i];
    myPins[i] = temp;
  }
  for (int i=0; i < length; i++) {
    digitalWrite(myPins[i], HIGH);
    delay(TIMEon / 5);
    digitalWrite(myPins[i], LOW);
    delay((PERIOD - TIMEon - PAUSE) / 5);
  }
  delay(PAUSE);
}
