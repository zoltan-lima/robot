#include <stdlib.h>
#include <string.h>

#include "robot.h"

robot* initRobot(map* m) {
    robot* r = malloc(sizeof(robot));
    r->facing = N;
    r->x = m->home->x;
    r->y = m->home->y;

    r->stack = initStack();
    r->visited = initVisited();

    drawRobot(r->x, r->y, r->facing);

    return r;
}

void forward(robot* r) {
    moveRobot(&r->x, &r->y, r->facing);
}

void left(robot* r) {
    switch (r->facing) {
        case N: r->facing = W; break;
        case E: r->facing = N; break;
        case S: r->facing = E; break;
        case W: r->facing = S; break;
    }

    drawRobot(r->x, r->y, r->facing);
}

void right(robot* r) {
    switch (r->facing) {
        case N: r->facing = E; break;
        case E: r->facing = S; break;
        case S: r->facing = W; break;
        case W: r->facing = N; break;
    }

    drawRobot(r->x, r->y, r->facing);
}

void pickUpMarker(robot* r, square* sq) {
    sq->type = B;
    r->hasMarker = 1;
}

void dropMarker(robot* r) {
    r->hasMarker = 0;
}

int isCarryingAMarker(robot* r) {
    return r->hasMarker;
}

void moveMarker(robot* r, square* c, square* n) {
    // Clear the previous square.
    background();
    fillSquare(*c, white);

    if (atHome(n) == 0) fillSquare(*n, lightgray);
}

square** getNeighbours(map* m, square* sq) {
    int x = sq->x, y = sq->y;
    square** neighbours = malloc(sizeof(square*) * 4);
    square* s;
    // For each direction, get the neighbouring square.
    for (int i=N; i<=W; i++) {
        switch (i) {
            case N: s = positionToSquare(m, x, y-SQUARE_SIZE); break;
            case E: s = positionToSquare(m, x+SQUARE_SIZE, y); break;
            case S: s = positionToSquare(m, x, y+SQUARE_SIZE); break;
            case W: s = positionToSquare(m, x-SQUARE_SIZE, y); break;
        }
        if (s == NULL || s->type == O) neighbours[i] = NULL; // Obstacles can't be traversed so return null if the square is an obstacle.
        else neighbours[i] = s;
    }

    return neighbours;
}

square* getUnvisitedNeighbour(set* v, square** neighbours) {
    for (int i=N; i<=W; i++) {
        // Return as soon as an unvisited neighbour is found.
        if (neighbours[i] != NULL && contains(v, neighbours[i]) == 0) return neighbours[i];
    }
    return NULL;
}

void interpretMove(robot* r, square* c, square* n) {
    // Given two neighbouring squares, determine the move(s) required.
    // Determine which direction the robot is facing, and orientate it so that it will move towards the new square.
    if (n->y < c->y) {
        switch(r->facing) {
            case N: break; // Already facing north.
            case E: left(r); break;
            case S: left(r); left(r); break;
            case W: right(r); break;
        }
    }
    else if (n->x > c->x) {
        switch(r->facing) {
            case N: right(r); break;
            case E: break; // Already facing right.
            case S: left(r); break;
            case W: left(r); left(r); break;
        }
    }
    else if (n->y > c->y) {
        switch(r->facing) {
            case N: left(r); left(r); break;
            case E: right(r); break;
            case S: break; // Already facing south.
            case W: left(r); break;
        }
    }
    else if (n->x < c-> x) {
        switch(r->facing) {
            case N: left(r); break;
            case E: left(r); left(r); break;
            case S: right(r); break;
            case W: break; // Already facing west.
        }
    }
    else return;

    // After the robot is ifacing the correct direction, move it forward.
    forward(r);
    if (isCarryingAMarker(r) == 1) moveMarker(r, c, n);
}

stack* goHome(robot* r, square* current) {
    stack* path = initStack();

    while (isEmpty(r->stack) == 0) {
        square* prev = pop(r->stack);
        push(path, prev);
        interpretMove(r, current, prev);
        current = prev;
    }

    dropMarker(r);

    return path;
}

void traverse(map* m, robot* r) {
    // This function implements the DFS algorithm.

    // Pointers to the stack and visited array, for convenience.
    stack* s = r->stack;
    set* v = r->visited;

    // The robot's position has already been intialised to the home square.
    square* home = positionToSquare(m, r->x, r->y);
    push(s, home);
    append(v, home);

    while(isEmpty(s) == 0) {
        // While there are still squares to visit, continue to search for markers.
        square* current = peek(s);

        if(atMarker(current) == 1) {
            pickUpMarker(r, current);

            // Go back home while recording the moves taken to go back home.
            stack* path = goHome(r, current);
            square* c = home;

            // Then return to the current square.
            while (isEmpty(path) == 0) {
                square* prev = pop(path);
                push(s, prev);
                interpretMove(r, c, prev);
                c = prev;
            }

            freeStack(path);
            // Continue the DFS.
        }

        // The map is only used to find the neighbouring squares.
        square** neighbours = getNeighbours(m, current);
        square* nb = getUnvisitedNeighbour(v, neighbours);
        free(neighbours);

        if (nb == NULL) {
            // No unvisited neighbours.
            // Backtrack by 1.
            pop(s);
            if(isEmpty(s) == 0) {
                square* prev = peek(s);
                interpretMove(r, current, prev);
            }
        }
        else {
            // Unvisited neighbour found.
            push(s, nb);
            append(v, nb);
            interpretMove(r, current, nb);
        }
    }

    // No more markers are in the grid, free the memory used by the stack and visited array.
    freeStack(s);
    freeVisited(v);
}