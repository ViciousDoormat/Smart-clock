#include <ESP8266WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include "config.h"
#include "display.h"
#include "time.h"
#include "weather.h"
#include "fact.h"

//Arduino Cloud
WiFiConnectionHandler ArduinoIoTPreferredConnection(ssid, password);
CloudSwitch power;
void onPowerChange();



void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);

  // START THE OLED DISPLAY //
  Wire.begin(D3, D5);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //TODO do not proceed, loop forever
  }

  display.clearDisplay();
  displayContent({ DisplayItem("Klabonga v2", 1) });
  display.display();

  setup_wifi();

  setupCloud();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  timeClient.begin();

  randomSeed(analogRead(D2));

}

void loop() {
  delay(500);
  ArduinoCloud.update();

  if(power){
    if(toggleDisplay()) {
      display.clearDisplay();
      switch(currentDisplay) {
        case Time:
          timeClient.update();
          printTime();
        break;

        case Weather:
          if(newHour()) {
            fetchWeatherData();
          }
          printWeather();
        break;

        case Fact:
          printFact();
        break;
      }
      display.display();
    }
  }
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupCloud(){
  ArduinoCloud.setBoardId(id);
  ArduinoCloud.setSecretDeviceKey(key);
  ArduinoCloud.addProperty(power, READWRITE, ON_CHANGE, onPowerChange);
}

void onPowerChange() {}