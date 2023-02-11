#include <Adafruit_NeoPixel.h>

#define LED_PIN 20
#define TOUCHREAD_PIN 23
#define TOUCHREAD_THRESHOLD 1000

int data; 
bool ledOn = false;

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
  int count = 0;

  // IF A TOUCH IS FELT...INCREASE COUNT BY 1
    if(data >= TOUCHREAD_THRESHOLD && !ledOn) {
        count ++;
        outputs(count);
    }

  delay(100); 
}

void fadeInRed() {
  Serial.println("Fade In Red");
  for(int i=1; i<256; i++) {
    strip.setPixelColor(0, strip.Color(i, 0, 0));
    strip.show();    
    delay(10);
  }
}

void outputs(int count){
    if(count >= 5){
    // AMBER LIGHT ON (+ sound?)
      fadeInYellow();
  }
  else if(count >=10){
    // RED LIGHT ON (+ sound?)
      fadeInRed();
  }
  else{
    // LIGHTS OFF - NO SOUNDS
      strip.show();  
  }
}

void fadeInYellow() {
  Serial.println("Fade In Yellow");
  for(int i=1; i<256; i++) {
    strip.setPixelColor(0, strip.Color(0, i, 0));
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
