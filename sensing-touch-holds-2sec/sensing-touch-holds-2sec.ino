//Each touch holds for 2 seconds
//Each touch can reset the 2 second counter
//While finger is on, light won't turn off.

#include <Adafruit_NeoPixel.h>

#define LED_PIN 20
#define TOUCHREAD_PIN 23
#define TOUCHREAD_THRESHOLD 1000

int data; 
bool ledOn = false;
unsigned long touchTime;
int timeOnThreshold = 2000;// 1 * 60 * 1000;

Adafruit_NeoPixel strip(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(57600); 
  strip.begin();           
  strip.show();           
  strip.setBrightness(50);
}

void loop() {
  data = touchRead(TOUCHREAD_PIN);
  //Serial.println(data);

  if(data >= TOUCHREAD_THRESHOLD && !ledOn) {
    touchTime = millis();
    ledOn = true;
    fadeIn();
  }else if(data >= TOUCHREAD_THRESHOLD && ledOn) {
    touchTime = millis();
  } else if (abs(millis() - touchTime) > timeOnThreshold && ledOn) {
    ledOn = false;
    fadeOut();
  }
  delay(100); 
}

void fadeIn() {
  Serial.println("Fade In");
  for(int i=1; i<256; i++) {
    strip.setPixelColor(0, strip.Color(i, i, i));
    strip.show();    
    delay(10);
  }
}

void fadeOut() {
  Serial.println("Fade Out");
  for(int i=255; i>1; i--) {
    strip.setPixelColor(0, strip.Color(i, i, i));
    strip.show();    
    delay(10);
  }
}
