#include "lexer.h"

//
// generates the lexer's output
//   t: the token
//   tval: token value
//
void lexer_emit(int t, int tval) {
  char operator[20];
  char Binary_operator[20];
  char Punctuation[20];

  switch(t) {
    case NUM:
      printf("NUM.%d\n", tval);
      break;
    case ID:
      printf("ID.%s\n", lexbuf);
      break;
  // Keyword
    case IF:
      printf("IF\n");
      break;
    case INT:
      printf("INT\n");
      break;
    case CHAR:
      printf("CHAR\n");
      break;
    case WHILE:
      printf("WHILE\n");
      break;
    case BREAK:
      printf("BREAK\n");
      break;
    case ELSE:
      printf("ELSE\n");
      break;
    case READ:
      printf("READ \n");
      break;
    case WRITE:
      printf("WRITE \n");
      break;
    case WRITELN:
      printf("WRITELN \n");
      break;
    case RETURN:
      printf("RETURN\n");
      break;
    case DONE:
      printf("%s\n", "DONE");
      break;
    case UNOP:
      if (tval == ASSIGN){
        char Binary_operatorp[20] = "ASSIGN";
      }else{
        char Binary_operator[20] = "NOT";
      }
      printf("UNOP.%s\n", Binary_operator);
      break;
    case BINOP:
      if (tval == PLUS){
        char operator[20] = "PLUS";
      }else if (tval == MINUS) {
        char operator[20] = "MINUS";
        /* code */
      } else if (tval == DIVIDE) {
        char operator[20] = "DIVIDE";
      } else if (tval == MULTIPLY) {
        char operator[20] = "MULTIPLY";
      }else if (tval == E) {
        char operator[20] = "E";
      }else if (tval == NE) {
        char operator[20] = "NE";
      }else if (tval == LT) {
        char operator[20] = "LT";
      }else if (tval == LE) {
        char operator[20] = "LE";
      }else if (tval == GT) {
        char operator[20] = "GT";
      } else if (tval == GE) {
        char operator[20] = "GE";
      }else if (tval == AND) {
        char operator[20]  = "AND";
      }else {
        char operator[20] = "OR";
      }
      printf("BINOP.%s\n", operator);
      break;
    case PUNCT:
      if (tval == LCB){
        char Punctuation[20] = "LCB";
      }else if (tval == RCB) {
        char Punctuation[20] = "RCB";
      }else if (tval == LB) {
        char Punctuation[20] = "LB";
      }else if (tval == RB) {
        char Punctuation[20] = "RB";
      }else if (tval == LP) {
        char Punctuation[20] = "LP";
      }else if (tval == RP) {
        char Punctuation[20] = "RP";
      }else if (tval == SEMICOLON) {
        char Punctuation[20] = "SEMICOLON";
      }else if (tval == COMMA) {
          char Punctuation[20] = "COMMA";
      }
      printf("PUNCT.%s\n", Punctuation );
      break;
    default:
      printf("token %s\n", curr);
      break;
  }
}
