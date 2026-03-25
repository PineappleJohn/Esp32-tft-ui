#include <Menus/menu.h>
#include <iostream>
#include <string>
#include <cstdio>

#define ITEMS 12

class MainMenu : public Menu
{
    const char* colors[ITEMS] = {"WiFi", "TestB", "TestC", "TestD", "TestE", "TestF", "TestG", "TestH", "TestI", "TestJ", "TestK", "TestL"};
    int16_t selectedValue = 0;
    bool pressed = false;

    void render(TFT_eSPI *tft)
    {
        try
        {
            tft->setTextColor(TFT_WHITE, TFT_BLACK);
            tft->fillScreen(TFT_BLACK);
            tft->setTextFont(2);
            tft->drawString("Main Menu", 130, 2);

            tft->drawLine(15, 25, 305, 25, TFT_WHITE);

            if (selectedValue >= ITEMS)
            {
                selectedValue = 0;
            }
            else if (selectedValue < 0)
            {
                selectedValue = ITEMS;
            }

            for (size_t i = 0; i < ITEMS; i++)
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

        if (tft->getTouch(&x, &y)) {
            pressed = true;
            //printf("Y: %d\n", (abs(x - 320) - 60) / 15);
            selectedValue = (abs(x - 320) - 60) / 20;
            render(tft);
        } else if (!tft->getTouch(&x, &y) && pressed) {
            //printf("SV: %d", selectedValue);
            pressed = false;
            switch (selectedValue) {
                case 0:
                return 1;
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
