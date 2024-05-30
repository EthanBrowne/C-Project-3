/**
@file vigesimal
@author Ethan Browne, efbrowne
Reads and prints in base 20. Also contains function that skips whitespace.
 */

#include "vigesimal.h"
#include "check.h"

/** Base of the number system we're implementing. */
#define BASE 20

/** Maximum number of characters needed to print the largest number. */
#define MAX_NUMBER_LEN 16

/** The ASCII value that A starts at*/
#define A_START 65

/**
Reads characters inside file until it finds a non whitespace character
@param input the file that we are skipping whitespaces in
@return the code for the first non-whitespace character it finds including EOF
*/
int skipWhitespace( FILE *input )
{
    int c = fgetc(input);
    while (c == ' ' || c == '\n'){
        c = fgetc(input);
    }
    return c;
}

/**
Reads the next number from the given file in base 20
@param val the value it reads in
@param input the input file
@return whether it detects errors in the input number
*/
bool parseNumber( long *val, FILE *input )
{
    // Value we've parsed so far.
    *val = 0;
    // Get the next input character.
    int ch = skipWhitespace(input);
    /** If the number is negative*/
    if (ch == '-'){
        ch = skipWhitespace(input);
        while ( ch >= 'A' && ch <= 'T') {
            // Convert from ASCII code for the next digit into the value
            // of that digit.  For example 'A' -> 0 or 'H' -> 7
            int d = ch - A_START;
            // Slide all digits we've read so far one place value to the
            // left.
            if (!multiply(val, *val, BASE)){
                /** If overflow go to end of line and return false*/
                while (ch != ';' && ch != EOF) {
                    ch = skipWhitespace(input);
                }
                return false;
            }
            // Subtracts this digit as a new, low-order digit.
            if (!subtract(val, *val, d)){
                /** If overflow go to end of line and return false*/
                while (ch != ';' && ch != EOF) {
                    ch = skipWhitespace(input);
                }
                return false;
            }
            // Get the next input character.
            ch = fgetc(input);
        }
        // ch was one character past the end of the number.  Put it back on
        // the input stream so it's there for other code to parse.
        ungetc(ch, input);
        return true;
    } else {
        /** If the number is positive */
        while ( ch >= 'A' && ch <= 'T') {
            // Convert from ASCII code for the next digit into the value
            // of that digit.  For example 'A' -> 0 or 'H' -> 7
            int d = ch - A_START;
            // Slide all digits we've read so far one place value to the
            // left.
            if (!multiply(val, *val, BASE)){
                while (ch != ';' && ch != EOF) {
                    ch = skipWhitespace(input);
                }
                return false;
            }
            // Add this digit as a new, low-order digit.
            if (!add(val, *val, d)){
                while (ch != ';' && ch != EOF) {
                    ch = skipWhitespace(input);
                }
                return false;
            }
            // Get the next input character.
            ch = fgetc(input);
        }
        // ch was one character past the end of the number.  Put it back on
        // the input stream so it's there for other code to parse.
        ungetc(ch, input);
        return true;
    }
}



/**
Prints the value to a given file in base 20
@param val the value it prints
@param output the output file
*/
void printNumber( long val, FILE *output )
{
    if (val == LONG_MIN) {
        // Handle the special case of the minimum long value
        if (output == NULL) {
            printf("-FMLPTSKDPRCGTKI");
            val = 0;
        } else {
            fprintf(output, "-FMLPTSKDPRCGTKI");
            val = 0;
        }
    /** If the val is negative print - character and make positive*/
    }else if (val < 0 && output == NULL){
        printf("-");
        val *= -1;
    } else if (val < 0) {
        fprintf(output, "-");
        val *= -1;
    } else if (val == 0){
        if (output == NULL){
            printf("A");
        } else {
            fprintf(output, "A");
        }
    }
    char str[MAX_NUMBER_LEN + 1] = {};
    // Store characters starting from index 0.
    int idx = 0;
    // While there are more digits to print.
    while ( val != 0) {
        // Get the next digit on the right.
        int d = val % BASE;
        // Convert it to a character, e.g, 9 -> 'J' or 17 -> 'H'
        int ch = d + A_START;
        // Store the next digit in a string.
        str[ idx++ ] = ch;
        // Slide remaining digits to the right.
        divide(&val, val, BASE);
    }
    // Put a null terminator at the end.
    str[ idx ] = '\0';
    if (output == NULL){
        for (int i = idx - 1; i >= 0; i--){
            printf("%c", str[i]);
        }
        printf("\n");
    } else {
        for (int i = idx - 1; i >= 0; i--){
            fprintf(output, "%c", str[i]);
        }
        fprintf(output,"\n");
    }
}