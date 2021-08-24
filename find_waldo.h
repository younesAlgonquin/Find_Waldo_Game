#ifndef FIND_WALDO_H_
#define FIND_WALDO_H_

/**
 ** Header (.H) file for Find Waldo Game
 **
 ** You are not permitted to add / subtract / alter from this file, with
 ** the notableable exception of conditional compilation using DEBUG
 **
 ** @version 1.0
 **
 ** @author Gerald.Hurdle@AlgonquinCollege.com
 **/

/* If #define DEBUG, then put Waldo at world[#DEBUG_ROW][#DEBUG_COL] */
#define DEBUG

/* If NOT #define DEBUG, then put Waldo at world[random row][random column]   */
/* Constraint:                                                                */
/*  ("random row" && "random column") cannot equal (#DEBUG_ROW && #DEBUG_COL) */
/* #TODO - uncomment next line to un-def DEBUG ***************************************/

/*#undef DEBUG*/

#define DEBUG_COL 5
#define DEBUG_ROW 5

/* If User enters: HINT_ROW_INPUT HINT_COL_INPUT */
/* Then display hint where Waldo is hiding.      */
#define HINT_ROW_INPUT (-1)
#define HINT_COL_INPUT (-1)

/* Waldo's world is MAX_ROWS by MAX_COLS */
#define MAX_COLS 10
#define MAX_ROWS 10

/* User can guess up to (and including) MAX_ROUNDS            */
/* EXIT_FAILURE if User can't find Waldo in under MAX_ROUNDS  */
/* Do not count a guess if the User enters invalid data.      */
/* Do not count a guest if the user enters HINT_ROW_INPUT, HINT_COL_INPUT */
#define MAX_ROUNDS 10

/* #TODO - declare as global variables in .C  file ***************************************/
extern int gWaldoColumn;
extern int gWaldoRow;

/* Function Declarations (prototypes) */
/* #TODO - define each function in .C file */

/* If #define DEBUG                                        */
/*  Returns DEBUG_ROW                                      */
/* Else                                                    */
/*  Returns random int in range 1 to MAX_COLS (inclusive). */
int hideWaldoAtColumn();

/* If #define DEBUG                                        */
/*  Returns DEBUG_COL                                      */
/* Else                                                    */
/*  Returns random int in range 1 to MAX_ROWS (inclusive). */
int hideWaldoAtRow();

/* Returns 1 if Waldo is at world[row][column]; otherwise, 0. */
/* Set world[row][column] to:                                 */
/*   W - if Waldo is at row and column                        */
/*   m - if Waldo is not at row and column                    */
int isWaldoAt(char world[][MAX_COLS], int row, int column);

/* Displays world with headings for rows and columns.    */
/* Legend:                                               */
/*          * - initial state; unknown if Waldo is here  */
/*          m - miss... no Waldo                         */
/*          W - it's Waldo                               */
void printWorld(char world[][MAX_COLS]);

/* Sets entire world[*][*] to: * */
void resetWorld(char world[][MAX_COLS]);

#endif /* FIND_WALDO_H_ */
