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
static void parser_error(src_lineno);
void print_my_ast_node(ast_info *t);

char *terminal_strings[] = {"STARTTOKEN",
              "INT",
              "CHAR",        // types
              "IF",
              "ELSE",
              "WHILE",
              "BREAK",
              "WRITE",
              "WRITELN",
              "READ",
              "RETURN",          // keyword
              "NUM",              // integer literal
              "ID",
              "BINOP",
              "UNOP",
              "PUNCT",             // special "token" indicates LA is done
              "PLUS",
              "MINUS",
              "DIVIDE",
              "MULTIPLY",
              "E",
              "NE",
              "LT",
              "LE",
              "GT",
              "GE",
              "AND",
              "OR",
              "NOT",
              "LCB",
              "RCB",
              "LB",
              "RB",
              "LP",
              "RP",
              "SEMICOLON",
              "COMMA",
              "ASSIGN",
              "DONE",
              "ENDTOKEN"};

int lookahead;  // stores next token returned by lexer
                // you may need to change its type to match your implementation
int second = 0;
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
        parser_error(src_lineno);
  }

  // lookahead is a global variable holding the next token
  // you could also use a local variable and then pass it to program
  lookahead = lexan(fd);
  program(fd, ast_tree.root);  // program corresponds to the start state


  // the last token should be DONE
  if (lookahead != DONE) {
    printf("expected end of file");
  } else {
     printf("YAYYYYYYYYYYYY\n");
  }


}
/**************************************************************************/
static void parser_error(int lineno) {
  ("Error on line %d. \n", lineno);
  exit(1);
}
int match(int matched_with, int matched_with_tokenval){
      if(lookahead == matched_with && matched_with == ID){
        printf("MATCH:%s", terminal_strings[lookahead]);
        printf(".%s\n",lexbuf);
        return 1;
      } else if(lookahead == matched_with && matched_with == NUM){
        printf("MATCH:%s", terminal_strings[lookahead]);
        printf(".%d\n",tokenval);
        return 1;
      }else if ((lookahead == matched_with && matched_with == PUNCT  && tokenval == matched_with_tokenval)||
      (lookahead == matched_with && matched_with == BINOP && tokenval == matched_with_tokenval)
      ||(lookahead == matched_with && matched_with == UNOP&& tokenval == matched_with_tokenval)) {
        printf("MATCH:%s", terminal_strings[lookahead]);
        printf(".%s\n", terminal_strings[tokenval]);
        return 1;
      }else if((lookahead == matched_with && matched_with == PUNCT) ||
               (lookahead == matched_with && matched_with == BINOP)||
                (lookahead == matched_with && matched_with == UNOP)){
        return 0;
      }else if(lookahead == matched_with){
        printf("MATCH:%s", terminal_strings[lookahead]);
        printf("\n");
        return 1;
      }else{
        return 0;
    }
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
  printf("program\n");
  ast_info *prog_info = create_new_ast_node_info(NONTERMINAL, 0, PROGRAM, 0, src_lineno);
  ast_node *prog = create_ast_node(prog_info);
  if (match(INT, 0)|| match(CHAR, 0)){
    ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, 0, src_lineno);
    ast_node *type = create_ast_node(type_info);
    add_child_node(prog, type);
    lookahead = lexan(fd);
    if (match(ID, 0)){
      ast_info *id_info = create_new_ast_node_info(ID, 0, 0,
                                      lexbuf, src_lineno);
      ast_node *id_node = create_ast_node(id_info);
      add_child_node(prog, id_node);
      lookahead = lexan(fd);
      func(fd, prog);
      add_child_node(parent, prog);
    }else{
    parser_error(src_lineno );

    }
  }else{
    parser_error(src_lineno);
  }
}

void func(FILE *fd, ast_node *parent){
   ast_info *func_info = create_new_ast_node_info(NONTERMINAL, 0, FUNC, lexbuf, src_lineno);
   ast_node *func_node = create_ast_node(func_info);
   if ((if lookahead == PUNCT && tokenval == SEMICOLON)||(if lookahead == PUNCT && tokenval == LB)){
      VarDec(fd, func_node);
      K(fd, func_node);
      add_child_node(parent, func_node);
    }else if(){
      FunDec(fd, func_node);
      FunDecListHelper(fd, func_node);
      add_child_node(parent, func_node);
    }else{
      parser_error(src_lineno);
    }
}

void VardecList(FILE *fd, ast_node *parent){
  printf("VardecList\n");
  ast_info *VarDecList_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST,lexbuf, src_lineno);
  ast_node *VarDecList_node = create_ast_node(VarDecList_info);
  if(match(INT, 0)|| match(CHAR, 0)){
    ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
    ast_node *type_node = create_ast_node(type_info);
    add_child_node(VarDecList_node, type_node);
    lookahead = lexan(fd);
    if(match(ID, 0)){
      ast_info *ID_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
      ast_node *ID_node = create_ast_node(ID_info);
      add_child_node(VarDecList_node, ID_node);
      lookahead = lexan(fd);
      VarDec(fd, VarDecList_node);
      VarDecListHelper(fd, VarDecList_node);
      add_child_node(parent, VarDecList_node);
    }else{
      parser_error(src_lineno);
    }
  }else{
    parser_error(src_lineno);

  }

}

void VarDec(FILE *fd, ast_node *parent) {
  printf("VarDec\n");
  if (match(PUNCT, SEMICOLON)){
    ast_info *vardec_info = create_new_ast_node_info(NONTERMINAL, 0, VARDEC, lexbuf, src_lineno);
    ast_node *vardec_node = create_ast_node(vardec_info);
    ast_info *s = create_new_ast_node_info(PUNCT, SEMICOLON, 0, 0, src_lineno);
    ast_node *new_node_1 = create_ast_node(s);
    add_child_node(vardec_node, new_node_1);
    add_child_node(parent, vardec_node);
    lookahead = lexan(fd);
  }else if(match(PUNCT, LB)){
    ast_info *vardec_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLIST, lexbuf, src_lineno);
    ast_node *vardec_node = create_ast_node(vardec_info);
    ast_info *s = create_new_ast_node_info(PUNCT, LB, 0, lexbuf, src_lineno);
    ast_node *new_node_1 = create_ast_node(s);
    add_child_node(vardec_node, new_node_1);

    lookahead = lexan(fd);

    if(match(NUM, 0)){
      ast_info *num_info  = create_new_ast_node_info(NUM, tokenval, 0,lexbuf, src_lineno);
      ast_node *num_node = create_ast_node(num_info);
      add_child_node(vardec_node, num_node);

      lookahead = lexan(fd);

      if(match(PUNCT, RB)){
        ast_info *RB_info = create_new_ast_node_info(PUNCT, RB, 0, lexbuf, src_lineno);
        ast_node *RB_node = create_ast_node(RB_info);
        add_child_node(vardec_node, RB_node);

        lookahead = lexan(fd);

        if(match(PUNCT, SEMICOLON)){
          ast_info *semi_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
          ast_node *semi_node = create_ast_node(semi_info);
          add_child_node(vardec_node, semi_node);
          add_child_node(parent, vardec_node);
          lookahead = lexan(fd);
        }else{
          parser_error(src_lineno);
        }

      }else{
        parser_error(src_lineno);
      }


    } else{
      parser_error(src_lineno);

    }
  }
}

void FunDec(FILE *fd, ast_node *parent) {
  printf("FunDec\n");
  if(match(PUNCT, LP)){
    ast_info *fundec_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDEC, lexbuf, src_lineno);
    ast_node *fundec_node = create_ast_node(fundec_info);
    ast_info *punct2_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
    ast_node *punct2_node = create_ast_node(punct2_info);
    add_child_node(fundec_node, punct2_node);
    lookahead = lexan(fd);
    ParamDecList(fd, fundec_node);
    if(match(PUNCT, RP)){
      ast_info *punct3_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
      ast_node *punct3_node = create_ast_node(punct3_info);
      add_child_node(fundec_node, punct3_node);
      lookahead = lexan(fd);
      block(fd, fundec_node);
      add_child_node(parent, fundec_node);
    }else{
      parser_error(src_lineno);
    }
  }
}

void FunDecListHelper(FILE *fd, ast_node *parent) {
  printf("FunDecListHelper\n");
  if(match(INT, 0)||match(CHAR, 0)) {
    ast_info *FunDecListHelper_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDECLISTHELPER, lexbuf, src_lineno);
    ast_node *FunDecListHelper_node = create_ast_node(FunDecListHelper_info);
    FunDecList(fd, FunDecListHelper_node);
    add_child_node(parent, FunDecListHelper_node);
  }
}

void VarDecListHelper(FILE *fd, ast_node *parent) {
    printf("VarDecListHelper\n");
  if(match(INT, 0)||match(CHAR, 0)) {
    ast_info *VarDecListHelper_info = create_new_ast_node_info(NONTERMINAL, 0, VARDECLISTHELPER, lexbuf, src_lineno);
    ast_node *VarDecListHelper_node = create_ast_node(VarDecListHelper_info);
    VardecList(fd, VarDecListHelper_node);
    add_child_node(parent, VarDecListHelper_node);
  }
}

void K(FILE *fd, ast_node *parent) {
    printf("K\n");
    ast_info *prog_info = create_new_ast_node_info(NONTERMINAL, 0, PROGRAM, 0, src_lineno);
    ast_node *prog = create_ast_node(prog_info);
    if (match(INT, 0)|| match(CHAR, 0)){
      ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, 0, src_lineno);
      ast_node *type = create_ast_node(type_info);
      add_child_node(prog, type);
      lookahead = lexan(fd);
      if (match(ID, 0)){
        ast_info *id_info = create_new_ast_node_info(ID, 0, 0,
                                        lexbuf, src_lineno);
        ast_node *id_node = create_ast_node(id_info);
        add_child_node(prog, id_node);
        lookahead = lexan(fd);
        func(fd, prog);
        add_child_node(parent, prog);
      }else{
      parser_error(src_lineno );

      }
    }
}

void FunDecList(FILE *fd, ast_node *parent){
  printf("FunDecList\n");
  ast_info *FunDecList_info = create_new_ast_node_info(NONTERMINAL, 0, FUNDECLIST,lexbuf, src_lineno);
  ast_node *FunDecList_node = create_ast_node(FunDecList_info);
  if(match(INT, 0)||match(CHAR, 0)){
    ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
    ast_node *type_node = create_ast_node(type_info);
    add_child_node(FunDecList_node, type_node);
    lookahead = lexan(fd);
    if(match(ID, 0)){
      ast_info *ID_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
      ast_node *ID_node = create_ast_node(ID_info);
      add_child_node(FunDecList_node, ID_node);
      lookahead = lexan(fd);
      FunDec(fd, FunDecList_node);
      FunDecListHelper(fd, FunDecList_node);
      add_child_node(parent, FunDecList_node);
    }else{
      parser_error(src_lineno);
    }
  }else{
    parser_error(src_lineno);

  }

}

void ParamDecList(FILE *fd, ast_node *parent){
  printf("ParamDecList\n");
  if(match(INT, 0)||match(CHAR, 0)){
    ast_info *ParamDecList_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLIST, lexbuf, src_lineno);
    ast_node *ParamDecList_node = create_ast_node(ParamDecList_info);
    ParamDecListTail(fd, ParamDecList_node);
  }
}

void ParamDecListTail(FILE *fd, ast_node *parent){
  printf("ParamDecListTail\n");
  if(match(INT, 0)||match(CHAR, 0)){
    ast_info *ParamDecListTail_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDECLISTTAIL, lexbuf, src_lineno);
    ast_node *ParamDecListTail_node = create_ast_node(ParamDecListTail_info);
    ParamDec1(fd, ParamDecListTail_node);
    ParamFollow(fd, ParamDecListTail_node);
    add_child_node(parent, ParamDecListTail_node);
  }else{
    parser_error(src_lineno);
  }
}

void ParamFollow(FILE *fd, ast_node *parent){
  printf("ParamFollow\n");
  if(match(PUNCT, COMMA)){
    ast_info *ParamFollow_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMFOLLOW, lexbuf, src_lineno);
    ast_node *ParamFollow_node = create_ast_node(ParamFollow_info);
    ast_info *punct5_info = create_new_ast_node_info(PUNCT, COMMA, 0, lexbuf, src_lineno);
    ast_node *punct5_node = create_ast_node(punct5_info);
    add_child_node(ParamFollow_node, punct5_node);
    lookahead = lexan(fd);
    if(match(INT, 0)||match(CHAR, 0)){
      ParamDecListTail(fd, ParamFollow_node);
      add_child_node(parent, ParamFollow_node);
    }else{
      parser_error(src_lineno);
    }
  }
}

void ParamDec1(FILE *fd, ast_node *parent){
  ast_info *ParamDec1_info = create_new_ast_node_info(NONTERMINAL, 0, PARAMDEC1, lexbuf, src_lineno);
  ast_node *ParamDec1_node = create_ast_node(ParamDec1_info);
  if(match(INT, 0)||match(CHAR, 0)){
    ast_info *type_info = create_new_ast_node_info(lookahead, 0, 0, 0, src_lineno);
    ast_node *type_node = create_ast_node(type_info);
    add_child_node(ParamDec1_node, type_node);
    lookahead = lexan(fd);
    if (match(ID, 0)){
      ast_info *ID2_info = create_new_ast_node_info(lookahead, 0, PARAMDEC1, lexbuf, src_lineno);
      ast_node *ID2_node = create_ast_node(ID2_info);
      add_child_node(ParamDec1_node, ID2_node);
      lookahead = lexan(fd);
      C(fd, ParamDec1_node);
      add_child_node(parent, ParamDec1_node);
    }else{
    parser_error(src_lineno);
    }
  }else{
    parser_error(src_lineno);
  }
}

void C(FILE *fd, ast_node *parent){
  printf("C\n");
  if(match(PUNCT, LB)){
    printf("C\n");
    ast_info *C_info = create_new_ast_node_info(NONTERMINAL, 0, CNEW, lexbuf, src_lineno);
    ast_node *C_node = create_ast_node(C_info);

    ast_info *punct6_info = create_new_ast_node_info(lookahead, LB, 0, lexbuf, src_lineno);
    ast_node *punct6_node = create_ast_node(punct6_info);
    add_child_node(C_node, punct6_node);
    lookahead = lexan(fd);
    if(match(PUNCT, RB)){
      ast_info *punct7_info = create_new_ast_node_info(lookahead, RB, 0, lexbuf, src_lineno);
      ast_node *punct7_node = create_ast_node(punct7_info);
      add_child_node(C_node, punct7_node);
      add_child_node (parent, C_node);
      lookahead = lexan(fd);
    }else{
      parser_error(src_lineno);
    }
  }
}

void block(FILE *fd, ast_node *parent){
  printf("block\n");
  if(match(PUNCT, LCB)){
    ast_info *block_info = create_new_ast_node_info(NONTERMINAL, 0, BLOCK, lexbuf, src_lineno);
    ast_node *block_node = create_ast_node(block_info);

    ast_info *punct8_info = create_new_ast_node_info(lookahead, LCB, 0, lexbuf, src_lineno);
    ast_node *punct8_node = create_ast_node(punct8_info);

    add_child_node(block_node, punct8_node);

    lookahead = lexan(fd);
    VarDecListHelper(fd, block_node);

    StmtList(fd, block_node);
    printf("%s\n",terminal_strings[tokenval]);

    if(match(PUNCT, RCB)){
      ast_info *punct9_info = create_new_ast_node_info(lookahead, RCB, 0, lexbuf, src_lineno);
      ast_node *punct9_node = create_ast_node(punct9_info);
      lookahead = lexan(fd);
      add_child_node(block_node, punct9_node);
    }else{
      parser_error(src_lineno);
    }
  }else{
    parser_error(src_lineno);
  }
}

void StmtList(FILE *fd, ast_node *parent){
  printf("StmtList\n");

  ast_info *StmtList_info = create_new_ast_node_info(NONTERMINAL, 0, STMTLIST, lexbuf, src_lineno);
  ast_node *StmtList_node = create_ast_node(StmtList_info);
  Stmt(fd, StmtList_node);
  D(fd, StmtList_node);
  add_child_node(parent, StmtList_node);
}

void D(FILE *fd, ast_node *parent) {
  printf("D\n");
  ast_info *D_info = create_new_ast_node_info(NONTERMINAL, 0, DNEW, lexbuf, src_lineno);
  ast_node *D_node = create_ast_node(D_info);
  if((match(PUNCT, SEMICOLON)) ||match(IF,0)|| match(WHILE, 0) ||
     match(BREAK, 0) ||match(WRITE, 0) ||match( WRITELN, 0) || match( READ, 0) ||
     match(RETURN, 0) || match(PUNCT, LCB)|| match(UNOP, ASSIGN)|| match(UNOP, NOT)
     || match(INT, 0)||  match(CHAR, 0) || match(ID, 0) ||match(NUM, 0) || match(PUNCT, LP)){
     StmtList(fd,D_node);
     add_child_node(parent, D_node);
  }
}

void Stmt(FILE *fd, ast_node *parent){
  printf("Stmt\n");
  ast_info *stmt_info = create_new_ast_node_info(NONTERMINAL, 0, STMTLIST, lexbuf, src_lineno);
  ast_node *stmt_node = create_ast_node(stmt_info);

  if(match(IF,0)){
    ast_info *if_info = create_new_ast_node_info(IF, 0, 0, lexbuf, src_lineno);
    ast_node *if_node = create_ast_node(if_info);
    add_child_node(stmt_node, if_node);
    lookahead = lexan(fd);
    if(match(PUNCT, LP)){
      ast_info *punct10_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
      ast_node *punct10_node = create_ast_node(punct10_info);
      add_child_node(stmt_node, punct10_node);
      lookahead = lexan(fd);
      expr(fd, stmt_node);
      if(match(PUNCT, RP)){
        ast_info *punct11_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
        ast_node *punct11_node = create_ast_node(punct11_info);
        add_child_node(stmt_node, punct11_node);
        lookahead = lexan(fd);
        Stmt(fd, stmt_node);
        if(match(ELSE, 0)){
          ast_info *punct12_info = create_new_ast_node_info(ELSE, 0, 0, lexbuf, src_lineno);
          ast_node *punct12_node = create_ast_node(punct11_info);
          add_child_node(stmt_node, punct12_node);
          lookahead = lexan(fd);
          Stmt(fd, stmt_node);
          add_child_node(parent, stmt_node);
        }else{
          parser_error(src_lineno);
        }
      }else{
        parser_error(src_lineno);
      }
    }else{
        parser_error(src_lineno);
      }
  }else if(match(WHILE, 0)){
      ast_info *while_info = create_new_ast_node_info(IF, 0, 0, lexbuf, src_lineno);
      ast_node *while_node = create_ast_node(while_info);
      add_child_node(stmt_node, while_node);
      lookahead = lexan(fd);
      if(match(PUNCT, LP)){
        ast_info *punct10_info = create_new_ast_node_info(PUNCT, LP, 0, lexbuf, src_lineno);
        ast_node *punct10_node = create_ast_node(punct10_info);
        add_child_node(stmt_node, punct10_node);
        lookahead = lexan(fd);
        expr(fd, stmt_node);
        if(match(PUNCT, RP)){
          ast_info *punct11_info = create_new_ast_node_info(PUNCT, RP, 0, lexbuf, src_lineno);
          ast_node *punct11_node = create_ast_node(punct11_info);
          add_child_node(stmt_node, punct11_node);
          lookahead = lexan(fd);
          Stmt(fd, stmt_node);
          add_child_node(parent, stmt_node);
        }else{
          parser_error(src_lineno);
        }
      }else{
        parser_error(src_lineno);
      }
    }else if(match(PUNCT, SEMICOLON)){
      ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
      ast_node *punct12_node = create_ast_node(punct12_info);
      add_child_node(stmt_node, punct12_node);
      add_child_node(parent, stmt_node);
      lookahead = lexan(fd);

    } else if(match(RETURN, 0) ||match(WRITE, 0)){
      ast_info *punct13_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
      ast_node *punct13_node = create_ast_node(punct13_info);
      add_child_node(stmt_node, punct13_node);
      lookahead = lexan(fd);
      expr(fd, punct13_node);
      printf("%s\n",terminal_strings[tokenval]);
      if(match(PUNCT, SEMICOLON)){
        ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
        ast_node *punct12_node = create_ast_node(punct12_info);
        add_child_node(stmt_node, punct12_node);
        add_child_node(parent, stmt_node);
        lookahead = lexan(fd);
      }else{
        parser_error(src_lineno);
      }
    }else if(match(BREAK, 0) || match(WRITELN, 0) ){
      printf("%s\n", "helloooooo");
      ast_info *punct13_info = create_new_ast_node_info(lookahead, 0, 0, lexbuf, src_lineno);
      ast_node *punct13_node = create_ast_node(punct13_info);
      add_child_node(stmt_node, punct13_node);
      lookahead = lexan(fd);
      if(match(PUNCT, SEMICOLON)){
        ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
        ast_node *punct12_node = create_ast_node(punct12_info);
        add_child_node(stmt_node, punct12_node);
        add_child_node(parent, stmt_node);
        lookahead = lexan(fd);
      }else{
        parser_error(src_lineno);
      }
    }else if(match(PUNCT, LCB)){
      block(fd, stmt_node);
      add_child_node(parent, stmt_node);
    }else if(match(READ, 0)){
      ast_info *read_info = create_new_ast_node_info(READ, 0, 0, lexbuf, src_lineno);
      ast_node *read_node = create_ast_node(read_info);
      add_child_node(stmt_node, read_node);
      lookahead = lexan(fd);
      if(match(ID, 0)){
        ast_info *id_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
        ast_node *id_node = create_ast_node(id_info);
        add_child_node(stmt_node, id_node);
        lookahead = lexan(fd);
        if(match(PUNCT, SEMICOLON)){
          ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
          ast_node *punct12_node = create_ast_node(punct12_info);
          add_child_node(stmt_node, punct12_node);
          add_child_node(parent, stmt_node);
          lookahead = lexan(fd);
        }else{
          parser_error(src_lineno);
        }
      }else{
        parser_error(src_lineno);
      }
    }else{
      expr(fd, stmt_node);
      if(match(PUNCT, SEMICOLON)){
        ast_info *punct12_info = create_new_ast_node_info(PUNCT, SEMICOLON, 0, lexbuf, src_lineno);
        ast_node *punct12_node = create_ast_node(punct12_info);
        add_child_node(stmt_node, punct12_node);
        add_child_node(parent, stmt_node);
        lookahead = lexan(fd);
      }else{
        parser_error(src_lineno);
      }
    }
}

void expr(FILE *fd, ast_node *parent){
  printf("expr\n");
  if (match(BINOP,MINUS)){
    ast_info *expr_info = create_new_ast_node_info(NONTERMINAL, 0, EXPR, 0, src_lineno);
    ast_node *expr_node = create_ast_node(expr_info);

    ast_info *punct14_info = create_new_ast_node_info(BINOP, MINUS, 0, lexbuf, src_lineno);
    ast_node *punct14_node = create_ast_node(punct14_info);

    add_child_node(expr_node, punct14_node);

    lookahead = lexan(fd);

    expr(fd, expr_node);
    add_child_node(parent, expr_node);

  }else if (match(ID,0)){
    ast_info *expr_info = create_new_ast_node_info(NONTERMINAL, 0, EXPR, 0, src_lineno);
    ast_node *expr_node = create_ast_node(expr_info);

    ast_info *ID_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
    ast_node *ID_node = create_ast_node(ID_info);

    add_child_node(expr_node, ID_node);
    second = lexan(fd);
    exprfollow(fd, expr_node);
    add_child_node(parent, expr_node);


  }else{
    ast_info *expr_info = create_new_ast_node_info(NONTERMINAL, 0, EXPR, 0, src_lineno);
    ast_node *expr_node = create_ast_node(expr_info);

    expr_zero(fd, expr_node);

    add_child_node(parent, expr_node);
  }
}

void exprfollow(FILE *fd, ast_node *parent){
  printf("exprfollow\n");
  ast_info *exprfollow_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRFOLLOW, 0, src_lineno);
  ast_node *exprfollow_node = create_ast_node(exprfollow_info);
  if(second == UNOP && tokenval == ASSIGN){
    lookahead = second;
    match(UNOP, ASSIGN);
    second = 0;
    ast_info *eq_info = create_new_ast_node_info(UNOP, ASSIGN, 0, lexbuf, src_lineno);
    ast_node *eq_node = create_ast_node(eq_info);
    lookahead = lexan(fd);
    add_child_node(exprfollow_node, eq_node);

    expr_zero(fd, exprfollow_node);

    add_child_node(parent, exprfollow_node);

  }else if (second == PUNCT && tokenval == LB){

    ast_info *lb_info = create_new_ast_node_info(PUNCT, LB, 0, lexbuf, src_lineno);
    ast_node *lb_node = create_ast_node(lb_info);

    lookahead = second;
    second = 0;
    match(PUNCT, LB);
    printf("%s\n", terminal_strings[lookahead]);
    printf("%s\n", terminal_strings[tokenval]);
    add_child_node(exprfollow_node, lb_node);

    lookahead = lexan(fd);
    printf("%s\n", lexbuf);
    printf("%s\n", terminal_strings[lookahead]);
    printf("%s\n", terminal_strings[tokenval]);

    expr_zero(fd, exprfollow_node);

    printf("%s\n", terminal_strings[lookahead]);
    printf("%s\n", terminal_strings[tokenval]);

    if (match(PUNCT, RB)){
      ast_info *rb_info = create_new_ast_node_info(PUNCT, RB, 0, lexbuf, src_lineno);
      ast_node *rb_node = create_ast_node(lb_info);

      add_child_node(exprfollow_node, rb_node);
      lookahead = lexan(fd);

        if(lookahead == UNOP && tokenval == ASSIGN){
          ast_info *eq_info = create_new_ast_node_info(UNOP, ASSIGN, 0, lexbuf, src_lineno);
          ast_node *eq_node = create_ast_node(eq_info);

          add_child_node(exprfollow_node, eq_node);

          lookahead = lexan(fd);

          expr_zero(fd, exprfollow_node);

          add_child_node(parent, exprfollow_node);
        }
    }else{
      parser_error(src_lineno);
    }
  }else{
    expr_zero(fd, exprfollow_node);
  }
}

void expr_zero(FILE *fd, ast_node *parent){
  ast_info *expr_0_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRZERO, 0, src_lineno);
  ast_node *expr_0_node = create_ast_node(expr_0_info);
  printf("expr_zero\n");

  expr_one(fd, expr_0_node);
  expr_zero_dash(fd, expr_0_node);
  add_child_node(parent, expr_0_node);
}

void expr_one(FILE *fd, ast_node *parent){
  printf("expr_one\n");
  ast_info *expr_1_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRONE, 0, src_lineno);
  ast_node *expr_1_node = create_ast_node(expr_1_info);

  expr_two(fd, expr_1_node);

  expr_one_dash(fd, expr_1_node);

  add_child_node(parent, expr_1_node);
}

void expr_zero_dash(FILE *fd, ast_node *parent){
  printf("expr_zero_dash\n");
  if(match(BINOP, OR)){
    ast_info *expr_0_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRZERODASH, 0, src_lineno);
    ast_node *expr_0_dash_node = create_ast_node( expr_0_dash_info);
    ast_info *or_info = create_new_ast_node_info(BINOP, OR, 0, 0, src_lineno);
    ast_node *or_node = create_ast_node( or_info);

    add_child_node(expr_0_dash_node, or_node);

    lookahead = lexan(fd);
    expr_one(fd, expr_0_dash_node);
    expr_zero_dash(fd, expr_0_dash_node);

    add_child_node(parent, expr_0_dash_node);

  }
}

void expr_two(FILE *fd, ast_node *parent){
  printf("expr_two\n");
  ast_info *expr_two_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRTWO, 0, src_lineno);
  ast_node *expr_two_node = create_ast_node(expr_two_info);


  expr_three(fd, expr_two_node);

  expr_two_dash(fd, expr_two_node);

  add_child_node(parent, expr_two_node);

}

void expr_one_dash(FILE *fd, ast_node *parent){
  printf("expr_one_dash\n");
  if(match(BINOP, AND)){
    ast_info *expr_one_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRONEDASH, 0, src_lineno);
    ast_node *expr_one_dash_node = create_ast_node( expr_one_dash_info);

    ast_info *and_info = create_new_ast_node_info(BINOP, AND, 0, 0, src_lineno);
    ast_node *and_node = create_ast_node(and_info);

    add_child_node(expr_one_dash_node, and_node);
    lookahead = lexan(fd);
    expr_two(fd, expr_one_dash_node);

    expr_one_dash(fd, expr_one_dash_node);

    add_child_node(parent, expr_one_dash_node);

  }
}

void expr_three(FILE *fd, ast_node *parent){
  printf("expr_three\n");
  ast_info *expr_three_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRTHREE, 0, src_lineno);
  ast_node *expr_three_node = create_ast_node(expr_three_info);

  expr_four(fd, expr_three_node);

  expr_three_dash(fd, expr_three_node);

  add_child_node(parent, expr_three_node);

}

void expr_two_dash(FILE *fd, ast_node *parent){
  printf("expr_two_dash\n");
  if(match(BINOP, E) ||match(BINOP, NE)){
    ast_info *expr_two_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRTWODASH, 0, src_lineno);
    ast_node *expr_two_dash_node = create_ast_node( expr_two_dash_info);
    ast_info *e_info = create_new_ast_node_info(BINOP, tokenval, 0, 0, src_lineno);
    ast_node *e_node = create_ast_node(e_info);

    add_child_node(expr_two_dash_node, e_node);
    lookahead = lexan(fd);

    expr_three(fd, expr_two_dash_node);

    expr_two_dash(fd, expr_two_dash_node);

    add_child_node(parent, expr_two_dash_node);

  }
}

void expr_four(FILE *fd, ast_node *parent){
  printf("expr_four\n");
  ast_info *expr_four_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRFOUR, 0, src_lineno);
  ast_node *expr_four_node = create_ast_node(expr_four_info);

  expr_five(fd, expr_four_node);

  expr_four_dash(fd, expr_four_node);

  add_child_node(parent, expr_four_node);

}

void expr_three_dash(FILE *fd, ast_node *parent){
  printf("expr_three_dash\n");
  if(match( BINOP , GT) || match( BINOP , LT )||match( BINOP , LE) ||match( BINOP , GE )){
    ast_info *expr_three_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRTHREEDASH, 0, src_lineno);
    ast_node *expr_three_dash_node = create_ast_node( expr_three_dash_info);
    ast_info *rel_info = create_new_ast_node_info(BINOP, tokenval, 0, 0, src_lineno);
    ast_node *rel_node = create_ast_node(rel_info);

    add_child_node(expr_three_dash_node, rel_node);
    lookahead = lexan(fd);

    expr_four(fd, expr_three_dash_node);
    expr_three_dash(fd, expr_three_dash_node);

    add_child_node(parent, expr_three_dash_node);

  }
}

void expr_five(FILE *fd, ast_node *parent){
  printf("expr_five\n");
  ast_info *expr_five_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRFIVE, 0, src_lineno);
  ast_node *expr_five_node = create_ast_node(expr_five_info);

  primary(fd, expr_five_node);
  // printf("%s\n", terminal_strings[lookahead]);
  // printf("%s\n", terminal_strings[tokenval]);
  expr_five_dash(fd, expr_five_node);
  add_child_node(parent, expr_five_node);

}

void expr_four_dash(FILE *fd, ast_node *parent){
  printf("expr_four_dash\n");
  if(match(BINOP ,PLUS)|| match( BINOP ,MINUS )){
    ast_info *expr_four_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRFOURDASH, 0, src_lineno);
    ast_node *expr_four_dash_node = create_ast_node( expr_four_dash_info);

    ast_info *pm_info = create_new_ast_node_info(BINOP, tokenval, 0, 0, src_lineno);
    ast_node *pm_node = create_ast_node(pm_info);

    add_child_node(expr_four_dash_node, pm_node);

    lookahead = lexan(fd);

    expr_five(fd, expr_four_dash_node);

    expr_four_dash(fd, expr_four_dash_node);

    add_child_node(parent, expr_four_dash_node);

  }
}

void expr_five_dash(FILE *fd, ast_node *parent){
  printf("expr_five_dash\n");
  if(match( BINOP , MULTIPLY)||match( BINOP , DIVIDE )){

    ast_info *expr_five_dash_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRFOURDASH, 0, src_lineno);
    ast_node *expr_five_dash_node = create_ast_node( expr_five_dash_info);
    ast_info *dm_info = create_new_ast_node_info(BINOP, tokenval, 0, 0, src_lineno);
    ast_node *dm_node = create_ast_node(dm_info);

    add_child_node(expr_five_dash_node, dm_node);
    lookahead = lexan(fd);
    primary(fd, expr_five_dash_node);
    expr_five_dash(fd, expr_five_dash_node);
    add_child_node(parent, expr_five_dash_node);
  }
}

void primary(FILE *fd, ast_node *parent){
  printf("primary\n");

  if(lookahead == ID){
    ast_info *primary_info = create_new_ast_node_info(NONTERMINAL, 0, PRIMARY, 0, src_lineno);
    ast_node *primary_node = create_ast_node(primary_info);
    ast_info *id_info = create_new_ast_node_info(ID, 0, 0, lexbuf, src_lineno);
    ast_node *id_node = create_ast_node(id_info);

    add_child_node(primary_node, id_node);
    if(second != 0){
      lookahead = second;
      second = 0;
    }else{
      lookahead = lexan(fd);
      // printf("%s\n", terminal_strings[lookahead]);
      // printf("%s\n", terminal_strings[tokenval]);
    }
    id_dec(fd, id_node);
    add_child_node(parent, primary_node);
  }else if(match(NUM, 0)){
      ast_info *primary_info = create_new_ast_node_info(NONTERMINAL, 0, PRIMARY, 0, src_lineno);
      ast_node *primary_node = create_ast_node(primary_info);
      ast_info *num_info = create_new_ast_node_info(NUM, tokenval, 0, lexbuf, src_lineno);
      ast_node *num_node = create_ast_node(num_info);

      add_child_node(primary_node, num_node);

      add_child_node(parent, primary_node);
      lookahead = lexan(fd);
  }else if(match(PUNCT, LP)){
    ast_info *primary_info = create_new_ast_node_info(NONTERMINAL, 0, PRIMARY, 0, src_lineno);
    ast_node *primary_node = create_ast_node(primary_info);

    ast_info *lp_info = create_new_ast_node_info(PUNCT, LP, 0, 0, src_lineno);
    ast_node *lp_node = create_ast_node(lp_info);

    add_child_node(primary_node, lp_node);

    lookahead = lexan(fd);

    expr(fd, primary_node);

    if(match(PUNCT, RP)){
      ast_info *rp_info = create_new_ast_node_info(PUNCT, RP, 0, 0, src_lineno);
      ast_node *rp_node = create_ast_node(rp_info);

      add_child_node(primary_node, rp_node);

      add_child_node(parent, primary_node);
      lookahead = lexan(fd);
    }else{
      parser_error(src_lineno);
    }
  }else{
    parser_error(src_lineno);

  }
}

void id_dec(FILE *fd, ast_node *parent){
  printf("id_dec\n");
  if(match(PUNCT, LP)){
    ast_info *id_dec_info = create_new_ast_node_info(NONTERMINAL, 0, IDDEC, 0, src_lineno);
    ast_node *id_dec_node = create_ast_node(id_dec_info);

    ast_info *lp_info = create_new_ast_node_info(PUNCT, LP, 0, 0, src_lineno);
    ast_node *lp_node = create_ast_node(lp_info);

    add_child_node(id_dec_node, lp_node);

    lookahead = lexan(fd);

    expr_list(fd, id_dec_node);

    if(match(PUNCT, RP)){
      ast_info *rp_info = create_new_ast_node_info(PUNCT, RP, 0, 0, src_lineno);
      ast_node *rp_node = create_ast_node(rp_info);

      add_child_node(id_dec_node, rp_node);

      add_child_node(parent, id_dec_node);
      lookahead = lexan(fd);
    } else{
      parser_error(src_lineno);
    }
  }else if(match(PUNCT, LB)){
    ast_info *id_dec_info = create_new_ast_node_info(NONTERMINAL, 0, IDDEC, 0, src_lineno);
    ast_node *id_dec_node = create_ast_node(id_dec_info);

    ast_info *lb_info = create_new_ast_node_info(PUNCT, LB, 0, 0, src_lineno);
    ast_node *lb_node = create_ast_node(lb_info);

    add_child_node(id_dec_node, lb_node);

    lookahead = lexan(fd);

    expr_zero(fd, id_dec_node);

    if(match(PUNCT, RB)){
      ast_info *rb_info = create_new_ast_node_info(PUNCT, RB, 0, 0, src_lineno);
      ast_node *rb_node = create_ast_node(rb_info);

      add_child_node(id_dec_node, rb_node);

      add_child_node(parent, id_dec_node);
      lookahead = lexan(fd);
    } else{
      parser_error(src_lineno);
    }
  }
}

void expr_list(FILE *fd, ast_node *parent){
  printf("expr_list\n");
  if(match(ID, 0)||match(UNOP,ASSIGN)||match(UNOP,NOT)||
    match(PUNCT,LP)||match(NUM, 0)){
    ast_info *expr_list_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRLIST, 0, src_lineno);
    ast_node *expr_list_node = create_ast_node(expr_list_info);
    expr_list_tail(fd, expr_list_node);
    add_child_node(parent, expr_list_node);
  }
}

void expr_list_tail(FILE *fd, ast_node *parent){
  printf("expr_list_tail\n");
  ast_info *expr_list_tail_info = create_new_ast_node_info(NONTERMINAL, 0, EXPRLISTTAIL, 0, src_lineno);
  ast_node *expr_list_tail_node = create_ast_node(expr_list_tail_info);
  expr(fd, expr_list_tail_node);
  tailfollow(fd, expr_list_tail_node);
  add_child_node(parent, expr_list_tail_node);
}

void tailfollow(FILE *fd, ast_node *parent){
  printf("tailfollow\n");

  if(match(PUNCT, COMMA)){
    ast_info *tailfollow_info = create_new_ast_node_info(NONTERMINAL, 0, TAILFOLLOW, 0, src_lineno);
    ast_node *tailfollow_node = create_ast_node(tailfollow_info);
    ast_info *comma_info = create_new_ast_node_info(PUNCT, COMMA, 0, 0, src_lineno);
    ast_node *comma_node = create_ast_node(comma_info);
    add_child_node(tailfollow_node, comma_node);
    lookahead = lexan(fd);
    expr_list_tail(fd, tailfollow_node);
    //lookahead = lexan(fd);
    add_child_node(parent, tailfollow_node);
  }
}
