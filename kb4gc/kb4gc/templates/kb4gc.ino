#include "Nintendo.h"

// Defines a "Gamecube Console" sending data to the console on pin 8
CGamecubeConsole GamecubeConsole(8);
// Structure for data to be sent to console
Gamecube_Data_t d = defaultGamecubeData;

// This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

// Pinouts
const int A         = {% a %};
const int B         = {% b %};
const int X         = {% x %};
const int Y         = {% y %};
const int Z         = {% z %};
const int START     = {% start %};
const int R         = {% r %};
const int L         = {% l %};
const int LEFT      = {% left %};
const int RIGHT     = {% right %};
const int UP        = {% up %};
const int DOWN      = {% down %};
const int X1        = {% x1 %};
const int X2        = {% x2 %};
const int Y1        = {% y1 %};
const int Y2        = {% y2 %};
const int CLEFT     = {% cleft %};
const int CRIGHT    = {% cright %};
const int CUP       = {% cup %};
const int CDOWN     = {% cdown %};
const int SWITCH    = {% switch_ %};

// Analog tilt modifiers
const int X1v = {$ x1v $};
const int X2v = {$ x2v $};
const int X3v = {$ x3v $};

const int Y1v = {$ y1v $};
const int Y2v = {$ y2v $};
const int Y3v = {$ y3v $};

void setup()
{
    // Establish the pin assignments to input pins
    pinMode(A, INPUT_PULLUP);
    pinMode(B, INPUT_PULLUP);
    pinMode(X, INPUT_PULLUP);
    pinMode(Y, INPUT_PULLUP);
    pinMode(Z, INPUT_PULLUP);
    pinMode(START, INPUT_PULLUP);

    pinMode(R, INPUT_PULLUP);
    pinMode(L, INPUT_PULLUP);
    pinMode(RLIGHT, INPUT_PULLUP);

    pinMode(LEFT, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);

    pinMode(X1, INPUT_PULLUP);
    pinMode(X2, INPUT_PULLUP);
    pinMode(Y1, INPUT_PULLUP);
    pinMode(Y2, INPUT_PULLUP);

    pinMode(CLEFT, INPUT_PULLUP);
    pinMode(CRIGHT, INPUT_PULLUP);
    pinMode(CUP, INPUT_PULLUP);
    pinMode(CDOWN, INPUT_PULLUP);

    pinMode(SWITCH, INPUT_PULLUP);

    // This is needed to run the code.
    GamecubeController1.read();
}

void loop()
{
    // Reset and establish all the values after the controller sends them
    // to the console and helps with initial "zeroing"
    int pinA = 0;
    int pinB = 0;
    int pinX = 0;
    int pinY = 0;
    int pinZ = 0;
    int pinSTART = 0;

    int pinR = 0;
    int pinL = 0;
    int pinRLIGHT = 0;

    int pinLEFT = 0;
    int pinRIGHT = 0;
    int pinUP = 0;
    int pinDOWN = 0;

    int pinX1 = 0;
    int pinX2 = 0;
    int pinY1 = 0;
    int pinY2 = 0;

    int pinCLEFT = 0;
    int pinCRIGHT = 0;
    int pinCUP = 0;
    int pinCDOWN = 0;

    int pinxAxisC = 128;
    int pinyAxisC = 128;

    int pinxAxis = 128;
    int xmod = 0;
    int pinyAxis = 128;

    int rightOne = 0;
    int leftOne = 0;
    int downOne = 0;

    int pinSWITCH = 0;

    // Read control stick as neutral when both left/right or up/down is
    // pressed at the same time.
    // Also sets parameters for the diffrent analog tilt modifiers IE: X1+X2 = X3
    if (digitalRead(LEFT) == HIGH && digitalRead(RIGHT) == LOW){
        pinxAxis = 128+86;
        if (digitalRead(X1) == LOW && digitalRead(X2) == HIGH) pinxAxis = X1v + 128;
        if (digitalRead(X1) == HIGH && digitalRead(X2) == LOW) pinxAxis = X2v + 128;
        if (digitalRead(X1) == LOW && digitalRead(X2) == LOW) pinxAxis = X3v + 128;
        rightOne = 1;
    }
    if (digitalRead(LEFT) == LOW && digitalRead(RIGHT) == HIGH){
        pinxAxis = 128-86;
        if (digitalRead(X1) == LOW && digitalRead(X2) == HIGH) pinxAxis = 128 - X1v;
        if (digitalRead(X1) == HIGH && digitalRead(X2) == LOW) pinxAxis = 128 - X2v;
        if (digitalRead(X1) == LOW && digitalRead(X2) == LOW) pinxAxis = 128 - X3v;
        leftOne = 1;
    }

    if (digitalRead(DOWN) == HIGH && digitalRead(UP) == LOW){
        pinyAxis = 128+86;
        if (digitalRead(Y1) == LOW && digitalRead(Y2) == HIGH) pinyAxis = 128 + Y1v;
        if (digitalRead(Y1) == HIGH && digitalRead(Y2) == LOW) pinyAxis = 128 + Y2v;
        if (digitalRead(Y1) == LOW && digitalRead(Y2) == LOW) pinyAxis = 128 + Y3v;
    }
    if (digitalRead(DOWN) == LOW && digitalRead(UP) == HIGH){
        pinyAxis = 128-86;
        if (digitalRead(Y1) == LOW && digitalRead(Y2) == HIGH) pinyAxis = 128 - Y1v;
        if (digitalRead(Y1) == HIGH && digitalRead(Y2) == LOW) pinyAxis = 128 - Y2v;
        if (digitalRead(Y1) == LOW && digitalRead(Y2) == LOW) pinyAxis = 128 - Y3v;
        downOne = 1;
    }

    // Disallow shield drops
    if (digitalRead(X1) == HIGH && digitalRead(X2) == HIGH && digitalRead(Y1) == HIGH && digitalRead(Y2) == HIGH && downOne == 1 && leftOne == 1){
        pinxAxis = 128-80;
        pinyAxis = 128-78;
    }

    if (digitalRead(X1) == HIGH && digitalRead(X2) == HIGH && digitalRead(Y1) == HIGH && digitalRead(Y2) == HIGH && downOne == 1 && rightOne == 1){
        pinxAxis = 128+80;
        pinyAxis = 128-78;
    }

    // C-stick
    if (digitalRead(CLEFT) == HIGH && digitalRead(CRIGHT) == LOW)pinxAxisC = 255;
    if (digitalRead(CLEFT) == LOW && digitalRead(CRIGHT) == HIGH)pinxAxisC = 0;
    if (digitalRead(CDOWN) == HIGH && digitalRead(CUP) == LOW)pinyAxisC = 255;
    if (digitalRead(CDOWN) == LOW && digitalRead(CUP) == HIGH)pinyAxisC = 0;

    if (digitalRead(A) == LOW)pinA = 1;
    if (digitalRead(B) == LOW)pinB = 1;
    if (digitalRead(X) == LOW)pinX = 1;
    if (digitalRead(Y) == LOW)pinY = 1;
    if (digitalRead(Z) == LOW)pinZ = 1;
    if (digitalRead(START) == LOW)pinSTART = 1;
    // Analog bumper
    if (digitalRead(RLIGHT) == LOW)pinRLIGHT = RLIGHTv;
    // Digital bumper
    if (digitalRead(R) == LOW)pinR = 1;
    if (digitalRead(L) == LOW)pinL = 1;

    if (digitalRead(SWITCH) == LOW)pinSWITCH = 1;

    d.report.dup = 0;
    d.report.dright = 0;
    d.report.ddown = 0;
    d.report.dleft = 0;

    // When switch is activated, X/Y 1/2 is Dpad
    if (pinSWITCH == 1){
        if(digitalRead(X1) == LOW)d.report.dleft = 1;
        if(digitalRead(X2) == LOW)d.report.ddown = 1;
        if(digitalRead(Y1) == LOW)d.report.dup = 1;
        if(digitalRead(Y2) == LOW)d.report.dright = 1;
    }



    // Construct data to report
    d.report.a = pinA;
    d.report.b = pinB;
    d.report.x = pinX;
    d.report.y = pinY;
    d.report.z = pinZ;
    d.report.start = pinSTART;
    d.report.r = pinR;
    d.report.l = pinL;
    d.report.left = pinRLIGHT;
    d.report.xAxis = pinxAxis;
    d.report.yAxis = pinyAxis;
    d.report.cxAxis = pinxAxisC;
    d.report.cyAxis = pinyAxisC;

    // Send data to console
    GamecubeConsole.write(d);
}
