// This file just implements the necessary stack operations and functionality to be used in my DFS algorithm.

#include <stdlib.h> // For NULL.
#include "stack.h"

stack* initStack() {
    stack* s = malloc(sizeof(stack));
    s->items = malloc(sizeof(struct square*) * 100); // Start with space for 100 squares.
    s->top = -1;
    s->size = 100;
    return s;
}

void push(stack* s, struct square* sq) {
    if (s->top == (s->size - 1)) {
        // If we have run out of space, add another 100 spaces.
        s->size += 100;
        s->items = realloc(s->items, (sizeof(struct square*) * s->size));
    }
    s->top++;
    s->items[s->top] = sq;
}

struct square* pop(stack* s) {
    if (s->top == -1) {
        return NULL;
    }
    struct square* sq = s->items[s->top];
    s->top--;
    return sq;
}

struct square* peek(stack* s) {
    if (s->top == -1) {
        return NULL;
    }
    return s->items[s->top];
}

int isEmpty(stack* s) {
    return (s->top == -1);
}

void freeStack(stack* s) {
    free(s->items);
    free(s);
}