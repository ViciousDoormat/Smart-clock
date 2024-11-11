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
const long interval = 30000;
bool displayActive = true;

struct DisplayItem {
  String text;
  int size;

  DisplayItem(String text, int size = 2) { 
    this->text = text;
    this->size = size;
  }
};

void displayContent(std::initializer_list<DisplayItem> items) {
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (const DisplayItem& item : items) {
    display.setTextSize(item.size);
    display.println(item.text);
  }
}

void toggleDisplay() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    displayActive = !displayActive;
  }
}

#endif