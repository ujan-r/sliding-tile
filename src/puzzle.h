#ifndef INCLUDE_GUARD_CC57C29C_B018_4BB2_AA2F_5963CED1C57A
#define INCLUDE_GUARD_CC57C29C_B018_4BB2_AA2F_5963CED1C57A


#include <stdbool.h>
#include <stdint.h>

#include "src/move.h"


typedef struct puzzle Puzzle;


/* Create a new (optionally shuffled) `Puzzle` with the specified
 * dimensions.
 *
 * args:
 * - `rows`, `cols` - `Puzzle` dimensions
 * - `shuffle` - number of moves to make when shuffling
 *
 * returns:
 * - pointer to a newly created `Puzzle`
 * - NULL (on error)
 *
 * notes:
 * - use `freePuzzle()` to free this pointer
 * - shuffling uses `rand()`, so you should call `srand()` before the
 * first time you use this function
 * - the product of `rows` and `cols` should be >= 2 */
Puzzle * newPuzzle(uint8_t rows, uint8_t cols, unsigned shuffle);

/* Free a pointer returned by `newPuzzle()`.
 *
 * notes:
 * - it is safe to pass a null pointer to this function */
void freePuzzle(Puzzle *);

/* Compare the states of two puzzles.
 *
 * returns:
 * - `true` if the puzzles have the same dimensions and state
 * - `false` otherwise */
bool comparePuzzles(Puzzle const *, Puzzle const *);

/* Get the legal moves for the current state of a given puzzle.
 *
 * returns:
 * - flag representing the legal moves */
MoveFlag getLegalMoves(Puzzle *);

/* Try to make a move on a given puzzle.
 *
 * args:
 * - `move` - flag containing the move to make
 * - `puzzle`
 *
 * returns:
 * - `true` if the move was legal and could be made
 * - `false` otherwise */
bool makeMove(MoveFlag, Puzzle *);

/* Print the string representation of a puzzle to `stdscr`.
 *
 * notes:
 * - output is padded with whitespace to resemble a grid
 * - `stdscr` is assumed to exist
 * - the cursor is moved to (0, 0) before printing */
void printPuzzle(Puzzle *);


#endif /* !INCLUDE_GUARD_CC57C29C_B018_4BB2_AA2F_5963CED1C57A */
