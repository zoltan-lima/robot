#include "animations.h"
#include "map.h"
#include "stack.h"
#include "set.h"

typedef enum {F, L, R, P} move;

typedef struct robot {
    direction facing;
    int x;
    int y;
    stack* stack;
    set* visited;
    int hasMarker;
} robot;

robot* initRobot(map *m);
void traverse(map* m, robot* r);