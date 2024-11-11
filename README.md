Code for an ESP8266 and OLED display 0.96 128×64. 
The system switches between separately definable intervals between a time/day display, a weather information display, and a random fact display. 
The current time and day are fetched from the NTP server pool.ntp.org. 
Weather information (current temperature, feels like temperature, cloudiness, and humidity) is fetched from weatherAPI every hour. 
Random facts are obtained from numbersapi cycling through the four types of facts for random numbers between 0 and 1000.
The system is connected to the Arduino Cloud with a CloudSwitch variable that indicates whether the clock is on or off. This variable can for example be connected to Google Home.
