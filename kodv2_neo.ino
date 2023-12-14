#include <LCD16x2.h> //olimex library 
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// setupvariable för neopixel och konstruktion av neopiuxel objekt
const byte neoPin = 6;
const byte neoPixels = 24;
byte neoBright = 100;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(neoPixels, neoPin, NEO_GRB);

// variabler och konstruktion av lcd objekt
int buttons;
LCD16x2 lcd;

int red;
int green;
int blue;

int activeButton = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ring.begin();
  ring.setBrightness(neoBright);
  ring.show();
  Wire.begin();
  lcd.lcdClear();
}

void loop() {
  setActiveButton();

  switch (activeButton) {
    case 1:
      lcd.lcdClear();
      lcd.lcdWrite("RED");
      red = 255;
      green = 0;
      blue = 0;
      break;
    case 2:
      lcd.lcdClear();
      lcd.lcdWrite("BLUE");
      red = 0;
      green = 0;
      blue = 255;
      break;
    case 3:
      lcd.lcdClear();
      lcd.lcdWrite("GREEN");
      red = 0;
      green = 255;
      blue = 0;
      break;
    case 4:
      lcd.lcdClear();
      lcd.lcdWrite("YELLOW");
      red = 255;
      green = 255;
      blue = 153;
      break;
  }
  
  if(analogRead(A0) > 50){
    animation(red,blue,green);
    }
}

void setActiveButton() {
  buttons = lcd.readButtons();
  if (buttons & 0x01) {
  } else {
    activeButton = 1;
  }
  if (buttons & 0x02) {
  } else {
    activeButton = 2;
  }
  if (buttons & 0x04) {
  } else {
    activeButton = 3;
  }
  if (buttons & 0x08) {
  } else {
    activeButton = 4;
  }
}

void animation(int r, int g, int b) {
  for (int i = 0; i < neoPixels; i++) {
    ring.setPixelColor(i, ring.Color(r, g, b));
    ring.show();
    delay(20);
  }
  for (int i = 0; i < neoPixels; i++) {
    ring.setPixelColor(i, ring.Color(0, 0, 0));
    ring.show();
  }
}
