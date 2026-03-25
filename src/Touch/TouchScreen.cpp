#ifndef ts
#define ts
#include <TFT_eSPI.h>
#include <Touch/Point.h>

class TouchScreen
{
    /*
    The last touched point, use GetTouched() or IsTouchingScreen() to update it.
    */
    Point lastTouched = Point();

public:
    /*
    Calibrates touch screen based off of pre-tested points.
    */
    void CalibrateTouch(TFT_eSPI *tft)
    {
        uint16_t calData[5] = {280, 3597, 390, 3565, 6};
        tft->setTouch(calData);
    }

    /*
    Calibrates touch screen based off of your own points.
    */
    void CalibrateTouch(TFT_eSPI *tft, uint16_t calData[5])
    {
        tft->setTouch(calData);
    }

    /*
    Returns true if the user is touching the screen, also updates last touched coords.
    */
    bool IsTouchingScreen(TFT_eSPI *tft)
    {
        return tft->getTouch(lastTouched.x, lastTouched.y);
    }

    /*
    Returns the point of last touched, make sure to use IsTouchingScreen to tell if the user is actually touching the screen.
    */
    Point GetTouched(TFT_eSPI *tft)
    {
        tft->getTouch(lastTouched.x, lastTouched.y);
        return lastTouched;
    }
};
#endif