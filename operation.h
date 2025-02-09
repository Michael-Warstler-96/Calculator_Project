/**
   @file operation.h
   @author Michael Warstler (mwwarstl)
   Header file for defining functions for arithmetic operations addition, subtraction, 
   multiplication, exponential, and division.
*/

/**
   Function adds the given parameters and returns the result. Detects for overflow. If overflow is 
   detected, program terminates with exit status.
   @param a is long integer to add.
   @param b is long integer to add.
   @return is sum of two parameters if overflow is avoided.
*/
long plus(long a, long b);

/**
   Function subtracts the given parameters and returns the result. Detects for overflow. If
   overflow is detected, program terminates with exit status.
   @param a is long integer to subtract.
   @param b is long integer to subtract.
   @return is difference of two parameters if overflow is avoided.
*/
long minus(long a, long b);

/**
   Function multiplies the given parameters and returns the result. Detects for overflow. If 
   overflow is detected, program terminates with exit status.
   @param a is long integer to multiply.
   @param b is long integer to multiply.
   @return is product of two parameters if overflow is avoided.
*/
long times(long a, long b);

/**
   Function exponentiates the parameter (raises a to the power of b, if b is non-negative) and 
   returns the result. Overflow and negative B parameter cause different fail exit statuses.
   @param a is long integer.
   @param b is long integer to be exponent to param a.
   @return is exponential result of two parameters.
*/
long exponential(long a, long b);

/**
   Function divides parameter a by parameter b and returns the result. Detects for one case of 
   overflow. Detects any attempt to divide by zero. Dividing by zero or overflow result in 
   specific fail program termination.
   @param a is long integer.
   @param b is long integer to divide a with.
   @return is quotient of two parameters if overflow and divide by 0 is avoided.
*/
long divide(long a, long b);