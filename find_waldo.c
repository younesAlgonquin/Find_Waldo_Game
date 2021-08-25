/**************************************************************************
Assignment number (and name if any): Lab 03: Find Waldo Game 
                                                      
Course name and number: CST8234 C Language
Lab section number: 013
Due date of assignment: June 18, 2021
Submission date of assignment: June 15, 2021
List of source and header files in the project: find_waldo.c , find_waldo.h
***************************************************************************/
/**************************************************************************
Declare include files
***************************************************************************/
#include "find_waldo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**************************************************************************
 Declare global vriables
***************************************************************************/
/*This is the actual waldo column*/
int gWaldoColumn;
/*This is the actual waldo row*/
int gWaldoRow;

/**************************************************************************
 * Main function
 * The Find Waldo game challenges the User to find Waldo (‘W’), 
 * who is hiding within a 2-dimensional world (10 x 10). 
 * The game begins with prompting the User to enter the number of rounds 
 * they need to find Waldo then print the result to the screen
 * It takes no parameters and returns EXIT_SUCCESS or EXIT_FAILURE values
 * 
 * Version: 1.0
 * Author/Student Name: Younes Boutaleb
 **************************************************************************/
int main()
{

  /**************************************************************************
   Declare local vriables
  **************************************************************************/
  /*2-dimensional that contains Waldo*/
  char world[MAX_ROWS][MAX_COLS];
  /*this is the return code of the user input*/
  int rc = 0;
  /*Maximum number of rounds the User thinks they need to find Waldo*/
  int rounds = 0;
  /*User's guess for column number*/
  int column;
  /*User's guess for row number*/
  int row;
  /*this is the first remaining charachter in stdin after scanf is executed*/
  char nextChar;
  /*for loop variable*/
  int i;
  /*The game result (won:1 ; lost:0)*/
  int result;

  /**************************************************************************
  Assign a '*' to all world cells and define the Waldo position
  **************************************************************************/
  /*This method will generate random integers for Waldo column and row*/
  srand(time(NULL));
  /*Reset all world cells to '*' charachter */
  resetWorld(world);
  /*Assign Waldo column to gWaldoRow variable*/
  gWaldoRow = hideWaldoAtRow();
  /*Assign Waldo row to gWaldoRow variable*/
  gWaldoColumn = hideWaldoAtColumn();

  /**************************************************************************
   Prompt user for number of rounds and validate the input
  **************************************************************************/
  /*Loop until the user enters a valid input or exits the game*/
  while (rc != 1)
  {
    printf("Enter the number of rounds you need to find Waldo(0 to quit, 10 max): ");
    /*it takes 1 if scanf reads an integer*/
    rc = scanf(" %d", &rounds);
    /*Read the next charachter in stdin after scanf is executed*/
    nextChar = getchar();

    /*Checks for clrt-d input which stands for the end of input EOF
      Exits the game with failure if the user enters the EOF charachter*/
    if (nextChar == -1)
    {
      puts("\n"); 
      return EXIT_FAILURE;
    } /*end if*/

    /*Prints an error message if the user enters an invalid input (strings/float)
    and goes back to the while loop*/
    else if (rc != 1 || nextChar != '\n')
    {
      rc = 0;
      printf("Error - enter number of rounds between 1 and 10\n");

      /*if not a valid input clear the stdin*/
      while (getchar() != '\n')
      {
        /*chomp stdin*/
      } /*end while*/
    }   /*end else if*/

    /*Prints an error message if the user enters an invalid integer
    and goes back to the while loop*/
    else if (rounds > 10 || rounds < 0)
    {
      rc = 0;
      printf("Error - enter number of rounds between 1 and 10\n");
    } /*end else if*/

    /*Prints an error message and exits the game with failure if the user enters 0 */
    else if (rounds == 0)
    {
      /* puts("\nYou ended the game.\n"); */
      return EXIT_FAILURE;
    } /*end else if*/
  }   /*end while*/

  /**************************************************************************
   Prints the reset Waldo world
  **************************************************************************/
  printWorld(world);

  /**************************************************************************
   Prompt user for Waldo column & row and validates the input
   Then it displays the guess result
   It continues until the user wins the game or exceeds max number of rounds
  **************************************************************************/
  for (i = 1; i <= rounds; i++)
  {
    /*overwrite and nitialize the return code value*/
    rc = 0;
    /*Loop until the user enters a valid input or exits the game*/
    while (rc != 2)
    {
      printf("Round %d of %d. Enter row and column (control-d to quit): ", i, rounds);

      /*it takes 1 if scanf reads an integer for row*/
      rc = scanf(" %d", &row);
      /*Read the next charachter in stdin after scanf is executed*/
      nextChar = getchar();

      /*Reads the column number if the entered a valid row number (integer + space)*/
      if (rc == 1 && nextChar == ' ')
      {
        /*it takes 2 if scanf reads an integer for column*/
        rc += scanf(" %d", &column);
        /*Read the next charachter in stdin after scanf is executed*/
        nextChar = getchar();
      } /*end if*/

      /*Checks for clrt-d input which stands for the end of input EOF
      Exits with faillure if the user enters the EOF charachter
     */
      if (nextChar == -1)
      {
        puts("\n");
        return EXIT_FAILURE;
      } /*end if*/

      /*Prints an error message if the user enters an invalid input (strings/float)
    and goes back to the while loop*/
      else if (rc != 2 || nextChar != '\n')
      {
        rc = 0;
        printf("Error - enter a row (int) and column (int).\n\n");

        /*if not a valid input clear the stdin*/
        if(nextChar != '\n')
        {
        while (getchar() != '\n')
        {
          /*chomp stdin*/

        } /*end while*/
        }
      }   /*end else if*/

      /*Displays the waldo position id the user enters -1 -1 and loops back */
      else if (row == HINT_ROW_INPUT && column == HINT_COL_INPUT)
      {
        rc = 0;
        printf("Hint: %d %d\n\n", gWaldoRow, gWaldoColumn);
      } /*end else if*/

      /*Prints an error message if the user enters an invalid integer
        and goes back to the while loop*/
      else if ((row > 10 || row < 1) || (column > 10 || column < 1))
      {
        rc = 0;
        printf("Error - row and column must be in the range 1 to 10\n\n");

      } /*end else if*/
    }   /*end while*/

    /**************************************************************************
     Deternmines the guess result and print it in the waldo world
    **************************************************************************/
    /*This is the guess result*/
    result = isWaldoAt(world, row, column);
    /*print the new Waldo world*/
    printWorld(world);

    /*Ends the game if the user wins*/
    if (result)
    {
      puts("Huzzah... you found Waldo!");
      return EXIT_SUCCESS;
    } /*end if*/
    /*Goes back to the foor loop if the user miss it*/
    else
      puts("Miss!");

  } /*end for*/

  /*Exits the game with failure if the user exceeds the max number of rounds*/
  return EXIT_FAILURE;

} /*end main*/

/**************************************************************************
Method to define waldo column number
  **************************************************************************/
int hideWaldoAtColumn()
{
  /*Sets Waldo column to DEBUG_COL*/
  #ifdef DEBUG
    return DEBUG_COL;

  /*Sets Waldo column to a random integer between 1 and 10*/
  #else
    /*random column in range 1 to MAX_COLS (inclusive) */
    return (int)((rand() % 10) + 1);
  #endif
} /*end hideWaldoAtColumn*/

/**************************************************************************
Method to define waldo row number
**************************************************************************/
int hideWaldoAtRow()
{
  /*Sets Waldo row to DEBUG_ROW*/
  #ifdef DEBUG
    return DEBUG_ROW;
  /*Sets Waldo row to a random integer between 1 and 10*/
  #else
    /*random row in range 1 to MAX_ROWS (inclusive) */
    return (int)((rand() % 10) + 1);
  #endif
} /*end hideWaldoAtRow*/

/**************************************************************************
Method to determin the Guess result and store it in the world array
**************************************************************************/
int isWaldoAt(char world[][MAX_COLS], int row, int column)
{
  /*If the guess is true return 1 and assign 'W' to the corresponding cell*/
  if (row == gWaldoRow && column == gWaldoColumn)
  {
    world[row - 1][column - 1] = 'W';
    return 1;
  } /*end if*/

  /*If the guess is false return 0 and assign 'm' to the corresponding cell*/
  else
  {
    world[row - 1][column - 1] = 'm';
    return 0;
  } /*end else*/
}

/**************************************************************************
Method to dprint the waldo world array to the screen
**************************************************************************/
void printWorld(char world[][MAX_COLS])
{
  /*Column number */
  int c;
  /*Row number */
  int r;

  /*display column heading */
  printf("   ");
  for (c = 0; c < MAX_COLS; c++)
  {
    printf(" %d ", c + 1);
  } /*end for */

  /*Goes to a new line */
  printf("\n");

  /*display the array content */
  for (r = 0; r < MAX_ROWS; r++)
  {
    /*display row heading */
    printf("%2d ", (r + 1));
    /*display the values of each row of the array */
    for (c = 0; c < MAX_COLS; c++)
    {
      printf(" %c ", world[r][c]);
    } /*end inner for */

    /*Goes to a new line */
    printf("\n");
  } /*end outer for */
} /*end printWorld */

/**************************************************************************
Method to reset world cells to '*' charachter
**************************************************************************/
void resetWorld(char world[][MAX_COLS])
{
  /*Column number */
  int c;
  /*Row number */
  int r;

  for (r = 0; r < MAX_ROWS; r++)
  {
    for (c = 0; c < MAX_COLS; c++)
    {
      world[r][c] = '*';
    } /*end inner for */
  }   /*end outer for */
} /*end resetWorld */
