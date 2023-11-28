struct square;

typedef struct {
    struct square** items;
    int top;
    int size;
    int max;
} stack;

stack* initStack();
void push(stack* s, struct square* sq);
struct square* pop(stack* s);
struct square* peek(stack* s);
int isEmpty(stack* s);
void freeStack(stack* s);