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
    ast_info prog_info = create_new_ast_node_info(lookahead, 0, 0,
                                    lexbuf, src_lineno);
    ast_node prog = create_ast_node(prog_info);
    add_child_node(parent, prog);
    lookahead = lexan(fd)
    if (lookahead == ID){
      ast_info id_info = create_new_ast_node_info(ID, 0, 0,
                                      lexbuf, src_lineno);
      ast_node id_node = create_ast_node(id_info);
      add_child_node(prog, id_node);
      lookahead = lexan(fd)
      func(fd, prog);
      add_child_node(parent, prog);
    }else{
      parser_error( "Not syntactically valid" );

    }
  }else{
    parser_error("Not syntactically valid" );

    }


  parser_debug0("in program\n");

  // assert is useful for testing a function's pre and post conditions
  assert(parent->symbol->token == NONTERMINAL);
  assert(parent->symbol->grammar_symbol == ROOT);

}

static void func(FILE *fd, ast_node *parent){
   ast_info func_info = create_new_ast_node_info(NONTERMINAL, 0, FUNC, lexbuf, src_lineno);
   ast_node func_node = create_ast_node(func_info);
    if ((lookahead == PUNCT && tokenval = SEMICOLON )||(lookahead == PUNCT && tokenval == LB)){
      VardecList(fd, func_node);
      lookahead = lexan(fd);
      program(fd,func_node);
    }else if(lookahead == PUNCT && tokenval = LCP ){
      FunDec(fd, punct_node);
      lookahead = lexan(fd);
      FunDecListHelper(fd, punct_node);
      add_child_node(parent, punct_node);
    }else{
      //error condition
    }
}

static void VardecList(FILE *fd, ast_node *parent) {
  if (lookahead == PUNCT && tokenval = SEMICOLON ){
    ast_info vardec_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST, lexbuf, src_lineno);
    ast_node ardec_node = create_ast_node(vardec_info);
    s = create_new_ast_node_info(PUNCT, SEMICOLON, 0, src_lineno);
    new_node_1 = create_ast_node(s);
    add_child_node(vardec_node, new_node_1);
  }else if(lookahead == PUNCT && tokenval =  LB){
    ast_info vardec_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST, lexbuf, src_lineno);
    vardec_node = create_ast_node(vardec_info);
    s = create_new_ast_node_info(PUNCT, LB, 0, lexbuf, src_lineno);
    new_node_1 = create_ast_node(s);
    add_child_node(new_node, new_node_1);

    lookahead = lexan(fd);

    if(lookahead == NUM ){
      s = create_new_ast_node_info(NUM, tokenval, 0,lexbuf, src_lineno);
      new_node_1 = create_ast_node(s);
      add_child_node(new_node, new_node_1);

      lookahead = lexan(fd);

      if(lookahead == PUNCT && tokenval =  RB){
        s = create_new_ast_node_info(PUNCT, RB, 0, lexbuf, src_lineno);
        new_node_1 = create_ast_node(s);
        add_child_node(new_node, new_node_1);

        lookahead = lexan(fd);

        if(lookahead == PUNCT && tokenval =  SEMICOLON){
          s = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
          new_node_1 = create_ast_node(s);
          add_child_node(new_node, new_node_1);
          add_child_node(parent, new_node);
        }else{
          //error
        }

      }else{
        //error
      }


    } else{
      //error condition

    }
  }
}

static void FunDec(FILE *fd, ast_node *parent) {
  fundec_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDEC, lexbuf, src_lineno);
  fundec_node = create_ast_node(fundec_info);
  if((lookahead == PUNCT) && (tokenval == LP)){
    ast_info punct2_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
    ast_node punct2_node = create_ast_node(punct2_info);
    add_child_node(fundec_node, punct2_node);
    lookahead = lexan(fd);
    ParamDecList(fd, fundec_node);
    lookahead = lexan(fd);
    if((lookahead == PUNCT) && (tokenval == RP)){
      ast_info punct3_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
      ast_node punct3_node = create_ast_node(punct3_info);
      add_child_node(fundec_node, punct3_node);
      lookahead = lexan(fd);
      block(fd, fundec_node);
      add_child_node(parent, fundec_node);
    }else{
      //error
    }
  }else{
    //error
  }
}

static void FunDecListHelper(FILE *fd, ast_node *parent) {
  ast_info FunDecListHelper_info = create_new_ast_node_info(NONTERMINAL, 0, FunDecListHelper, lexbuf, src_lineno);
  ast_node FunDecListHelper_node = create_ast_node(FunDecListHelper_info);
  if(lookahead != epsilon) {
    FunDecList(fd, FunDecListHelper_node);
    add_child_node(parent, FunDecListHelper_node);
  }
}

static void FunDecList(FILE *fd, ast_node *parent){
  ast_info FunDecList_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDECLIST,lexbuf, src_lineno);
  ast_node FunDecList_node = create_ast_node(FunDecList_info);
  if((lookahead == INT ) || (lookahead == CHAR)){
    ast_info type_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
    ast_node type_node = create_ast_node(ID_info);
    add_child_node(FunDecList_node, type_node);
    lookahead = lexan(fd);
    if(lookahead == ID){
      ast_info ID_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
      ast_node ID_node = create_ast_node(ID_info);
      add_child_node(FunDecList_node, ID_node);
      lookahead = lexan(fd);
      FunDec(fd, FunDecList_node);
      lookahead = lexan(fd);
      FunDecListHelper(fd, FunDecList_node);
      add_child_node(parent, FunDecList_node);
    }else{
      //parser_error
    }
  }else{
    //parser_error

  }

}

static void ParamDecList(FILE *fd, ast_node *parent){
  if(lookahead != epsilon){
    ast_info ParamDecList_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLIST, lexbuf, src_lineno);
    ast_node ParamDecList_node = create_ast_node(ParamDecList_info);
    ParamDecListTail(fd, ParamDecList_node);
  }else{
    // parser_error
  }
}

static void ParamDecListTail(FILE *fd, ast_node *parent){
  if(lookahead == INT || lookahead == CHAR){
    ast_info ParamDecListTail_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLISTTAIL, lexbuf, src_lineno);
    ast_node ParamDecListTail_node = create_ast_node({ParamDecListTail_info);
    ParamDec1(fd, ParamDecList_node);
    lookahead = lexan(fd);
    if(lookahead == PUNCT && tokenval == COMMA){
      ast_info punct5_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLISTTAIL, lexbuf, src_lineno);
      ast_node punct5_node = create_ast_node(punct5_info);
      add_child_node()
    }
  }else{
    //parser_error
  }
}
