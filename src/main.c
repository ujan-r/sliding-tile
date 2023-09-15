#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/game.h"
#include "src/move.h"
#include "src/puzzle.h"
#include "src/utils.h"


static uint8_t rows, cols;


static void parseArgs(int argc, char *argv[]);


int main(int argc, char *argv[]) {
    parseArgs(argc, argv);
    play(rows, cols);

    return 0;
}


void parseArgs(int argc, char *argv[]) {
    if (argc != 3) exitWithError("usage: %s rows cols\n", argv[0]);

    int const passedRows = atoi(argv[1]);
    int const passedCols = atoi(argv[2]);

    if (passedRows == 0 || passedCols == 0 || passedRows * passedCols < 2)
        exitWithError("error: bad dimensions\n"
                      "usage: %s rows cols\n", argv[0]);

    if (passedRows > UINT8_MAX || passedCols > UINT8_MAX)
        exitWithError("error: dimensions must not exceed %ux%u\n",
                      UINT8_MAX, UINT8_MAX);

    rows = passedRows;
    cols = passedCols;
}
