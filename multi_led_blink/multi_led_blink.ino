
int const LED_12 = 12;
int const LED_11 = 11;
int const LED_10 = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_12, OUTPUT);
  pinMode(LED_11, OUTPUT);
  pinMode(LED_10, OUTPUT);
  Serial.begin(96000);
}
void blinkLedSequence(int *ledArr, int size);
void blinkMiddleLed(int ledId, int amount = 2);

void loop() {
  // put your main code here, to run repeatedly:
  int ledsArr[3] = { LED_12, LED_10, LED_11 };
  blinkLedSequence(ledsArr, 3);
  blinkMiddleLed(LED_10);
}

void blinkLedSequence(int *ledsArr, int size) {
  for (int i = 0; i < size; i++) {
    digitalWrite(ledsArr[i], HIGH);
    delay(350);
    digitalWrite(ledsArr[i], LOW);
    delay(70);
  }
}

void blinkMiddleLed(int ledId, int amount) {
  digitalWrite(ledId, HIGH);
  delay(650);
  digitalWrite(ledId, LOW);
  delay(70);
  if(amount > 0) {
    blinkMiddleLed(ledId, amount - 1);
  }
  return;
}
