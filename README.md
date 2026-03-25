# ESP32-TFT
This code is a basic ui for an esp32 tft display. The one I used to develop this C/C++ program is a 3.2" 240x320 lcd full color display.
## Connections
> As of now (3/25/26) this program focuses on touch screen but rotary encoder support is planned. 
<br> 

For the microcontroller I am using, which is an ESP32-WROOM-32E, these connections should work fine:<br>
|CS | DC/RS | RESET  |  SDI/MOSI | SCK |  SDO/MISO | BL   |   VCC  |  GND |
|---|-------|--------|-----------|-----|-----------|------|--------|------|
|15 |   2  | ESP32-EN|     13    |  14 |     12    | 27   |   5V   |  GND |
|   |      |         |           |     |           |      |        |      |  

