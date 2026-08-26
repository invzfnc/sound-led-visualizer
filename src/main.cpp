#include <Arduino.h>

//#define DEBUG  // comment this to disable debug

#define MAX_BARS 7
#define MIC_PIN 19

// these three are dependant
// less samples gives less sensitive and less accurate results, but less delay
// more samples gives more accurate results, but more delay
#define SAMPLE_COUNT 256 // tested sweet spot between 256 and 512
#define LOOP_DELAY 1  // milliseconds
#define READ_DELAY 50 // microseconds

#define DECAY_RATE 0.996f
#define MIN_RMS 4.0f  // adjust this to debug mode observations

const int ledPins[MAX_BARS] = {21, 47, 38, 39, 40, 41, 42};
float maxRms = 0;
int samples[SAMPLE_COUNT];

void updateLeds(int);

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < MAX_BARS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  long sum = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    int sample = analogRead(MIC_PIN);
    sum += sample;
    samples[i] = sample;

    delayMicroseconds(READ_DELAY);
  }

  // calculate dc bias
  float dcBias = (float)sum / SAMPLE_COUNT;

  float sumOfSquares = 0;
  float component;

  // calculate root mean square
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    component = (float)samples[i] - dcBias;
    sumOfSquares += component * component;
  }

  float rms = std::sqrt(sumOfSquares / SAMPLE_COUNT);

  // update max rms
  if (rms > maxRms) {
    maxRms = rms;
  }
  else {
    maxRms *= DECAY_RATE;
  }

  if (maxRms < MIN_RMS) {
    maxRms = MIN_RMS;
  }

  float normalized = constrain(rms / maxRms, 0.0, 1.0);
  int bars = (int)(normalized * MAX_BARS);
  
  #ifdef DEBUG
    Serial.print("dcBias: ");
    Serial.print(dcBias);
    Serial.print(" | component: ");
    Serial.print(component);
    Serial.print(" | rms: ");
    Serial.print(rms);
    Serial.print(" | maxRms: ");
    Serial.print(maxRms);
    Serial.print(" | bars: ");
    Serial.println(bars);
  #endif

  updateLeds(bars);
  delay(LOOP_DELAY);
}

/* turn on and turn off LEDs given number of lit bars */
void updateLeds(int bars) {
  for (int i = 0; i < MAX_BARS; i++) {
    if (i < bars) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}