/**
@file check
@author Ethan Browne, efbrowne
The purpose of this file is to add, subtract, multiply, and devide different numbers together
 */

#include "check.h"
#include <limits.h>

/**
Adds two longs together and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool add( long *result, long a, long b )
{
    long total = a + b;
    if (a > 0 && b > 0 && total < 0) {
        return false;
    } else if (a < 0 && b < 0 && total > 0){
        return false;
    }
    *result = total;
    return true;
}

/**
Subtracts two longs and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool subtract( long *result, long a, long b )
{
    long total = a - b;
    if (a > 0 && b < 0 && total < 0) {
        return false;
    } else if (a < 0 && b > 0 && total > 0){
        return false;
    }
    *result = total;
    return true;
}

/**
Multiplies two longs together and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool multiply( long *result, long a, long b )
{
    long total = a * b;
    if (a > 0 && b > 0 && total < 0) {
        return false;
    } else if (a < 0 && b < 0 && total < 0){
        return false;
    } else if (a > 0 && b < 0 && total > 0){
        return false;
    } else if (a < 0 && b > 0 && total > 0){
        return false;
    }
    *result = total;
    return true;
}

/**
Devides two longs and stores value in pointer. Checks to see if an overflow occured.
@param result the pointer to the result of the calculation
@param a the first long in calculation
@param b the second long in calculation
@return if the calculation would result in an overflow
*/
bool divide( long *result, long a, long b )
{
    if (b == 0) {
        return false;
    }
    long total = a / b;
    if (a > 0 && b > 0 && total < 0) {
        return false;
    } else if (a < 0 && b < 0 && total < 0){
        return false;
    }
    *result = total;
    return true;
}