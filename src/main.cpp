#include <Arduino.h>
#include "pinHeaders.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_ONBOARD_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_ONBOARD_LED, HIGH);
  delay(1000);
  digitalWrite(PIN_ONBOARD_LED, LOW);
  delay(1000);
}