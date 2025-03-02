#define led_pin 0

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_pin, HIGH);
  delay(50);

  digitalWrite(led_pin, LOW);
  delay(50);
}
