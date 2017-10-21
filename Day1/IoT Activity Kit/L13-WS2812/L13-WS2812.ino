#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define NEOPIN          10
#define NUMPIXELS       2

int delayval = 500;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

void LEDShow( int red, int green, int blue) {
  pixels.setPixelColor(0, pixels.Color(green, red, blue));
  pixels.setPixelColor(1, pixels.Color(green, red, blue));
  pixels.show();
  delay(delayval);
}

void setup() {
  pixels.begin();                             //WS2812 Init
  LEDShow(0, 0, 0);
  delay(500);
  LEDShow(255, 0, 0);
  delay(500);
  LEDShow(0, 255, 0);
  delay(500);
  LEDShow(0, 0, 255);
  delay(500);
  LEDShow(0, 0, 0);
}

void loop() {
}
