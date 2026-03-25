#include <Menus/menu.h>

class TimeMenu : public Menu {
    bool returnToWifiScreen = false;

    void start(TFT_eSPI* tft) override {
        tft->fillScreen(TFT_BLACK);

        tft->drawString("Retrieving time...", 0, 0);
        try {
            
            tft->fillScreen(TFT_BLACK);
            tft->drawString("It is ", 0, 0);

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