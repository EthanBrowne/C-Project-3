/**
@file check
@author Ethan Browne, efbrowne
This is the header file for check.c which adds, subtracts, multiplys, and devides different numbers together
 */

// The function prototypes need the bool type.
#include <stdbool.h>

/**
Adds two longs together and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool add( long *result, long a, long b );

/**
Subtracts two longs and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool subtract( long *result, long a, long b );

/**
Multiplies two longs together and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool multiply( long *result, long a, long b );

/**
Devides two longs and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool divide( long *result, long a, long b );
