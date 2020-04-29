#include "lexer.h"
//
// generates the lexer's output
//   t: the token
//   tval: token value
//
void lexer_emit(int t, int tval) {

  switch(t) {
    case NUM:
      printf("NUM.%d\n", tval);
    case ID:
      printf("ID.%s\n", string_so_far );
  // Keyword
    case IF:
      printf("IF\n");
      break;
    case INT:
      printf("INT\n")
    case CHAR:
      printf("CHAR\n", );
    case WHILE:
      printf("WHILE\n")
      break;
    case BREAK:
      printf("BREAK\n");
    case ELSE:
      printf("ELSE\n");
    case READ:
      printf("READ \n");
    case WRITE:
      printf("WRITE \n");
    case WRITELN:
      printf("WRITELN \n");
    case RETURN:
      printf("RETURN")
    case UNOP:
      char Binary_operator[]
      if (tval == ASSIGN)) {
        operator = "ASSIGN"
      }else{
        operator = "NOT"
      }
      printf("UNOP.%s\n", Binary_operator);
    case BINOP:
      char operator[]
      if (tval == PLUS){
        operator = "PLUS"
      }else if (tval == MINUS) {
        operator = "MINUS"
        /* code */
      } else if (tval == DIVIDE) {
        operator = "DIVIDE"
      } else if (tval == MULTIPLY) {
        operator = "MULTIPLY"
      }else if (tval == E) {
        operator = "E"
      }else if (tval == NE) {
        operator = "NE"
      }else if (tval == LT) {
        operator = "LT"
      }else if (tval == LE) {
        operator = "LE"
      }else if (tval == GT) {
        operator = "GT"
      } else if (tval == GE) {
        operator = "GE"
      }else if (tval == AND) {
        operator = "AND"
      }else {
        operator = "OR"
      }
      printf("BINOP.%d\n" operator)
    case PUNCT:
      char punctuation[]
      if (tval == LCB){
        operator = "LCB"
      }else if (tval == RCB) {
        operator = "RCB"
      }else if (tval == LB) {
        operator = "LB"
      }else if (tval == RB) {
        operator = "RB"
      }else if (tval == LP) {
        operator = "LP"
      }else if (tval == RP) {
        operator = "RP"
      }else if (tval == SEMICOLON) {
      operator = "SEMICOLON"
      }
      printf("PUNCT.%s\n", punctuation );
    default:
      printf("token %c\n", letter);
      break;
  }
}
