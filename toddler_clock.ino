#include <application.h>

#include "neopixel.h"

// nrf2401 code from https://github.com/technobly/SparkCore-RF24
#include "nRF24L01.h"
#include "RF24.h"

double temperature = 0;
char color[7] = "yellow";

#define PIXEL_COUNT 1
#define PIXEL_PIN D0
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  Spark.variable("color", color, STRING);
  Spark.variable("temperature", &temperature, DOUBLE);
  Spark.function("wakeUp", wakeUp);
  Spark.function("sleep", sleep);

  pinMode(A0, INPUT);
  sleep("");

  RGB.control(true);
  RGB.brightness(64);

  strip.begin();
  strip.setBrightness(128);
  strip.show();
}

void loop() {
  temperature = getTemperature();
}

void logToCloud(float temperature) {
    // http://www.netburner.com/learn/how-to-communicate-with-sparkfun-free-cloud-data-service
    // https://data.sparkfun.com/input/4Jr85ZmDV2slK916xXq3?private_key=b5KaYwjWo6tP1j4npo29&temp=10.09
}

int wakeUp(String args) {
  strip.setPixelColor(0, 0, 255, 0);
  strncpy(color, "green", 7);
  strip.show();
  return 0;
}

int sleep(String args) {
  strip.setPixelColor(0, 222, 170, 0);
  strncpy(color, "yellow", 7);
  strip.show();
  return 0;
}

double getTemperature() {
  float tempReading = analogRead(A0);
  float voltage = tempReading * 3.3;
  voltage /= 4095;

  double temperatureC = (voltage - 0.5) * 100;
  double temperatureF = temperatureC * 1.8 + 32;
  return temperatureF;
}
