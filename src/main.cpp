#include <Arduino.h>

#define MAX_BARS 7
#define MIC_PIN 19
#define SAMPLE_WINDOW 50
#define DELAY 50

const int ledPins[MAX_BARS] = {21, 47, 38, 39, 40, 41, 42};
unsigned long startMillis;

int calculateBars();
void updateLeds(int);

void setup() {
  Serial.begin(115200);
  Serial.println("boot ok");

  for (int i = 0; i < MAX_BARS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int bars = calculateBars();
  Serial.print("bars: ");
  Serial.println(bars);
  updateLeds(bars);
  delay(DELAY);
}

/* translates volume detected to bar/level */
int calculateBars() {
  unsigned int signalMin = 1024;
  unsigned int signalMax = 0;
  unsigned int signal;

  startMillis = millis();

  while (millis() - startMillis < SAMPLE_WINDOW) {
    signal = analogRead(MIC_PIN);
    if (signal > signalMax)
      signalMax = signal;
    if (signal < signalMin) 
      signalMin = signal;
  }

  // debug
  Serial.print("signalMin: ");
  Serial.print(signalMin);
  Serial.print(" | signalMax: ");
  Serial.print(signalMax);
  Serial.print(" | signal: ");
  Serial.println(signal);

  return map(signal, signalMin, signalMax, 0, MAX_BARS);
}

/* turn on and turn off LEDs given number of lit bars */
void updateLeds(int bars) {
  for (int i = 0; i < MAX_BARS; i++) {
    if (i <= bars) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}