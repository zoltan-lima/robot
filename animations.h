typedef enum {N, E, S, W} direction;

void drawRobot(int cx, int cy, direction facing);
void moveRobot(int* rx, int* ry, direction facing);