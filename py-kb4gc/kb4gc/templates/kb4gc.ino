#include "controller.h"

// Keyboard setup
USBHost usb;
KeyboardController keyboard(usb);

// Defines a "Gamecube Console" sending data to the console on pin 8
CGamecubeConsole GamecubeConsole( GC_OUTPUT );
// Structure for data to be sent to console
Gamecube_Data_t d = defaultGamecubeData;

// This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

// Number of key codes on a keyboard
#define KEYS 252
bool pressedKeys[KEYS];

// Polling rate for our keyboard
#define KB_POLL_RATE 9600

void setup()
{
    // Start your keyboard usb polling
    Serial.begin(KB_POLL_RATE);

    // This is a fake gc controller, it's needed to run the code
    GamecubeController1.read();

    for (int i=0; i<KEYS; i++) {
        pressedKeys[i] = false;
    }
}

void loop()
{
    // Look for key presses
    usb.Task();

    handleKeys(pressedKeys);
    getAxes();
    reportData(d);
    GamecubeConsole.write(d);
}

void keyPressed()
{
    int keyCode = keyboard.getKey();
    KEYS[keyCode] = true;
}

void keyReleased()
{
    int keyCode = keyboard.getKey();
    KEYS[keyCode] = false;
}
