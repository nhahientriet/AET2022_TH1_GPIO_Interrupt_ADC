
#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

volatile bool buttonPressed = false;

void IRAM_ATTR handleInterrupt() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(
    digitalPinToInterrupt(BUTTON_PIN),
    handleInterrupt,
    FALLING
  );
}

void loop() {

  if (buttonPressed) {
    buttonPressed = false;

    Serial.println("Button Pressed");

    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
}
