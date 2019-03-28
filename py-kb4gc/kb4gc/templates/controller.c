#include "controller.h"

keys_t vKeys;
axes_t axes;
stick_t stick;

/** Make sure that pKeys has at least 255 elements
 *  if not, we might run off the end of the array.
 */
void handleKeys (bool *pKeys) {
    vKeys.A       = (int) pKeys[KEYCODE_A];
    vKeys.B       = (int) pKeys[KEYCODE_B];
    vKeys.X       = (int) pKeys[KEYCODE_X];
    vKeys.Y       = (int) pKeys[KEYCODE_Y];
    vKeys.Start   = (int) pKeys[KEYCODE_START];
    vKeys.Z       = (int) pKeys[KEYCODE_Z];
    vKeys.R       = (int) pKeys[KEYCODE_R];
    vKeys.L       = (int) pKeys[KEYCODE_L];
    vKeys.RLight  = (int) pKeys[KEYCODE_RLIGHT];
    vKeys.Left    = (int) pKeys[KEYCODE_LEFT];
    vKeys.Right   = (int) pKeys[KEYCODE_RIGHT];
    vKeys.Up      = (int) pKeys[KEYCODE_UP];
    vKeys.Down    = (int) pKeys[KEYCODE_DOWN];
    vKeys.CLeft   = (int) pKeys[KEYCODE_CLEFT];
    vKeys.CRight  = (int) pKeys[KEYCODE_CRIGHT];
    vKeys.CUp     = (int) pKeys[KEYCODE_CUP];
    vKeys.CDown   = (int) pKeys[KEYCODE_CDOWN];
    vKeys.Switch  = (int) pKeys[KEYCODE_SWITCH];
    vKeys.X1      = (int) pKeys[KEYCODE_X1];
    vKeys.X2      = (int) pKeys[KEYCODE_X2];
    vKeys.Y1      = (int) pKeys[KEYCODE_Y1];
    vKeys.Y2      = (int) pKeys[KEYCODE_Y2];
}


void getAxes () {
    axes.xAxisC = STICK_CENTER;
    axes.yAxisC = STICK_CENTER;
    if (vKeys.CLeft == 1 &&  vKeys.CRight == 0)   axes.xAxisC = STICK_MAX;
    if (vKeys.CLeft == 0 &&  vKeys.CRight == 1)   axes.xAxisC = STICK_MIN;
    if (vKeys.CDown == 1 &&  vKeys.CUp == 0)      axes.yAxisC = STICK_MAX;
    if (vKeys.CDown == 0 &&  vKeys.CUp == 1)      axes.yAxisC = STICK_MIN;

    axes.xAxis = STICK_CENTER;
    axes.yAxis = STICK_CENTER;
    stick.right = false;
    stick.left = false;
    stick.down = false;
    if (vKeys.Left == 1 && vKeys.Right == 0) {
        axes.xAxis = STICK_CENTER + STICK_OFFSET;
        if (vKeys.X1 == 0 && vKeys.X2 == 1) axes.xAxis = STICK_CENTER + X1V;
        if (vKeys.X1 == 1 && vKeys.X2 == 0) axes.xAxis = STICK_CENTER + X2V;
        if (vKeys.X1 == 1 && vKeys.X2 == 1) axes.xAxis = STICK_CENTER + X3V;
        stick.right = true;
    }
    if (vKeys.Left == 0 && vKeys.Right == 1) {
        axes.xAxis = STICK_CENTER - STICK_OFFSET;
        if (vKeys.X1 == 0 && vKeys.X2 == 1) axes.xAxis = STICK_CENTER - X1V;
        if (vKeys.X1 == 1 && vKeys.X2 == 0) axes.xAxis = STICK_CENTER - X2V;
        if (vKeys.X1 == 1 && vKeys.X2 == 1) axes.xAxis = STICK_CENTER - X3V;
        stick.left = true;
    }
    if (vKeys.Down == 1 && vKeys.Up == 0) {
        axes.yAxis = STICK_CENTER + STICK_OFFSET;
        if (vKeys.Y1 == 0 && vKeys.Y2 == 1) axes.yAxis = STICK_CENTER + Y1V;
        if (vKeys.Y1 == 1 && vKeys.Y2 == 0) axes.yAxis = STICK_CENTER + Y2V;
        if (vKeys.Y1 == 1 && vKeys.Y2 == 1) axes.yAxis = STICK_CENTER + Y3V;
    }
    if (vKeys.Down == 0 && vKeys.Up == 1) {
        axes.yAxis = STICK_CENTER - STICK_OFFSET;
        if (vKeys.Y1 == 0 && vKeys.Y2 == 1) axes.yAxis = STICK_CENTER - Y1V;
        if (vKeys.Y1 == 1 && vKeys.Y2 == 0) axes.yAxis = STICK_CENTER - Y2V;
        if (vKeys.Y1 == 1 && vKeys.Y2 == 1) axes.yAxis = STICK_CENTER - Y3V;
        stick.down = true;
    }

    preventShieldDrop();
}

void preventShieldDrop ()
{
    // We don't prevent shield drops in this code, sorry.
}

inline void handleDPad(Gamecube_Data_t data) {
    if (vKeys.Switch == 1) {
        data.report.dleft = vKeys.X1;
        data.report.ddown = vKeys.X2;
        data.report.dup = vKeys.Y1;
        data.report.dright = vKeys.Y2;
    } else {
        data.report.dleft = 0;
        data.report.ddown = 0;
        data.report.dup = 0;
        data.report.dright = 0;
    }
}

inline void reportData (Gamecube_Data_t data) {
    data.report.a = vKeys.A;
    data.report.a = vKeys.A;
    data.report.b = vKeys.B;
    data.report.x = vKeys.X;
    data.report.y = vKeys.Y;
    data.report.z = vKeys.Z;
    data.report.start = vKeys.Start;
    data.report.r = vKeys.R;
    data.report.l = vKeys.L;
    data.report.left = vKeys.RLight;
    data.report.xAxis = axes.xAxis;
    data.report.yAxis = axes.yAxis;
    data.report.cxAxis = axes.xAxisC;
    data.report.cyAxis = axes.yAxisC;

    handleDPad(data)
}
