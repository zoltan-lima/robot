#include "graphics.h"

#define ROWS 10
#define COLS 10
#define SQUARES ROWS*COLS
#define OFFSET 100
#define SQUARE_SIZE 75
#define SQUARE_SEMISIZE (SQUARE_SIZE/2)
#define GRID_SIZE (ROWS*SQUARE_SIZE)
#define WINDOW_SIZE (2*OFFSET)+GRID_SIZE

// B = blank, H = home, O = obstacle, M = marker.
typedef enum {B, H, M, O} squareType;

typedef struct square {
    int x;
    int y;
    squareType type;
} square;

typedef struct map {
    square grid[ROWS][COLS];
    square* home;
} map;

map* initMap();
void fillSquare(square sq, colour c);
void addItems(map* m, int markers, int obstacles);
int atHome(square* sq);
int atMarker(square* sq);
square* positionToSquare(map* m, int x, int y);