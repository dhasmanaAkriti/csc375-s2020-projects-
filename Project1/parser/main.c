/*
 *  Main function for C-- compiler: now launches parser and prints AST
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

void print_my_ast_node(ast_info *t);

int main(int argc, char *argv[]) {

  FILE *fd = 0;

  if(argc != 2) {
    printf("usage: parser filename.c--\n");
    exit(1);
  }

  if(!(fd = fopen(argv[1], "rw")) ) {
    perror("no such file\n");
    exit(1);
  }

  // parser_init();  // if you need to init any global parser state

  parse(fd);
  printf("**********************************************\n");
  print_ast(ast_tree, print_my_ast_node);
  fclose(fd);

  destroy_ast(&ast_tree);
  exit(0);     /*  successful termination  */

}
/*********************************************************************/

// this is an example of how to define output strings corresponding to
// different ast node state that is used by the print_ast_node function:
static char *t_strings[] = {"int", "char", "if", "else", "while", "break",
                            "write", "writeln", "read", "return", "num", "DONE",
                            "BINOP", };

DIVIDE,
static char *t_strings2[] = {"+", "-", "*", "=", "!=", "<", "<=",">", ">=", "&&",
                            "||", "!", "{", "}", "[", "]", "(", ")", ";", ","};

static char *non_term_strings[] = { "start_ast_sym", "root","program", "func", "fundeclist", "vardeclist",
  "fundec",
  "fundeclisthelper",
  "paramdeclist",
  "paramdeclisttail",
  "paramfollow",
  "paramdec1",
   "cnew",
   "block",
   "stmtlist",
   "dnew",
   "stmt",
   "primary",
   "iddec",
   "expr",
   "exprlist",
   "exprlisttail",
   "exprzero",
   "exprzerodash",
   "exprone",
   "expronedash",
   "exprtwo",
   "exprtwodash",
   "exprthree”,
   “exprthreedash",
   "exprfour",
   "exprfourdash",
   "exprfive",
   "exprfivedash",
   "tailfollow"};

//
// This is the function that is passed to print_ast, to print information
// that is stored in an ast node
//
// TODO: you will need to add more functionality than is currently here
//       and you may need to change what is here to match with the way you
//       defined tokens in your lexer implementation.
//
void print_my_ast_node(ast_info *t) {

  if(t != NULL) {
    if((t->token >= STARTTOKEN) && (t->token <= ENDTOKEN)) {
      if(t->token == PUNCT) {
        printf("%s", t_strings2[(t->token)]);
      }else if(t->token == ID){
        printf("ID: %s",lexbuf);
      }else if(t->token == NUM){
        printf("NUM: %n",(t->value));
      }else{
          printf("%s", t_strings[(t->token)]);
        }
    }
    else if ((t->token == NONTERMINAL)) {
       if((t->grammar_symbol >= START_AST_SYM)
           && (t->grammar_symbol <= END_AST_SYM))
       {
           printf("%s", non_term_strings[(t->grammar_symbol - START_AST_SYM)]);
       }
       else {
           printf("unknown grammar symbol %d", t->grammar_symbol);
       }
    }
    else {
      printf("unknown token %d", t->token);
    }
  }
  else {
    printf("NULL token\n");
  }
}
