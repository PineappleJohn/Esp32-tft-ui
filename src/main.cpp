// As this esp has touch screen, I will define touch screen compatible.

#define TOUCH_SCREEN_COMPATIBLE

#define MENU_LENGTH 5


#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Menus/menu.h>
#include <Menus/main_menu.cpp>
#include <Menus/WiFi.cpp>
#include <Menus/Wifi Related Menus/Ping.cpp>
#include <Menus/Wifi Related Menus/Time.cpp>
#include <Menus/Maruader/WifiMaruader.cpp>
#include <Utils/Constants.h>

#ifdef TOUCH_SCREEN_COMPATIBLE
#include <Touch/TouchScreen.cpp>
#endif

#ifdef ROTARY_ENCODER_COMPATIBLE
#include <ESP32RotaryEncoder.h>
#endif



//240x320
//                   CS  DC/RS  RESET    SDI/MOSI  SCK   SDO/MISO  BL      VCC    GND    
//ESP32-WROOM-32E:   15    2   ESP32-EN     13      14      12     27      5V     GND   

TFT_eSPI tft = TFT_eSPI();
TouchScreen tos = TouchScreen();

bool wasPressingScreenLastFrame = false;

Menu* menus[MENU_LENGTH] = {
  new MainMenu(),
  new WifiMenu(),
  new PingMenu(),
  new TimeMenu(),
  new MaruaderMenu()
};

int loadedMenu = 0;
int targetMenu = -1;

void loadMenu(int index) {
  loadedMenu = index;
  tft.fillScreen(menus[loadedMenu]->backgroundColor);
  menus[loadedMenu]->start(&tft);
}

void setup(void) {
  Serial.begin(9600);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  for (size_t i = 0; i < MENU_LENGTH; i++)
  {
    if (menus[i] != nullptr)
    menus[i]->touchScreen = &tos; // I cant initialize the array with the screen so I add it in later.
  }
  

#ifdef TOUCH_SCREEN_COMPATIBLE
  tos.CalibrateTouch(&tft);
#endif

  loadMenu(0);
}

void loop() {
  if (menus[loadedMenu] != nullptr) {
    targetMenu = menus[loadedMenu]->update(&tft);

    if (targetMenu != -1) {
      loadMenu(targetMenu);
    }

    /*if (tft.getTouch(&x, &y)) {
      wasPressingScreenLastFrame = true;
    } else if (wasPressingScreenLastFrame && !tft.getTouch(&x, &y)) { // Yeah idk any other way to do this.
      wasPressingScreenLastFrame = false;
      int targetMenu = menus[loadedMenu]->onEvent(&tft, TouchRelease);

      if (targetMenu == -1) return;
      loadedMenu = targetMenu;
    }*/
  }
}