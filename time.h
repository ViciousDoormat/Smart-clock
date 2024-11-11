#ifndef TIME_H
#define TIME_H

#include <WiFiUdp.h>
#include <NTPClient.h>

// NTP server time
const char* ntpServer = "pool.ntp.org";
const long offset = 3600;
WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, offset);
const String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int currentHour = -1;

void printTime() {

  String time = timeClient.getFormattedTime().substring(0,5);
  String day = days[timeClient.getDay()];

  displayContent({DisplayItem(time, 3), DisplayItem(day)});
 
}

bool newHour() {
  int now = timeClient.getHours();
  if (currentHour != now) { 
    currentHour = now; 
    return true; 
  } else {
    return false; 
  }
}

#endif