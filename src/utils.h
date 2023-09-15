#ifndef INCLUDE_GUARD_21E139E0_EDED_48CB_8691_5E862FC07F40
#define INCLUDE_GUARD_21E139E0_EDED_48CB_8691_5E862FC07F40


/* Print a message to `stderr` and exit.
 *
 * notes:
 * - this function takes `printf()`-style arguments
 * - the exit code is set to `EXIT_FAILURE` */
void exitWithError(char *format, ...);


#endif /* !INCLUDE_GUARD_21E139E0_EDED_48CB_8691_5E862FC07F40 */
