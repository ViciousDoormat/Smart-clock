#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED DISPLAY config 
#define SCREEN_WIDTH 128 // in pixels
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long previousMillis = millis();

struct DisplayItem {
  String text;
  int size;

  DisplayItem(String text, int size = 2) { 
    this->text = text;
    this->size = size;
  }
};

enum Screen {
  Time,
  Weather,
  Fact
};
const int numDisplays = 3;
Screen currentDisplay = Time;
int displayDurations[numDisplays] = {30000, 15000, 20000};

void displayContent(std::initializer_list<DisplayItem> items) {
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (const DisplayItem& item : items) {
    display.setTextSize(item.size);
    display.println(item.text);
  }
}

bool toggleDisplay() {
  if (millis() - previousMillis >= displayDurations[currentDisplay]) {
    previousMillis = millis();
    currentDisplay = static_cast<Screen>((currentDisplay + 1) % numDisplays);
    return true;
  }
  return false;
}

#endif