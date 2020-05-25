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
     //match(DONE, fd);
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
void program(FILE *fd, ast_node *parent) {
  if (lookahead == INT || lookahead == CHAR){
    ast_info *prog_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
    ast_node *prog = create_ast_node(prog_info);
    add_child_node(parent, prog);
    lookahead = lexan(fd);
    if (lookahead == ID){
      ast_info *id_info = create_new_ast_node_info(ID, 0, 0,
                                      lexbuf, src_lineno);
      ast_node *id_node = create_ast_node(id_info);
      add_child_node(prog, id_node);
      lookahead = lexan(fd);
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

void func(FILE *fd, ast_node *parent){
   ast_info *func_info = create_new_ast_node_info(NONTERMINAL, 0, FUNC, lexbuf, src_lineno);
   ast_node *func_node = create_ast_node(func_info);
    if ((lookahead == PUNCT && tokenval == SEMICOLON )||(lookahead == PUNCT && tokenval == LB)){
      VardecList(fd, func_node);
      lookahead = lexan(fd);
      program(fd,func_node);
    }else if(lookahead == PUNCT && tokenval == LP){
      FunDec(fd, func_node);
      lookahead = lexan(fd);
      FunDecListHelper(fd, func_node);
      add_child_node(parent, func_node);
    }else{
      //error condition
    }
}

void VardecList(FILE *fd, ast_node *parent) {
  if (lookahead == PUNCT && tokenval == SEMICOLON ){
    ast_info *vardeclist_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST, lexbuf, src_lineno);
    ast_node *vardeclist_node = create_ast_node(vardeclist_info);
    ast_info *s = create_new_ast_node_info(PUNCT, SEMICOLON, 0, 0, src_lineno);
    ast_node *new_node_1 = create_ast_node(s);
    add_child_node(vardeclist_node, new_node_1);
  }else if(lookahead == PUNCT && tokenval ==  LB){
    ast_info *vardec_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST, lexbuf, src_lineno);
    ast_node *vardec_node = create_ast_node(vardec_info);
    ast_info *s = create_new_ast_node_info(PUNCT, LB, 0, lexbuf, src_lineno);
    ast_node *new_node_1 = create_ast_node(s);
    add_child_node(vardec_node, new_node_1);

    lookahead = lexan(fd);

    if(lookahead == NUM ){
      ast_info *num_info  = create_new_ast_node_info(NUM, tokenval, 0,lexbuf, src_lineno);
      ast_node *num_node = create_ast_node(num_info);
      add_child_node(vardec_node, num_node);

      lookahead = lexan(fd);

      if(lookahead == PUNCT && tokenval ==  RB){
        ast_info *RB_info = create_new_ast_node_info(PUNCT, RB, 0, lexbuf, src_lineno);
        ast_node *RB_node = create_ast_node(RB_info);
        add_child_node(vardec_node, RB_node);

        lookahead = lexan(fd);

        if(lookahead == PUNCT && tokenval ==  SEMICOLON){
          ast_info *semi_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
          ast_node *semi_node = create_ast_node(semi_info);
          add_child_node(vardec_node, semi_node);
          add_child_node(parent, vardec_node);
        }else{
          parser_error("Not a valid follow token");
        }

      }else{
        parser_error("Not a valid follow token");
      }


    } else{
      parser_error("Not a valid follow token");

    }
  }
}

void FunDec(FILE *fd, ast_node *parent) {

  if((lookahead == PUNCT) && (tokenval == LP)){
    ast_info *fundec_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDEC, lexbuf, src_lineno);
    ast_node *fundec_node = create_ast_node(fundec_info);
    ast_info *punct2_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
    ast_node *punct2_node = create_ast_node(punct2_info);
    add_child_node(fundec_node, punct2_node);
    lookahead = lexan(fd);
    ParamDecList(fd, fundec_node);
    lookahead = lexan(fd);
    if((lookahead == PUNCT) && (tokenval == RP)){
      ast_info *punct3_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
      ast_node *punct3_node = create_ast_node(punct3_info);
      add_child_node(fundec_node, punct3_node);
      lookahead = lexan(fd);
      block(fd, fundec_node);
      add_child_node(parent, fundec_node);
    }else{
      //error
    }
  }
}


void FunDecListHelper(FILE *fd, ast_node *parent) {
  ast_info *FunDecListHelper_info = create_new_ast_node_info(NONTERMINAL, 0, FunDecListHelper, lexbuf, src_lineno);
  ast_node *FunDecListHelper_node = create_ast_node(FunDecListHelper_info);
  if(lookahead == INT || lookahead == CHAR) {
    FunDecList(fd, FunDecListHelper_node);
    add_child_node(parent, FunDecListHelper_node);
  }
}

void FunDecList(FILE *fd, ast_node *parent){
  ast_info *FunDecList_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDECLIST,lexbuf, src_lineno);
  ast_node *FunDecList_node = create_ast_node(FunDecList_info);
  if((lookahead == INT ) || (lookahead == CHAR)){
    ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
    ast_node *type_node = create_ast_node(type_info);
    add_child_node(FunDecList_node, type_node);
    lookahead = lexan(fd);
    if(lookahead == ID){
      ast_info *ID_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
      ast_node *ID_node = create_ast_node(ID_info);
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

void ParamDecList(FILE *fd, ast_node *parent){
  if(lookahead == INT || lookahead == CHAR  ){
    ast_info *ParamDecList_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLIST, lexbuf, src_lineno);
    ast_node *ParamDecList_node = create_ast_node(ParamDecList_info);
    ParamDecListTail(fd, ParamDecList_node);
  }
}

void ParamDecListTail(FILE *fd, ast_node *parent){
  if(lookahead == INT || lookahead == CHAR){
    ast_info *ParamDecListTail_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLISTTAIL, lexbuf, src_lineno);
    ast_node *ParamDecListTail_node = create_ast_node(ParamDecListTail_info);
    ParamDec1(fd, ParamDecListTail_node);
    lookahead = lexan(fd);
    if(lookahead == PUNCT && tokenval == COMMA){
      ast_info *punct5_info = create_new_ast_node_info(PUNCT, COMMA, 0, lexbuf, src_lineno);
      ast_node *punct5_node = create_ast_node(punct5_info);
      add_child_node(ParamDecListTail_node, punct5_node);
      ParamFollow(fd, ParamDecListTail_node);
    }else{
      //parser_error
    }
  }else{
    //parser_error
  }
}

void ParamFollow(FILE *fd, ast_node *parent){
  if(lookahead == INT || lookahead == CHAR ){
    ast_info *ParamFollow_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMFOLLOW, lexbuf, src_lineno);
    ast_node *ParamFollow_node = create_ast_node(ParamFollow_info);
    ParamDecListTail(fd, ParamFollow_node);
    add_child_node(parent, ParamFollow_node);
  }

}

void ParamDec1(FILE *fd, ast_node *parent){
  ast_info *ParamDec1_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDEC1, lexbuf, src_lineno);
  ast_node *ParamDec1_node = create_ast_node(ParamDec1_info);
  if(lookahead == INT || lookahead == CHAR){
    lookahead = lexan(fd);
    if (lookahead == ID){
    ast_info *ID2_info = create_new_ast_node_info(lookahead, 0, PARAMDEC1, lexbuf, src_lineno);
    ast_node *ID2_node = create_ast_node(ID2_info);
    add_child_node(ParamDec1_node, ID2_node);
    lookahead = lexan(fd);
    C(fd, ParamDec1_node);
    add_child_node(parent, ParamDec1_node);
    }else{
    //parser_error
  }}else{
    //parser_error
  }
  }

void C(FILE *fd, ast_node *parent){
  if(lookahead == PUNCT && tokenval == LB){
    ast_info *C_info = create_new_ast_node_info(NONTERMINAL, 0, CNEW, lexbuf, src_lineno);
    ast_node *C_node = create_ast_node(C_info);

    ast_info *punct6_info = create_new_ast_node_info(lookahead, LB, 0, lexbuf, src_lineno);
    ast_node *punct6_node = create_ast_node(punct6_info);
    add_child_node(C_node, punct6_node);
    if(lookahead == PUNCT && tokenval == RB){
      lookahead = lexan(fd);
      ast_info *punct7_info = create_new_ast_node_info(lookahead, RB, 0, lexbuf, src_lineno);
      ast_node *punct7_node = create_ast_node(punct7_info);
      add_child_node(C_node, punct7_node);
      add_child_node (parent, C_node);}

  }else{
    //parser_error
  }
}

void block(FILE *fd, ast_node *parent){
  if(lookahead == PUNCT && tokenval == LCB){
    ast_info *block_info = create_new_ast_node_info(NONTERMINAL, 0, BLOCK, lexbuf, src_lineno);
    ast_node *block_node = create_ast_node(block_info);

    ast_info *punct8_info = create_new_ast_node_info(lookahead, LCB, 0, lexbuf, src_lineno);
    ast_node *punct8_node = create_ast_node(punct8_info);

    add_child_node(block_node, punct8_node);

    lookahead = lexan(fd);
    VardecList(fd, block_node);

    lookahead = lexan(fd);
    StmtList(fd, block_node);

    lookahead = lexan(fd);
    if(lookahead == PUNCT && tokenval == RCB){
      ast_info *punct9_info = create_new_ast_node_info(lookahead, RCB, 0, lexbuf, src_lineno);
      ast_node *punct9_node = create_ast_node(punct9_info);

      add_child_node(block_node, punct9_node);
    }else{
      //parser_error
    }
  }else{
    //parser_error
  }}

void StmtList(FILE *fd, ast_node *parent){
  ast_info *StmtList_info = create_new_ast_node_info(NONTERMINAL, 0, STMTLIST, lexbuf, src_lineno);
  ast_node *StmtList_node = create_ast_node(StmtList_info);
  Stmt(fd, StmtList_node);
  lookahead = lexan(fd);
  D(fd, StmtList_node);
  add_child_node(parent, StmtList_node);
}

void D(FILE *fd, ast_node *parent) {
  ast_info *D_info = create_new_ast_node_info(NONTERMINAL, 0, DNEW, lexbuf, src_lineno);
  ast_node *D_node = create_ast_node(D_info);
  if((lookahead == PUNCT && tokenval == SEMICOLON) || lookahead ==  IF|| lookahead == WHILE ||
     lookahead == BREAK || lookahead == WRITE || lookahead == WRITELN ||lookahead == READ ||
     lookahead == RETURN || lookahead == PUNCT && tokenval == LCB){
       // StmtList(fd,D_node);
       add_child_node(parent, D_node);
     }

}

void Stmt(FILE *fd, ast_node *parent){
  ast_info stmt_info = create_new_ast_node_info(NONTERMINAL, 0, STMTLIST, lexbuf, src_lineno);
  ast_node stmt_node = create_ast_node(stmt_info);
  if(lookahead ==  IF){
    ast_info *if_info = create_new_ast_node_info(IF, 0, 0, lexbuf, src_lineno);
    ast_node *if_node = create_ast_node(if_info);
    add_child_node(stmt_node, if_node);
    lookahead = lexan(fd);
    if(lookahead ==  PUNCT && tokenval == LP){
      ast_info *punct10_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
      ast_node *punct10_node = create_ast_node(punct10_info);
      add_child_node(stmt_node, punct10_node);
      lookahead = lexan(fd);
      expr(fd, stmt_node);
      lookahead = lexan(fd);
      if(lookahead ==  PUNCT && tokenval == RP){
        ast_info *punct11_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
        ast_node *punct11_node = create_ast_node(punct11_info);
        add_child_node(stmt_node, punct11_node);
        lookahead = lexan(fd);
        Stmt(fd, stmt_node);
        if(lookahead ==  ELSE){
          ast_info *punct12_info = create_new_ast_node_info(ELSE, 0, 0, lexbuf, src_lineno);
          ast_node *punct12_node = create_ast_node(punct11_info);
          add_child_node(stmt_node, punct12_node);
          lookahead = lexan(fd);
          Stmt(fd, stmt_node);
          add_child_node(parent, stmt_node);
        }else{
          parser_error
        }
      }else{
        parser_error
      }else{
        parser_error
      }
    }else if(lookahead == WHILE){
      ast_info *while_info = create_new_ast_node_info(IF, 0, 0, lexbuf, src_lineno);
      ast_node *while_node = create_ast_node(while_info);
      add_child_node(stmt_node, while_node);
      lookahead = lexan(fd);
      if(lookahead ==  PUNCT && tokenval == LP){
        ast_info *punct10_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
        ast_node *punct10_node = create_ast_node(punct10_info);
        add_child_node(stmt_node, punct10_node);
        lookahead = lexan(fd);
        expr(fd, stmt_node);
        lookahead = lexan(fd);
        if(lookahead ==  PUNCT && tokenval == RP){
          ast_info *punct11_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
          ast_node *punct11_node = create_ast_node(punct11_info);
          add_child_node(stmt_node, punct11_node);
          lookahead = lexan(fd);
          Stmt(fd, stmt_node);
          add_child_node(parent, stmt_node);
        }else{
          parser_error
        }
      }else{
        parser_error
      }
    }else if(lookahead ==  PUNCT && tokenval == SEMICOLON){
      ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
      ast_node *punct12_node = create_ast_node(punct12_info);
      add_child_node(stmt_node, punct12_node);
      add_child_node(parent, stmt_node);

    } else if(lookahead == RETURN || ookahead == WRITE ){
      ast_info *punct13_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
      ast_node *punct13_node = create_ast_node(punct13_info);
      add_child_node(stmt_node, punct13_node);
      lookahead(fd);
      expr(fd, punct13_node);
      lookahead(fd);
      if(lookahead ==  PUNCT && tokenval == SEMICOLON){
        ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
        ast_node *punct12_node = create_ast_node(punct12_info);
        add_child_node(stmt_node, punct12_node);
        add_child_node(parent, stmt_node);
      }else{
        parse_error;
      }
    }else if(lookahead == BREAK || ookahead == WRITELN ){
      ast_info *punct13_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
      ast_node *punct13_node = create_ast_node(punct13_info);
      add_child_node(stmt_node, punct13_node);
      lookahead(fd);
      if(lookahead ==  PUNCT && tokenval == SEMICOLON){
        ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
        ast_node *punct12_node = create_ast_node(punct12_info);
        add_child_node(stmt_node, punct12_node);
        add_child_node(parent, stmt_node);
      }else{
        parse_error
      }
    }else if(lookahead == PUNCT && tokenval == LCB){
      block(fd, stmt_node);
      dd_child_node(parent, stmt_node);
    }else{
      expr(fd, stmt_node);
    }
}
