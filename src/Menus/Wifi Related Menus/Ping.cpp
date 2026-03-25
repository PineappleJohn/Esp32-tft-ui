#include <Menus/menu.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <ESP32Ping.h>

class PingMenu : public Menu {
    bool returnToWifiScreen = false;

    void start(TFT_eSPI* tft) override {
        tft->fillScreen(TFT_BLACK);

        tft->drawString("Pinging Google.com...", 0, 0);
        try {
            Ping.ping("www.google.com");

            tft->fillScreen(TFT_BLACK);
            tft->drawString("Results: ", 0, 0);
            tft->drawString(String(Ping.averageTime()), 0, 20);

            delay(2000);

            returnToWifiScreen = true;
        } catch (...) 
        {
            tft->drawString("Unhandeled exeption while pinging", 130, 50);
        }
    }

    int update(TFT_eSPI* tft) override {
        return returnToWifiScreen ? 1 : -1;
    }

    int onEvent(TFT_eSPI* tft, Event event) {
        return -1;
    }
};