#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2
#define DEBOUNCE_MS 50

volatile uint32_t countPress = 0;
volatile unsigned long lastInterruptTime = 0;

void IRAM_ATTR handleInterrupt() {

  unsigned long now = millis();

  if (now - lastInterruptTime >= DEBOUNCE_MS) {
    countPress++;
    lastInterruptTime = now;
  }
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

  static uint32_t oldCount = 0;

  if (countPress != oldCount) {

    oldCount = countPress;

    Serial.print("Count = ");
    Serial.println(countPress);

    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}
