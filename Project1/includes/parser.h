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
#define START_AST_SYM 401       // used to specify start of valid range
#define ROOT          401       // the root ast node
#define FUNC          402
#define FUNDECLIST    403
#define VARDECLIST    404
#define FUNDEC        405
#define FUNDECLISTHELPER   406
#define PARAMDECLIST   407       // a list of variable declarations
#define PARAMDECLISTTAIL 408
#define PARAMFOLLOW   409
#define PARAMDEC1     410
#define  CNEW           411
#define  BLOCK        412
#define  STMTLIST     413
#define  DNEW         414
#define  STMT         415
#define  PRIMARY      416
#define  IDDEC        417
#define  EXPR         418
#define  EXPRLIST     419
#define  EXPRLISTTAIL 420
#define  EXPRZERO     421
#define  EXPRZERODASH 422
#define  EXPRONE      423
#define  EXPRONEDASH  424
#define  EXPRTWO      425
#define  EXPRTWODASH  426
#define  EXPRTHREE    427
#define  EXPRTHREEDASH 428
#define  EXPRFOUR     429
#define  EXPRFOURDASH 430
#define  EXPRFIVE     431
#define  EXPRFIVEDASH 432
#define  TAILFOLLOW   433
#define  PROGRAM      434
#define  VARDECLISTHELPER 435
#define  VARDECLIST 436
#define  VARDEC 437
#define  EXPRFOLLOW 438
#define END_AST_SYM   438       // used to specify end of valid range


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
