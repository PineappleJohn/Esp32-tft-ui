#include <Menus/menu.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

class TimeMenu : public Menu {
    bool returnToWifiScreen = false;

    WiFiUDP ntpUdp;
    NTPClient client = NTPClient(ntpUdp, "pool.ntp.org");

    void start(TFT_eSPI* tft) override {
        tft->fillScreen(TFT_BLACK);

        tft->drawString("Retrieving time...", 0, 0);
        try {

            client.begin();
            client.setTimeOffset(-18000);

            String formattedDate = client.getFormattedDate();
            int splitT = formattedDate.indexOf("T");
            String timestamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
            
            tft->fillScreen(TFT_BLACK);
            tft->drawString("It is " + timestamp, 0, 0);

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