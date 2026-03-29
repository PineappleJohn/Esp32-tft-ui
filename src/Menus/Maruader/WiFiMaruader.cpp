#include <Menus/menu.h>

class MaruaderMenu : public Menu {
    const char* colors[3] = {"Test", "None", "Back"};
    int16_t selectedValue = 0;
    bool pressed = false;

    HardwareSerial uartConnection = HardwareSerial(2); // TODO: Test 0-2 

    void render(TFT_eSPI *tft)
    {
        try
        {
            tft->setTextColor(TFT_WHITE, TFT_BLACK);
            tft->fillScreen(TFT_BLACK);
            tft->setTextFont(2);
            tft->drawString("UART Communication", 130, 2);

            tft->drawLine(15, 25, 305, 25, TFT_WHITE);

            if (selectedValue >= 1)
            {
                selectedValue = 0;
            }
            else if (selectedValue < 0)
            {
                selectedValue = 3;
            }

            for (size_t i = 0; i < 3; i++)
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

        uartConnection.begin(115200, SERIAL_8N1, 16, 17);
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
                uartConnection.println("what is happening"); // Its not  working
                return -1;
                case 2:
                return 1;
            }

            
        }

        if (uartConnection.available()) 
        {
            String data = uartConnection.readString();//Until('\n');
            printf("Received: %s\n", data.c_str());
            render(tft);
            tft->drawString(data, 15, 150);
        }

        return -1;
    }

    int onEvent(TFT_eSPI* tft, Event event) override {
        return -1;
    }
};