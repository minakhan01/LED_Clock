#include <FastLED.h>
#define NUM_LEDS 32
#define DATA_PIN 6
#define CLOCK_PIN 7

// Brightest the LEDs should pulse
int MAX_BRIGHTNESS = 150;
// Dimmest LEDs should pulse
int MIN_BRIGHTNESS = 25;
// Length of a pulse
int PULSE_TIME = 2000;
// How many levels to go through, smoothness
int GRANULARITY = 1;

// How many levels between MIN and MAX brightness
int stages = (MAX_BRIGHTNESS - MIN_BRIGHTNESS)/GRANULARITY;
// The delay between each change so that the total pulse is PULSE_TIME
int del = PULSE_TIME/stages;

// LEDs representing 9-10, noon, 3-4, and 5 on the clock
int blinkLEDs[] = {0, 9, 10, 11, 12, 15, 27, 28, 29, 30};

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);

  // Light up all the LEDs to start
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  for (int i = 0; i < (sizeof(blinkLEDs)/sizeof(int)) - 1; i++) {
    leds[blinkLEDs[i]] += CRGB(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);
  }
  FastLED.show();
}

// Tells us how far into our pulse we are
int count = 0;

void loop() { 
  for (int i = 0; i < (sizeof(blinkLEDs)/sizeof(int)) - 1; i++) {
    if (count < stages) {
      leds[blinkLEDs[i]] -= CRGB(GRANULARITY, GRANULARITY, GRANULARITY);
    } else {
      leds[blinkLEDs[i]] += CRGB(GRANULARITY, GRANULARITY, GRANULARITY);
    }
  }
  count++;
  if (count == stages*2) {
    count = 0;
  }
  FastLED.show();
  delay(del);
}
