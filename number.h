/**
   @file number.h
   @author Michael Warstler (mwwarstl)
   Header file for defining functions for reading numerical expressions from input.
*/

/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102

/** Global variable mainly used for user input base n (infix_n) program. */
extern int BASE;

/**
   Reads characters from standard input until it reaches non-whitespace character or EOF. Returns
   the code for the first non-whitespace character it finds (or EOF or \n if found)
   @return is numeric code for non-whitespace character read in or EOF if that is reached.
*/
int skipSpace();

/**
   Reads next number from input. Reads in base 10 for number_10.c, base 32 for number_32.c, and
   base n for number_n.c. If errors are detected with the input number, the program is terminated
   with FAIL_INPUT exit status.
   @return is a valid number read from input.
*/
long parseValue();

/**
   Prints the given value to standard output. Printed in base 10 for number_10.c, base 32 for 
   number_32.c, and base n for number_n.c.
   @param val is value to be printed.
*/
void printValue(long val);