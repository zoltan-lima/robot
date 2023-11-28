#include <stdlib.h>

#include "map.h"

void drawMap(map* m); // Forward declaration so that it is usable in initMap().
void addItems(map* m, int markers, int obstacles); // Forward declaration so that it is usable in initMap().

map* initMap(int markers, int obstacles) {
    map* m = malloc(sizeof(map));
    drawMap(m);
    addItems(m, markers, obstacles);

    return m;
}

void drawMap(map* m) {
    int x, y;
    int sqCounter = 0;

    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            x = j*SQUARE_SIZE;
            y = i*SQUARE_SIZE;

            // NOTE: Square coordinates are relative to the grid, and not the window.
            square sq;
            sq.x = x + (SQUARE_SEMISIZE);
            sq.y = y + (SQUARE_SEMISIZE);
            sq.type = B;

            m->grid[i][j] = sq;
            sqCounter++;

            // Since square coordinates are relative to the grid, and not the window, add offset.
            drawRect(x+OFFSET, y+OFFSET, SQUARE_SIZE, SQUARE_SIZE);
        }
    }
}

void fillSquare(square sq, colour c) {
    // De-centre the square.
    int x = sq.x - (SQUARE_SEMISIZE), y = sq.y - (SQUARE_SEMISIZE);
    setColour(c);

    // Off by one because we don't want to overwrite the border.
    fillRect(x+OFFSET+1, y+OFFSET+1, SQUARE_SIZE-1, SQUARE_SIZE-1);
}

void add(map* m, int n, squareType type) {
    int counter = 0;
    while(counter < n) {
        // Get a random square.
        int row = rand() % ROWS, col = rand() % COLS;
        square* sq = &m->grid[row][col];

        if (sq->type == B) {
            int isType = rand() % (SQUARES / n);
            sq->type = type;

            switch(type) {
                case B: break; // It will never be B since we have just overwritten it.
                case H: fillSquare(*sq, blue); m->home = sq; break;
                case M: fillSquare(*sq, lightgray); break;
                case O: fillSquare(*sq, black); break;
            }
            counter++;
            sleep(100);
        }
    }
}

void addItems(map* m, int markers, int obstacles) {
    add(m, 1, H);
    add(m, markers, M);
    add(m, obstacles, O);
}

int atHome(square* sq) {
    return (sq->type == H);
}

int atMarker(square* sq) {
    return (sq->type == M);
}

square* positionToSquare(map* m, int x, int y) {
    // Check if the position is within the bounds of the grid.
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        // Normalise the x and y coordinates to grid values.
        x = (x-SQUARE_SEMISIZE)/SQUARE_SIZE , y = (y-SQUARE_SEMISIZE)/SQUARE_SIZE;
        return &m->grid[y][x];
    } else {
        // Return NULL if the position is out of bounds.
        return NULL;
    }
}