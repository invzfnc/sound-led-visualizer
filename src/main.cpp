#include <Arduino.h>

#define MAX_BARS 7
#define PWM_FREQ 5000
#define PWM_RES 8

const int ledPins[MAX_BARS] = {21, 47, 38, 39, 40, 41, 42};

void setup() {
  Serial.begin(115200);
  Serial.println("boot ok");

  for (int i = 0; i < MAX_BARS; i++) {
    ledcSetup(i, PWM_FREQ, PWM_RES);
    ledcAttachPin(ledPins[i], i);
  }
}

void loop() {
  for (int b = 0; b <= 255; b++) {
    for (int i = 0; i < MAX_BARS; i++)
      ledcWrite(i, b);
    delay(4);
  }
  for (int b = 255; b >= 0; b--) {
    for (int i = 0; i < MAX_BARS; i++) 
      ledcWrite(i, b);
    delay(4);
  }

  delay(500);
}