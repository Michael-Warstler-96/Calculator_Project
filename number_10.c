/**
   @file number_10.c 
   @author Michael Warstler (mwwarstl)
   Component reads numeric values from input and writes results to output. This implementation
   has numbers written in base 10.
*/

#include "number.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"

/** ASCII number for space (whitespace) */
#define SPACE 32

/** Value of the base */
int BASE = 10;

// Read input until non-whitespace or newline.
int skipSpace()
{
   int c = getchar();
   // Loop until non whitespace is found.
   while ( c != '\n' && c <= SPACE ) {
       c = getchar();
   }
   return c;
}

// Read input in base 10.
long parseValue()
{
    // Values parsed so far.
    long value = 0;
    
    // Get next input character
    int ch = skipSpace();
    
    // Check if character was negative
    bool negative = false;
    if ( ch == '-' ) {
        negative = true;
        ch = getchar(); // get immediate next character.
    }
    
    // Check if the current parsed value is valid character for base 10 (0-9).
    if ( ch < '0' || ch > '9' ) {
        exit( FAIL_INPUT);
    }
    
    // Keep reading while character is digit in base 10
    while ( ch >= '0' && ch <= '9' ) {
        // Convert Character to a digit
        int digit = ch - '0';
        
        // Slide all digits read so far one place value to the left. (value = value * 10).
        value = times( value, BASE );
        
        // If number is negative, values must be subtracted, otherwise they are added.
        value = negative ? minus( value, digit ) : plus( value, digit );
        
        // Get next input character.
        ch = skipSpace();
    }
    
    // Check if last read non-digit character is allowed for program.
    if ( ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '\n' ) {
        exit( FAIL_INPUT );
    }
    // No issue with last read non-digit character. Unget - send back to input.
    else {
        ungetc ( ch, stdin );
        return value;
    }
}

// Print value in base 10.
void printValue(long val)
{
    printf( "%ld", val );
}
