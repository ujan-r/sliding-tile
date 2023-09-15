#include <curses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "src/game.h"
#include "src/move.h"
#include "src/puzzle.h"
#include "src/utils.h"


static Puzzle *puzzle, *goal;
static bool done, solved;
static time_t start, end;
static unsigned moves;

static void openWindow(void);
static void closeWindow(void);
static void processInput(void);


void play(uint8_t rows, uint8_t cols) {
    srand(time(NULL));

    puzzle = newPuzzle(rows, cols, rows*cols*10);
    goal   = newPuzzle(rows, cols, 0);

    if (!goal || !puzzle) {
        free(goal);
        free(puzzle);
        exitWithError("error: `newPuzzle()` returned NULL\n");
    }

    done = comparePuzzles(puzzle, goal);
    solved = done;

    openWindow();
    start = time(NULL);

    printPuzzle(puzzle);

    while (!done) {
        processInput();
        printPuzzle(puzzle);
    }

    end = time(NULL);
    closeWindow();

    if (solved) printf("solved in %ld s (%u moves)\n", end - start, moves);
}

void openWindow(void) {
    initscr();
    keypad(stdscr, true);
    curs_set(0);
}

void closeWindow(void) {
    endwin();
}

void processInput(void) {
    MoveFlag move;

    switch (getch()) {
        case KEY_UP    : move = UP;    break;
        case KEY_DOWN  : move = DOWN;  break;
        case KEY_LEFT  : move = LEFT;  break;
        case KEY_RIGHT : move = RIGHT; break;

        case 'q':
            done = true;
            return;

        default:
            processInput();
            return;
    }

    if (makeMove(move, puzzle)) {
        moves++;

        if (comparePuzzles(puzzle, goal)) {
            solved = true;
            done = true;
        }
    }
}
