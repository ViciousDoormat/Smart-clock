#ifndef WEATHER_H
#define WEATHER_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

//weather
const String link = "http://api.weatherapi.com/v1/current.json?key=" + weatherAPIKey + "&q=" + location + "&aqi=no";
float temp_c;
int humidity;
int cloud;
float feelslike_c;

void fetchWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, link);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();

      // Parse JSON response
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        // Extract weather data
        temp_c = doc["current"]["temp_c"];
        humidity = doc["current"]["humidity"];
        cloud = doc["current"]["cloud"];
        feelslike_c = doc["current"]["feelslike_c"];
      } 

    http.end();
    }
  }
}

void printWeather() {
  displayContent({  
                    DisplayItem("tmp:" + String(temp_c) + "C"), 
                    DisplayItem("lke:" + String(feelslike_c) + "C"),
                    DisplayItem("cld:" + String(cloud) + "%"),
                    DisplayItem("hum:" + String(humidity) + "%")
                 });
}

#endif