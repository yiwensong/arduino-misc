#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "Nintendo.h"

typedef union {
    // Pad buttons
    int A;
    int B;
    int X;
    int Y;
    int Start;

    // Shoulder buttons
    int Z;
    int R;
    int L;
    int RLight;

    // Stick
    int Left;
    int Right;
    int Up;
    int Down;

    // Cstick
    int CLeft;
    int CRight;
    int CUp;
    int CDown;

    // Modulus
    int Xmod;
    int Switch;
    int X1;
    int X2;
    int X3;
} keys_t;


typedef union {
    // Cstick axis
    int xAxisC;
    int yAxisC;

    // Control Stick axis
    int xAxis;
    int yAxis;
} axes_t;

typedef union {
    // Control stick state
    bool right;
    bool left;
    bool down;
} stick_t;

// Define our keycodes for each button
#define KEYCODE_A       {$ a $}
#define KEYCODE_B       {$ b $}
#define KEYCODE_X       {$ x $}
#define KEYCODE_Y       {$ y $}
#define KEYCODE_Z       {$ z $}
#define KEYCODE_START   {$ start $}
#define KEYCODE_R       {$ r $}
#define KEYCODE_L       {$ l $}
#define KEYCODE_RLIGHT  {$ rlight $}
#define KEYCODE_LEFT    {$ left $}
#define KEYCODE_RIGHT   {$ right $}
#define KEYCODE_UP      {$ up $}
#define KEYCODE_DOWN    {$ down $}
#define KEYCODE_X1      {$ x1 $}
#define KEYCODE_X2      {$ x2 $}
#define KEYCODE_Y1      {$ y1 $}
#define KEYCODE_Y2      {$ y2 $}
#define KEYCODE_CLEFT   {$ cleft $}
#define KEYCODE_CRIGHT  {$ cright $}
#define KEYCODE_CUP     {$ cup $}
#define KEYCODE_CDOWN   {$ cdown $}
#define KEYCODE_SWITCH  {$ switch_ $}

#define X1V {$ x1v $}
#define X2V {$ x2v $}
#define X3V {$ x3v $}
#define Y1V {$ y1v $}
#define Y2V {$ y2v $}
#define Y3V {$ y3v $}

#define STICK_CENTER 128
#define STICK_MAX 255
#define STICK_MIN 0
#define STICK_OFFSET 86

#define SHIELD_DROP_X 80
#define SHIELD_DROP_Y 78

#define GC_OUTPUT {$ gc_output $}

void handleKeys (bool*);
void getAxes ();
inline void reportData (Gamecube_Data_t);

#endif
