// This file just implements the necessary operations for a visited array in a DFS algorithm (though it acts more like a set).

#include "stdlib.h"
#include "set.h"

set* initVisited() {
    set* v = malloc(sizeof(set));
    v->items = malloc(sizeof(struct square*) * 100); // Start with space for 100 squares.
    v->index = 0;
    v->size = 100;
    return v;
}

void append(set* v, struct square* sq) {
    if (contains(v, sq)) return; // No duplicate squares.
    if (v->index == v->size) {
        // If we have run out of space, add another 100 spaces.
        v->size += 100;
        v->items = realloc(v->items, (sizeof(struct square*) * v->size));
    }
    v->items[v->index] = sq;
    v->index++;
}

int contains(set* v, struct square* sq) {
    for (int i=0; i<v->index; i++) {
        if (v->items[i] == sq) {
            return 1;
        }
    }
    return 0;
}

void clearVisited(set *v) {
    for (int i=0; i<v->index; i++) {
        v->items[i] = NULL;
    }
    v->index = 0;
}

void freeVisited(set* v) {
    free(v->items);
    free(v);
}