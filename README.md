
What you need
1. ESP8266 module like D1 Mini
2. USB lead
3. Computer

Getting started
1. download and install platformio IDE from https://platformio.org/platformio-ide
2. clone this repository. ```git clone https://github.com/bottomquark/esp8266_reed_contact.git```
3. plug in the ESP8266 module into the computer
4. start platform IDE and open this project
5. compile and upload. 

If you prefer working with a command line, see https://docs.platformio.org/en/latest/installation.html for installing.
After installation, cd to the location where you cloned the repository and type ```platformio run -t upload```

If the built in LED of the ESP8266 module flashes, everything worked.

Documentation:

https://arduino-esp8266.readthedocs.io/en/latest/
https://arduino-esp8266.readthedocs.io/en/latest/reference.html#digital-io
