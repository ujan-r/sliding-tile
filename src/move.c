#include <stdlib.h>

#include "src/move.h"


MoveFlag getRandomMove(void) {
    return 1 << (rand() % 4);
}
