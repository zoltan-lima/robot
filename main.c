#include <stdlib.h>
#include <time.h>

#include "main.h"

args parseArgs(int argc, char** argv) {
    args a;
    a.markers = 4;
    a.obstacles = 20;

    if (argc == 3) {
        int markers = atoi(argv[1]);
        int obstacles = atoi(argv[2]);

        if (markers > 0 && obstacles > 0 && (markers + obstacles) <= 99) {
            a.markers = markers;
            a.obstacles = obstacles;
        }
    }

    return a;
}

ptrs init(args a) {
    setWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    srand(time(0)); // Seed the random number generator.
    background();

    map* m = initMap(a.markers, a.obstacles);

    robot* r = initRobot(m);

    ptrs p = {m, r};
    return p;
}

int main (int argc, char** argv) {
    args a = parseArgs(argc, argv);
    ptrs p = init(a);

    sleep(1000);

    traverse(p.m, p.r);

    free(p.m);
    free(p.r);
}