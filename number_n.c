/**
   @file number_n.c 
   @author Michael Warstler (mwwarstl)
   Component reads numeric values from input and writes results to output. This implementation
   has numbers written in base n. N being decided by the user from value 1-32.
*/

#include "number.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "operation.h"

/** ASCII number for space (whitespace) */
#define SPACE 32

/** Base defined by user in infix.c's main(). */
int BASE;

// Read input until non-whitespace or newline.
int skipSpace()
{
    int c = getchar();
    // Loop until non whitespace or newline is found.
    while ( c != '\n' && c <= SPACE ) {
    c = getchar();
    }
    return c;
}

// Read input in base n as decided by the user.
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
    
    // Check if the current parsed value is valid character for current base n.     
    // charMax represents max of range of base n. Anything higher than base 10 requires
    // additional + 7 to skip past ASCII values 58-64. N - 1 since bases since lowest digit is 0.
    char charMax = BASE <= 10 ? '0' + BASE - 1 : '0' + BASE - 1 + 7;
    if ( ch > charMax || ch < '0' || (ch > '9' && ch < 'A') || ch > 'V' ) {
        exit( FAIL_INPUT );
    }
    
    // Keep reading while character is digit in base n: from 0 to charMax (n-1), and NOT ASCII 58-64.
    while ( (ch >= '0' && ch <= charMax) && !(ch > '9' && ch < 'A')) {
        // Convert 0-9 char to digit. If A-V, need minus 7 to account for characters between ASCII 9 and A.
        int digit = ch <= '9' ? ch - '0' : ch - '0' - 7;
    
        // Slide all digits read so far one place value to the left. (value = value * n).
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
    }
    
    return value;  
}

// Print output in base n.
void printValue(long val)
{
    // Check if value is negative
    bool negative = val < 0 ? true : false;    
    
    // Get the next digit on the right.
    int digit = val % BASE;
    // Convert digit to char base n (0 through n-1, excluding ASCII junk between '9' and 'A'. Must 
    // add 7 to clear junk characters if base is greater than 10.
    // Change negative digit to positive first
    if ( digit < 0 ) {
        digit = times( digit, -1 );
    }
    char ch = digit <= 9 ? digit + '0' : digit + '0' + 7;
    
    // Slide remaining digits to the right
    val = divide( val, BASE );
    
    // Recursively call function to get higher order digits if val is not 0 yet.
    if ( val != 0 ) {
        printValue( val );
    }
    // Only want to print negative once - must be on last iteration only.
    else {
        if ( negative ) {
            printf( "-" );
        }
    }
    
    // Recursion is finished. Print base n character for current iteration. Else block above is
    // skipped except for last iteration.
    printf( "%c", ch );
}
