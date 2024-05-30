/**
@file vigesimal
@author Ethan Browne, efbrowne
This file is the header for vigesmal.h which reads and prints in base 20.
 */

// The prototypes need the bool and FILE types.
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
Reads characters inside file until it finds a non whitespace character
@param input the file that we are skipping whitespaces in
@return the code for the first non-whitespace character it finds including EOF
*/
int skipWhitespace( FILE *input );

/**
Reads the next number from the given file in base 20
@param val the value it reads in
@param input the input file
@return whether it detects errors in the input number
*/
bool parseNumber( long *val, FILE *input );

/**
Prints the value to a given file in base 20
@param val the value it prints
@param output the output file
*/
void printNumber( long val, FILE *output );
