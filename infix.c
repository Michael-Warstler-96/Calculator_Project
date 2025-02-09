/**
   @file infix.c
   @author Michael Warstler (mwwarstl)
   Top level component reads in an expression from standard input, evaluates it, and prints restuls
   Depending on executable used (infix_10, infix_32, or infix_n), values are interpreted 
   differently as either base 10, base 32, or base n.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "number.h"
#include "operation.h"

/** Smallest base n allowed */
#define BASE_MIN 2

/** Largest base n allowed */
#define BASE_MAX 32

/**
   Reads the highest precedence parts of an expression, either an individual number or a sequence
   of numbers with an exponential ^ operator between them. Returns the value the factor evaluates
   to. Uses parseValue() function to parse numbers in each factor.
   @return is evaluated expression.
 */
static long parse_exp()
{
    // Get the initial number in the expression.
    long expResult = parseValue();
    int cursor = skipSpace();
    
    // Continue to calculate exponentials until a non ^ is found next. Anything invalid causes termination through parseValue().
    while ( cursor == '^' ) {
        expResult = exponential( expResult, parseValue() );
        cursor = skipSpace();
    }
    // Put latest character back on input stream, and return the result of the expression.
    ungetc ( cursor, stdin );
    return expResult;
}

/**
   Reads the terms in the input expression connected with multiply or divide operators. Calls on
   parse_exp() to parse the factors in the term.
   @return is evaluated expression.
 */
static long parse_mul_div()
{
    // Get initial value from term.
    long result = parse_exp();
    int cursor = skipSpace();
    
    // Continue to calculate product/quotients until hitting a non / or * is found next.
    while ( cursor == '*' || cursor == '/' ) {
        if ( cursor == '*' ) {
            result = times( result, parse_exp() );
        }
        // Else is division
        else {
            result = divide( result, parse_exp() );
        }
        cursor = skipSpace();
    }
    
    // Put latest character back on input stream, and return the result of the expression.
    ungetc ( cursor, stdin );
    return result;
}

/**
   Main function handles outer level math functions (addition and subtraction). For inner level, 
   higher precedence, the function passes responsibility to parse_mul_div() and parse_exp(). 
   For base n programs, function reads in an n value and calculates expression based on that.
   @param argc are command line arguments.
   @param **argv is array of character pointers listing all arguments.
   @return is exit status
*/
int main(int argc, char **argv)
{
  // If using infix_n program, scan for user input to determine what base n should be. Error check.
  if (strcmp(argv[0], "./infix_n") == 0) {
      // User enters a value to set base as (Only 2-31 are valid)
      // Check if correct tokens entered.
      char dollarSign;
      if ( scanf("%c%d", &dollarSign, &BASE) != 2 ) {
          return EXIT_FAILURE;
      }
      // Check for $ sign entered first
      if ( dollarSign != '$' ) {
          return EXIT_FAILURE;
      }
      // Check for valid base 
      if ( BASE < BASE_MIN || BASE > BASE_MAX ) {
          return EXIT_FAILURE;
      }          
  }
  // Get initial value from expression
  long finalResult = parse_mul_div();
  int cursor = skipSpace(); // reads value from last unget.
  
  // Continue until \n or EOF is detected.
  while ( cursor != '\n' && cursor != EOF ) {
      // Check for addition
      if ( cursor == '+' ) {
          finalResult = plus( finalResult, parse_mul_div() );
      }
      // Else is subtraction
      else {
          finalResult = minus( finalResult, parse_mul_div() );
      }
      cursor = skipSpace();
  }
  
  // Newline or EOF reached, print final result.
  printValue( finalResult );
  printf( "\n" );
  return EXIT_SUCCESS;
}
