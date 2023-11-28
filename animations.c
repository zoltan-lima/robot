#include "map.h"
#include "animations.h"

void removeRobot() {
    foreground();
    clear();
}

void drawRobot(int cx, int cy, direction facing) {
    removeRobot();

    // The robot is represented by a green triangle.
    setColour(green);
    int x[3], y[3];

    int r = SQUARE_SEMISIZE;

    cx += OFFSET, cy += OFFSET;
    r--; // To account for padding.
    switch(facing) {
        case N: {
            x[0] = cx - r;
            y[0] = cy + r + 1; // Correct the offset.
            x[1] = cx;
            y[1] = cy - r;
            x[2] = cx + r + 1;
            y[2] = cy + r + 1;
            break;
        }
        case E: {
            x[0] = cx - r;
            y[0] = cy - r;
            x[1] = cx + r + 1;
            y[1] = cy;
            x[2] = cx - r;
            y[2] = cy + r + 1;
            break;
        }
        case S: {
            x[0] = cx + r + 1;
            y[0] = cy - r;
            x[1] = cx;
            y[1] = cy + r + 1;
            x[2] = cx - r;
            y[2] = cy - r;
            break;
        }
        case W: {
            x[0] = cx + r + 1;
            y[0] = cy + r + 1;
            x[1] = cx - r;
            y[1] = cy;
            x[2] = cx + r + 1;
            y[2] = cy - r;
            break;
        }
    }
    
    drawPolygon(3, x, y);
    fillPolygon(3, x, y);
}

void moveRobot(int* rx, int* ry, direction facing) {
    int diff = 5;
    // Smoothly animate the robot moving between squares.
    for (int i=0; i<SQUARE_SIZE; i+=diff) {
        switch (facing) {
            case N: *ry -= diff; break;
            case E: *rx += diff; break;
            case S: *ry += diff; break;
            case W: *rx -= diff; break;
        }

        drawRobot(*rx, *ry, facing);
        sleep(25);
    }
}