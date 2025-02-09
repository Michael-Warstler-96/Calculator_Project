/**
   @file operation.c 
   @author Michael Warstler (mwwarstl)
   Component implements 5 functions for arithmetic on signed long values. Each automatically 
   detects overflow or divide by 0.
*/

#include "operation.h"
#include <stdlib.h>
#include <limits.h>

/** Exit status for when an overflow occurs. */
#define FAIL_OVERFLOW 100

/** Exit status for when we try to divide by zero. */
#define FAIL_DIVZERO 101

/** Exit status for when negative exponent. */
#define FAIL_NEGEXP 103

// Adds 2 parameters.
long plus(long a, long b)
{
    // Check for overflow first
    // 2 positives added should not equal negative
    if ( a > 0 && b > 0 && a + b < 0 ) {
        exit( FAIL_OVERFLOW );   
    }
    // 2 negatives added should not equal positive
    else if ( a < 0 && b < 0 && a + b > 0 ) {
        exit( FAIL_OVERFLOW );
    }
    // Add parameters together
    else {
        return a + b;
    }
}

// Subtracts b from a.
long minus(long a, long b)
{
    // Check for overflow first
    // A positive minus a negative cannot result in negative.
    if ( a > 0 && b < 0 && a - b < 0 ) {
        exit( FAIL_OVERFLOW );
    }
    // A negative minus a postive cannot result in positive.
    else if ( a < 0 && b > 0 && a - b > 0 ) {
        exit( FAIL_OVERFLOW );
    }
    else {
        return a - b;
    }
}

// Multiplies 2 parameters.
long times(long a, long b)
{
    // Value to check largest/smallest allowed to prevent overflow.
    long x;
    
    // Check overflow for both params positive.
    if ( a > 0 && b > 0 ) {
        x = LONG_MAX / b;   // x is the largest value possible for a to be to prevent overflow.
        if ( a > x ) {
            exit( FAIL_OVERFLOW );
        }
    }
    // Check overflow for param a is positive and param b is negative
    else if ( a > 0 && b < 0 ) {
        x = LONG_MIN / a;
        if ( b < x ) {
            exit( FAIL_OVERFLOW );
        }
    }
    // Check overflow for param a is negative and param b is positive
    else if ( a < 0 && b > 0 ) {
        x = LONG_MIN / b;
        if ( a < x ) {
            exit( FAIL_OVERFLOW );
        }
    }
    // Check overflow for both params negative.
    else if ( a < 0 && b < 0 ) {
        x = LONG_MAX / b;
        if ( a < x ) {
            exit( FAIL_OVERFLOW );
        }
    }
    // No overflow detected, return product.
    return a * b;
}

// Exponentiates parameter a by parameter b.
long exponential(long a, long b)
{
    // Check for negative exponent
    if ( b < 0 ) {
        exit( FAIL_NEGEXP );
    }
    // Special case of 0 exponent
    else if ( b == 0 ) {
        return 1;
    }
    else {
        // Loop to repeatedly multiply
        long initialValue = a;
        while ( b > 1 ) {
            a = times( a, initialValue );
            b--;
        }
        return a;
    }
}

// Divides parameter a by parameter b.
long divide(long a, long b)
{
    // Check for divide by 0.
    if ( b == 0 ) {
        exit( FAIL_DIVZERO );
    }
    // Check for special case overflow for long
    else if ( a == LONG_MIN && b == -1 ) {
        exit( FAIL_OVERFLOW );
    }
    // otherwise divide 
    else {
        return a / b;
    }
}
