Code for an ESP8266 and OLED display 0.96 128×64. 
The system switches every 30 seconds between a time/day display and a weather information display. 
The current time and day are fetched from the NTP server pool.ntp.org. 
Weather information (current temperature, feels like temperature, cloudiness, and humidity) is fetched from weatherAPI every hour. 
The system is connected to the Arduino Cloud with a CloudSwitch variable that indicates whether the clock is on or off. This variable can for example be connected to Google Home.
