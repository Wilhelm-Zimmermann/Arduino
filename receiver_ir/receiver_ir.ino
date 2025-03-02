#include <IRremote.hpp>
#define led_pin 13

IRrecv IR(3);
bool isOn {false};

void light_led();

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  IR.enableIRIn();
}

void loop() {
  if(isOn) light_led();
  if(IR.decode()) {
    IRRawDataType decodedData = IR.decodedIRData.decodedRawData;
    Serial.println(IR.decodedIRData.decodedRawData, HEX);

    if(decodedData == 0xF20DFF00) {
      isOn = !isOn;
    }

    if(decodedData == 0xE916FF00) {
      isOn = false;
      digitalWrite(led_pin, LOW);
    }

    delay(100);
    IR.resume();
  }
}

void light_led() {
  digitalWrite(led_pin, HIGH);
  delay(50);

  digitalWrite(led_pin, LOW);
  delay(50);
}
