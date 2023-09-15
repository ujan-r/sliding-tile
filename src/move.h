#ifndef INCLUDE_GUARD_2FEBF988_3FCF_43BD_8AE8_E1265E3403A7
#define INCLUDE_GUARD_2FEBF988_3FCF_43BD_8AE8_E1265E3403A7


typedef enum move_flag {
    ERROR = 0,
    UP    = 1 << 0,
    DOWN  = 1 << 1,
    LEFT  = 1 << 2,
    RIGHT = 1 << 3
} MoveFlag;


/* Generate a random move.
 *
 * returns:
 * - `UP`, `DOWN`, `LEFT`, or `RIGHT`
 *
 * notes:
 * - this function uses `rand()`, so you should call `srand()` before
 * the first time you use it */
MoveFlag getRandomMove(void);


#endif /* !INCLUDE_GUARD_2FEBF988_3FCF_43BD_8AE8_E1265E3403A7 */
