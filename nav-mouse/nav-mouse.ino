#include <BleMouse.h>

const int BUTTON_PINS[] = {10, 11, 12, 13, 14}; // GPIO pin numbers for the buttons
const int BUTTON_COUNT = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);
BleMouse bleMouse("Navigation Mouse");
const int moveDelay = 25;

struct Coordinates
{
    int x;
    int y;
};

Coordinates screenResolution = {1920, 1080};

Coordinates buttonCoords[] =
{
    {640, 526},
    {163, 266},
    {483, 131},
    {158, 135},
    {483, 261}
};

void setup()
{
    Serial.begin(9600);

    for(int i = 0; i < BUTTON_COUNT; i++)
    {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }

    bleMouse.begin();
}

void resetCursorToTopLeft()
{
    // x
    for(int i = 0; i < screenResolution.x / 127; i++)
    {
        bleMouse.move(-127, 0);
        delay(moveDelay);
    }
    if(screenResolution.x % 127 > 0)
    {
        bleMouse.move(-(screenResolution.x % 127), 0);
        delay(moveDelay);
    }

    // y
    for(int i = 0; i < screenResolution.y / 127; i++)
    {
        bleMouse.move(0, -127);
        delay(moveDelay);
    }
    if(screenResolution.y % 127 > 0)
    {
        bleMouse.move(0, -(screenResolution.y % 127));
        delay(moveDelay);
    }
}

void moveCursorToCoordinate(int targetX, int targetY)
{
    resetCursorToTopLeft();

    int distanceX = targetX;
    int distanceY = targetY;

    // Move in increments of 127 pixels
    while(abs(distanceX) > 127 || abs(distanceY) > 127)
    {
        int moveX = distanceX > 127 ? 127 : (distanceX < -127 ? -127 : distanceX);
        int moveY = distanceY > 127 ? 127 : (distanceY < -127 ? -127 : distanceY);

        bleMouse.move(moveX, moveY);

        distanceX -= moveX;
        distanceY -= moveY;

        delay(moveDelay);
    }

    // Final movements
    if(distanceX != 0 || distanceY != 0)
    {
        bleMouse.move(distanceX, distanceY);
    }
}

void loop()
{
    if(bleMouse.isConnected())
    {
        for(int i = 0; i < BUTTON_COUNT; i++)
        {
            int currentButtonState = digitalRead(BUTTON_PINS[i]);

            if(currentButtonState == LOW)
            {
                moveCursorToCoordinate(buttonCoords[i].x, buttonCoords[i].y);
                bleMouse.click(MOUSE_LEFT);

                delay(750);
            }
        }
    }

    delay(20); // Don't overwhelm CPU
}

