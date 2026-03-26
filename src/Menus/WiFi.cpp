#include <Menus/menu.h>
#include <WiFi.h>

// This file defines my specific ssid and password, you will have to create your own for your machine.
#include <Utils/Credentials.h>

class WifiMenu : public Menu {
    const char* colors[5] = {"Connect", "Ping", "Get Time", "None", "Back"};
    int16_t selectedValue = 0;
    bool pressed = false;

    bool connectedStatus = false;

    void render(TFT_eSPI *tft)
    {
        try
        {
            tft->setTextColor(TFT_WHITE, TFT_BLACK);
            tft->fillScreen(TFT_BLACK);
            tft->setTextFont(2);
            tft->drawString("WiFi", 130, 2);
            tft->drawString(connectedStatus ? "Connected" : "Disconnected", 160, 2);

            tft->drawLine(15, 25, 305, 25, TFT_WHITE);

            if (selectedValue >= 5)
            {
                selectedValue = 0;
            }
            else if (selectedValue < 0)
            {
                selectedValue = 5;
            }

            for (size_t i = 0; i < 5; i++)
            {
                if (i == selectedValue)
                    tft->setTextColor(TFT_BLACK, TFT_WHITE);
                else
                {
                    tft->setTextColor(TFT_WHITE, TFT_BLACK);
                }
                tft->drawString(colors[i], 15, 40 + (15 * i));
            }
        }
        catch (...)
        {
            printf("Error at rendering");
        }
    }

    bool ConnectToWifi() {
        return ConnectToWifi(SSID, PASSWORD); // See the top of the file referencing the actual definition of these variables.
    }

    bool ConnectToWifi(const char* ssid, const char* password) {
        WiFi.begin(ssid, password);

        delay(1500);
        
        return WiFi.status() == WL_CONNECTED;
    }

    void start(TFT_eSPI *tft) override
    {
        render(tft);
    }

    int update(TFT_eSPI *tft) override
    {
        uint16_t x, y;

        if (tft->getTouch(&x, &y)) {
            pressed = true;
            //printf("Y: %d\n", (abs(x - 320) - 60) / 15);
            selectedValue = (abs(x - 320) - 60) / 20;
            render(tft);
        } else if (!tft->getTouch(&x, &y) && pressed) {
            pressed = false;
            switch (selectedValue) {
                case 0:
                connectedStatus = ConnectToWifi();
                delay(250);
                render(tft);
                return -1;
                case 1:
                return 2;
                case 2: // get time
                
                return 3;
                case 3:
                return -1;
                case 4:
                return 0;
            }
        }

        return -1;
    }

    int onEvent(TFT_eSPI *tft, Event event) override {
        switch (event)
        {
            case RotaryRight:
                selectedValue++;
                return -1;
            case RotaryLeft:
                selectedValue--;
                return -1;
            case TouchRelease:
            case RotaryClick:
                render(tft);

                if (colors[selectedValue]) // C++ doesn't techincally support strings in switch statements to if/else it is
                {
                    if (colors[selectedValue] == colors[0]) {
                        return 1;
                    }
                }

                return -1;
            default:
                return -1;
        }
    }
};