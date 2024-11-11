#ifndef FACT_H
#define FACT_H

#include <ESP8266HTTPClient.h> //TODO move to config?
#include <WiFiClient.h>

const int numberOfTypes = 4;
const String types[numberOfTypes] = {"trivia", "math", "date", "year"};
int cycle = 0;

const String factLink = "http://numbersapi.com/";

String getLink() {
  cycle = (cycle + 1) % numberOfTypes; 
  return factLink + String(random(0, 1000)) + "/" + types[cycle];
}

String fetchRandomFact() {
  String payload = "";
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, getLink());

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      payload = http.getString();  
    }

    http.end();
  }
  return payload;
}

void printFact() {
  displayContent({ DisplayItem(fetchRandomFact(), 1) }); //TODO add enters when word crosses screen border
}

#endif