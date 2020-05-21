/*
 * parser.c: A Recursive Descent Parser for C--
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"

// TODO: you may completely wipe out or change the contents of this file; it
//       is just an example of how to get started on the structure of the
//       parser program.

static void program(FILE *fd, ast_node *parent);
static void parser_error(char *err_string);

int lookahead;  // stores next token returned by lexer
                // you may need to change its type to match your implementation

ast ast_tree;   // the abstract syntax tree

/**************************************************************************/
/*
 *  Main parser routine: parses the C-- program in input file pt'ed to by fd,
 *                       calls the function corresponding to the start state,
 *                       checks to see that the last token is DONE,
 *                       prints a success msg if there were no parsing errors
 *  param fd: file pointer for input
 */
void parse(FILE *fd)  {

  // TODO: here is an example of what this function might look like,
  //       you may completely change this:
  ast_info *s;
  ast_node *n;

  // create the root AST node
  s = create_new_ast_node_info(NONTERMINAL, 0, ROOT, 0, 0);
  n = create_ast_node(s);
  if(init_ast(&ast_tree, n)) {
        parser_error("ERROR: bad AST\n");
  }

  // lookahead is a global variable holding the next token
  // you could also use a local variable and then pass it to program
  lookahead = lexan(fd);
  program(fd, ast_tree.root);  // program corresponds to the start state


  // the last token should be DONE
  if (lookahead != DONE) {
    parser_error("expected end of file");
  } else {
     match(DONE, fd);
  }


}
/**************************************************************************/
static void parser_error(char *err_string) {
  if(err_string) {
    printf("%s\n", err_string);
  }
  exit(1);
}
/**************************************************************************/
/*
 *  this function corresponds to the start symbol in the LL(1) grammar
 *  when this function returns, the full AST tree with parent node "parent"
 *  will be constructed
 *         fd: the input stream
 *     parent: the parent ast node  (it should be a ROOT)
 */
static void program(FILE *fd, ast_node *parent) {
  if (lookahead == INT || lookahead == CHAR){
    ast_info child = create_new_ast_node_info(lookahead, 0, TYPE,
                                    lexbuf, src_lineno);
    ast_node child_node = create_ast_node(child);
    add_child_node(parent, child_node);
    lookahead = lexan(fd)
    if (lookahead == ID){
      ast_info child = create_new_ast_node_info(lookahead, 0, 0,
                                      lexbuf, src_lineno);
      ast_node child_node = create_ast_node(child);
      add_child_node(parent, child_node);
      func(fd, parent)
    }else{
      printf("%s\n", "Not syntactically valid" );

    }
  }else{
    printf("%s\n", "Not syntactically valid" );

    }

  parser_debug0("in program\n");

  // assert is useful for testing a function's pre and post conditions
  assert(parent->symbol->token == NONTERMINAL);
  assert(parent->symbol->grammar_symbol == ROOT);
}

  static void func(FILE *fd, ast_node *parent) {
    lookahead = lexan(fd);
    if ((lookahead == PUNCT && tokenval = SEMICOLON )||(lookahead == PUNCT && tokenval == LB)){
      ast_info new = create_new_ast_node_info(NONTERMINAL, 0, FUNC, 0 )


  }


}
