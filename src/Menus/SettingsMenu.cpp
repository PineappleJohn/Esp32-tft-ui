#include <Menus/menu.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Utils/Constants.h>
#include "LittleFS.h"
#include "iostream"

class SettingsMenu : public Menu
{
    const char *colors[5] = {"Raise brightness", "Lower brightness", "", "Developer mode", "Back"};
    int16_t selectedValue = 0;
    bool pressed = false;
    String version = "";

    void render(TFT_eSPI *tft)
    {
        try
        {
            tft->setTextColor(TFT_WHITE, TFT_BLACK);
            tft->fillScreen(TFT_BLACK);
            tft->setTextFont(2);
            tft->drawString("Settings", 130, 2);

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

    void start(TFT_eSPI *tft) override
    {
        render(tft);
    }

    int update(TFT_eSPI *tft) override
    {
        uint16_t x, y;

        if (tft->getTouch(&x, &y))
        {
            pressed = true;
            selectedValue = (abs(x - 320) - 60) / 20;
            render(tft);
        }
        else if (!tft->getTouch(&x, &y) && pressed)
        {
            pressed = false;
            switch (selectedValue)
            {
            case 0:
                return -1;
            case 3:
                debugMode = !debugMode;
                return -1;
            case 4:
                return 1;
            }
        }

        return -1;
    }

    int onEvent(TFT_eSPI *tft, Event event) override
    {
        return -1;
    }
};