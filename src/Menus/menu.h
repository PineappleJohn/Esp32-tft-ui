#ifndef MENUINIT
#define MENUINIT
#include <iostream>
#include <TFT_eSPI.h>
#include <Touch/TouchScreen.cpp>

enum Event {
    RotaryRight,
    RotaryLeft,
    RotaryClick,
    TouchPress,
    TouchRelease
};

/*
Menu class
*/
class Menu
{
    public: 
        mutable TouchScreen* touchScreen;
        long backgroundColor = 0x0000;
        bool loaded = false;

        virtual ~Menu() {delete touchScreen;}
        
        virtual void start(TFT_eSPI* tft) = 0;
        virtual int update(TFT_eSPI* tft) = 0;

        /*
         *  Called whenever an event like the rotary encoder turning and will return the screen to swap to (-1 to stay on the same screen) 
         */
        virtual int onEvent(TFT_eSPI* tft, Event event) = 0;
};

#endif