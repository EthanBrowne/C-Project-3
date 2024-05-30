/**
@file vcalc
@author Ethan Browne, efbrowne
This file reads statements from an input file, and prints results either to standard output or to an output file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "vigesimal.h"
#include "check.h"

/** Requried input-file argument. */
#define INPUT_ARG 1

/** Optional, output-file argument. */
#define OUTPUT_ARG 2

/** The ASCII value that a starts at*/
#define LOWER_A_START 97

/** The length of the aphabet*/
#define ALPHABET_LENGTH 26

/** The list of all of the variables */
long variableArrayValues[ALPHABET_LENGTH] = {};

/** When the numbner of files is too few or too many */
static void usage()
{
  fprintf( stderr, "usage: vcalc INPUT-FILE [OUTPUT-FILE]\n" );
  exit( EXIT_FAILURE );
}

/**
Reads the next operand from the input file.
Store the value in val. If it is a variable it stores name in vname.
If it is neither sets the char to null terminator.
@param val the value of the operand
@param vname the name of the variable
@param input the file that is being read
@return false if the input doesn't contain valid operand and true if it does.
*/
bool parseOperand( long *val, char *vname, FILE *input )
{
  /** Checks if the variable is negative*/
  int ch = skipWhitespace(input);
  if (ch == '-') {
    /** Checks to see if it is a value or variable*/
    int nextChar = skipWhitespace(input);
    if (nextChar >= 'a' && nextChar <= 'z') {
      /** Sets vname to the variable name and val to the negative value of the variable*/
      *vname = nextChar;
      *val = -1 * variableArrayValues[nextChar - LOWER_A_START];
      return true;
    } else if (nextChar >= 'A' && nextChar <= 'T') {
      /** Sets vname to null terminator. Ungets both chars and computes the value*/
      *vname = '\0';
      ungetc(nextChar, input);
      ungetc(ch, input);  
      return parseNumber(val, input);
    }
  /** Checks to see if it is a value or variable*/
  } else if (ch >= 'a' && ch <= 'z') {
    /** Sets vname to the variable name and val to the value of the variable*/
    *vname = ch;
    *val = variableArrayValues[ch - LOWER_A_START];
    return true;
  } else if (ch >= 'A' && ch <= 'T'){
    /** Sets vname to null terminator. Ungets char and computes the value*/
    *vname = '\0';
    ungetc(ch, input);
    return parseNumber(val, input);
  }
  /** If its not a value go to the next line or EOF*/
  while (ch != ';' && ch != EOF) {
    ch = skipWhitespace(input);
  }
  return false;
}

/**
Reads an expression as a sequence of operands separated by the ‘+’, ‘-’, ’*’ and ‘/’ operators.
It computes the result of the whole expression and stores it in result.
@param result the value of the expression
@param left the value passed in
@param input the file that is being read
@return whether the expression is valid.
*/
bool parseExpression( long *result, long left, FILE *input )
{
  /** Checks to see if there are more than one equals in a line */
  static int equalsCount = 0;
  /** The value to the right of the operand */
  long right = 0;
  /** The operator */
  char operator = skipWhitespace(input);
  char nothing = '\0';
  if (operator != ';' && operator != EOF){
    /** Runs the parse operator function */
    if (!parseOperand(&right, &nothing, input)){
        return false;
    }
    /** If its equal set the result equal to the right */
    if (operator == '='){
      equalsCount++;
      if (equalsCount > 1){
        while (operator != ';') {
          operator = skipWhitespace(input);
        }
        return false;
      }
      *result = right;
    /** If its add set the result equal to addition of the left and the right */
    } else if (operator == '+'){
      if (!add(result, left, right)){
        while (operator != ';') {
          operator = skipWhitespace(input);
        }
        return false;
      }
    /** If its subtraction set the result equal to subtraction of the left and the right */
    } else if (operator == '-'){
      if (!subtract(result, left, right)){
        while (operator != ';') {
          operator = skipWhitespace(input);
        }
        return false;
      }
    /** If its multiplication set the result equal to multiplication of the left and the right */
    } else if (operator == '*'){
      if (!multiply(result, left, right)){
        while (operator != ';') {
          operator = skipWhitespace(input);
        }
        return false;
      }
    /** If its devide set the result equal to devide of the left and the right */
    } else if (operator == '/'){
      if (!divide(result, left, right)){
        while (operator != ';') {
          operator = skipWhitespace(input);
        }
        return false;
      }
    }
    /** If it is none of the operators go to the next line */
    if (operator != '+' && operator != '-' && operator != '*' && operator != '/' && operator != '=') {
      while (operator != ';') {
        operator = skipWhitespace(input);
      }
      return false;
    }
    /** Call the function again */
    return parseExpression(result, *result, input);
  }
  /** Resets the equal count */
  equalsCount = 0;
  if (operator == EOF){
    return false;
  }
  return true;
}

/**
Reads the next statement from the input stream.
If it’s an expression, it reports its value to the given output stream using the given stmt number as the statement number.
@param stmtNum
@param input the file that is being read
@param output the file that is being written in
@return whether the statement is valid.
*/
bool parseStatement( int stmtNum, FILE *input, FILE *output )
{
  /** Checks for EOF */
  int maybeEOF = skipWhitespace(input);
  if (maybeEOF == EOF) {
    return false;
  }
  ungetc(maybeEOF, input);
  /** Checks if it is an equals */
  int possibleEquals = '\0';
  char name;
  long total = 0;
  /** Gets the first operand*/
  if (!parseOperand(&total, &name, input)) {
    /** Prints invalid if invalid operand */
    if (output == NULL){
      printf("S%d: invalid\n", stmtNum);
    } else {
      fprintf(output, "S%d: invalid\n", stmtNum);
    }
    return true;
  }
  /** If the name is not null and check to see if there is an equals*/
  if (name != '\0'){
    possibleEquals = skipWhitespace(input);
    ungetc(possibleEquals, input);
  }
  /** Get the values after the the first operand*/
  if (!parseExpression(&total, total, input)) {
    /** Prints invalid if invalid expression */
    if (output == NULL){
      printf("S%d: invalid\n", stmtNum);
    } else {
      fprintf(output, "S%d: invalid\n", stmtNum);
    }
    return true;
  }
  /** If there was an equals set the array value to the total*/
  if (possibleEquals == '='){
    variableArrayValues[(int) (name - LOWER_A_START)] = total;
  } else {
    /** Print out the total if not an eqauls*/
    if (output == NULL){
      printf("S%d: ", stmtNum);
    } else {
      fprintf(output, "S%d: ", stmtNum);
    }
    printNumber(total, output);
  }
  return true;
}

/**
Main method. Runs all of the functions together.
return whether program was successful
*/
int main( int argc, char *argv[])
{
  /** If too many or to feq arguments exit*/
  if (argc > OUTPUT_ARG + INPUT_ARG || argc < OUTPUT_ARG) {
    usage();
  }
  /** Opens the file*/
  FILE *input = fopen(argv[INPUT_ARG], "r");
  /** If there is no file exit*/
  if (input == NULL) {
    fprintf(stderr, "Can't open file: %s\n", argv[INPUT_ARG]);
    return EXIT_FAILURE;
  }
  FILE *output = NULL;
  bool closeOutput = false;
  /** Opens the output file*/
  if (argc > OUTPUT_ARG) {
    output = fopen(argv[OUTPUT_ARG], "w");
    closeOutput = true;
    /** If there is no file exit*/
    if (output == NULL) {
      fprintf(stderr, "Can't open file: %s\n", argv[OUTPUT_ARG]);
      fclose(input);
      return EXIT_FAILURE;
    }
  }
  int statementNum = 1;
  /** Repeat until it parses all statements*/
  bool nextLine = parseStatement(statementNum, input, output);
  while (nextLine) {
    statementNum++;
    nextLine = parseStatement(statementNum, input, output);
  }
  /** Closes the files*/
  fclose(input);
  if (closeOutput){
    fclose(output);
  }
  return EXIT_SUCCESS;
}