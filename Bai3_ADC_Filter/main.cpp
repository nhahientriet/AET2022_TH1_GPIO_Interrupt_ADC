#include <Arduino.h>

#define ADC_PIN 34
#define LED_PIN 18

const int N = 8;

int bufferADC[N];
int indexADC = 0;

int filterADC(int value) {

  bufferADC[indexADC] = value;
  indexADC = (indexADC + 1) % N;

  long total = 0;

  for (int i = 0; i < N; i++) {
    total += bufferADC[i];
  }

  return total / N;
}

void setup() {

  Serial.begin(115200);

  pinMode(ADC_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  int rawValue = analogRead(ADC_PIN);

  int filteredValue = filterADC(rawValue);

  int pwmValue =
    map(filteredValue, 0, 4095, 0, 255);

  analogWrite(LED_PIN, pwmValue);

  Serial.print("RAW: ");
  Serial.print(rawValue);

  Serial.print(" FILTERED: ");
  Serial.println(filteredValue);

  delay(20);
}
