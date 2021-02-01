#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Blink!");
  sleep(500);
  digitalWrite(LED_BUILTIN, HIGH);
  sleep(500);
  digitalWrite(LED_BUILTIN, LOW);
}