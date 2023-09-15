#include <curses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "src/puzzle.h"


static void swap(uint16_t i, uint16_t j, Puzzle *);
static void shufflePuzzle(Puzzle *, unsigned moves);


struct puzzle {
    uint16_t * const board;
    uint8_t    const rows;
    uint8_t    const cols;
    uint16_t         emptySquare;
};


Puzzle * newPuzzle(uint8_t rows, uint8_t cols, unsigned shuffle) {
    uint16_t const size = rows * cols;

    if (size < 2) goto error;

    Puzzle   *puzzle = malloc(sizeof *puzzle);
    uint16_t *board = calloc(size, sizeof *board);

    if (!puzzle || !board) goto memory_error;

    /* Populate the board with tiles and an empty square. */
    for (uint16_t i = 0; i < size; i++)
        board[i] = i + 1;
    board[size-1] = 0;

    /* Initialize the puzzle and copy its data to the return pointer. */
    memcpy(puzzle, &(Puzzle){board, rows, cols, size-1}, sizeof *puzzle);

    /* Shuffle the puzzle as necessary. */
    shufflePuzzle(puzzle, shuffle);

    return puzzle;

memory_error:
    free(board);
    free(puzzle);
error:
    return NULL;
}

void freePuzzle(Puzzle *puzzle) {
    if (!puzzle) return;

    free(puzzle->board);
    free(puzzle);
}

bool comparePuzzles(Puzzle const * const puzzle1, Puzzle const * const puzzle2) {
    if (puzzle1->rows != puzzle2->rows || puzzle1->cols != puzzle2->cols)
        return false;

    uint16_t const size = puzzle1->rows * puzzle1->cols;

    return !memcmp(puzzle1->board, puzzle2->board, size * sizeof *puzzle1->board);
}

MoveFlag getLegalMoves(Puzzle *puzzle) {
    MoveFlag flag = 0;

    uint8_t const rows = puzzle->rows;
    uint8_t const cols = puzzle->cols;
    uint8_t const emptyRow = puzzle->emptySquare / cols;
    uint8_t const emptyCol = puzzle->emptySquare % cols;

    if (emptyRow > 0)        flag |= DOWN;
    if (emptyCol > 0)        flag |= RIGHT;
    if (emptyRow < rows - 1) flag |= UP;
    if (emptyCol < cols - 1) flag |= LEFT;

    return flag;
}

bool makeMove(MoveFlag move, Puzzle *puzzle) {
    /* Check if the move is legal. */
    if (!(move & getLegalMoves(puzzle))) return false;

    uint16_t const dest = puzzle->emptySquare;
    uint16_t source;

    switch (move) {
        case UP    : source = dest + puzzle->cols; break;
        case DOWN  : source = dest - puzzle->cols; break;
        case LEFT  : source = dest + 1;            break;
        case RIGHT : source = dest - 1;            break;

        default:
            return false;
    }

    swap(source, dest, puzzle);
    puzzle->emptySquare = source;

    return true;
}

void printPuzzle(Puzzle *puzzle) {
    /* To properly display a grid, each square must have the same width
     * regardless of its value: a square containing 12 must take up the
     * same amount of space as a square containing 2.
     *
     * Set the square width to two plus the length of the string
     * representation of the largest number in the grid. */
    unsigned const largestNumber = puzzle->rows * puzzle->cols - 1;
    unsigned const squareWidth = snprintf(NULL, 0, "%u", largestNumber) + 2;

    move(0, 0);

    for (uint8_t row = 0; row < puzzle->rows; row++) {
        for (uint8_t col = 0; col < puzzle->cols; col++) {
            uint16_t index = (row * puzzle->cols) + col;
            uint16_t value = puzzle->board[index];

            if (value) printw("%*u", squareWidth, value);
            else       printw("%*c", squareWidth, ' ');
        }

        /* Print a row separator. */
        printw("\n");
    }
}


void shufflePuzzle(Puzzle *puzzle, unsigned moves) {
    for (unsigned i = 0; i < moves; i++) {
        MoveFlag const legalMoves = getLegalMoves(puzzle);

        MoveFlag randomMove;
        do randomMove = getRandomMove();
        while (!(randomMove & legalMoves));

        makeMove(randomMove, puzzle);
    }
}

void swap(uint16_t i, uint16_t j, Puzzle * const puzzle) {
    uint16_t * const board = puzzle->board;

    uint16_t const temp = board[i];
    board[i] = board[j];
    board[j] = temp;
}
