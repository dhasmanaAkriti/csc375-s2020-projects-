/****** parser.h ********************************************************/
// this should contain definitions that are defined by the parser and
// that are shared across files and modules
//
#ifndef _PARSER_H_
#define _PARSER_H_


// TODO: you may remove everything that is in here if you'd like; the contents
//       are just to give you an example of some of the types of things
//       that may appear in this file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast.h"


// a special value for the token field of an AST node to signify that
// this AST node corresponds to syntax that is not represented by a terminal
// in the grammar
#define NONTERMINAL   400       // set to 400 so that it does not conflict
                                // with a valid token value that is defined
                                // as an enum type in lexer.h
                                // (it would be better to add this to the
                                // enum def, but is separated out since
                                // it's appearing for the first time in part2
                                // of the project

// symbols for AST nodes corresponding to non-terminals
// ... add more, or feel free to change these completely
// also, you could use an enum type here instead of #defines
//
#define START_AST_SYM 400
#define ROOT          401
#define PROGRAM       402
#define FUNDECLIST    403
#define VARDECLIST    404
#define FUNDEC        405
#define FUNDECLISTHELPER   406
#define PARAMDECLIST   407
#define PARAMDEC1     408
#define  BLOCK        409
#define  STMTLIST     410
#define  STMT         411
#define  PRIMARY       412
#define  EXPR          413
#define  EXPRLIST      414
#define  VARDECLISTHELPER  415
#define  VARDEC  416
#define  EXPRFOLLOW  417
#define  FUNC  418
#define  K_ 419
#define END_AST_SYM    420


// add global variable definitions:
extern ast ast_tree;        // the abstract syntax tree

// add any function prototypes that are shared across files:
extern void parse(FILE *fd);

// uncomment DEBUG_PARSER #define to enable debug output
#define DEBUG_PARSER     1
#ifdef DEBUG_PARSER  // DEBUG_PARSER on:
#define parser_debug0(str)            printf(str)           // 1 string arg
#define parser_debug1(fmtstr, arg1)   printf(fmtstr,arg1)   // format str & arg
#define parser_debug2(fmtstr, arg1, arg2)  printf(fmtstr, arg1, arg2)
#else  // DEBUG_LEXER off:
#define parser_debug0(str)
#define parser_debug1(fmtstr, arg1)
#define parser_debug2(fmtstr, arg1, arg2)
#endif


#endif
