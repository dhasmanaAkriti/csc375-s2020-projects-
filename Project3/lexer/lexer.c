/* Starter code provided to students */

/* The lexical analyzer for the C-- Programming Language
 */
// TODO: you are welcome to completely wipe out the contents of this
// file and start from scratch, or use this as your starting point.

#include <stdlib.h>
#include <assert.h>
#include "lexer.h"


// these are likely values that will be needed by the parser, so 
// making them global variables is okay
char lexbuf[MAXLEXSIZE];  // stores current lexeme
int  tokenval=0;          // stores current token's value
                          // (might not be used for every token)
int  src_lineno=0;        // current line number in source code input

// function prototypes:
static void print_lineno();  // static limits its scope to only in this .c file

/***************************************************************************/
/* 
 *  Main lexer routine:  returns the next token in the input 
 *
 *  param fd: file pointer for reading input file (source C-- program)
 *            TODO: you may want to add more parameters
 *
 *  returns: the next token, or 
 *           DONE if there are no more tokens, or
 *           LEXERROR if there is a token parsing error 
 */
int lexan(FILE *fd) {

  // here is an example of how to use the debug macros defined in lexer.h
  //   uncomment #define DEBUG_LEXER, and recompile to see debug output 
  //   comment #define DEBUG_LEXER, and recompile to see debug output 
  //
  lexer_debug0("in lexan\n");
  lexer_debug1("in lexan, lineno = %d\n", src_lineno);
  lexer_debug1("in lexan, message = %s\n", "hello there");

  // bogus code:
  if(src_lineno < 5) {
    src_lineno++;
    return IF;
  }
  print_lineno();
  return DONE;
}
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
static void print_lineno() {
  
  printf("line no = %d\n", src_lineno);

}


