struct square;

typedef struct {
    struct square** items;
    int index;
    int size;
} set;

set* initVisited();
void append(set* v, struct square* sq);
int contains(set* v, struct square* sq);
void clearVisited(set *v);
void freeVisited(set* v);