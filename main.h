#include "robot.h"

typedef struct {
    int markers;
    int obstacles;
    direction facing;
} args;

typedef struct {
    map* m;
    robot* r;
} ptrs;