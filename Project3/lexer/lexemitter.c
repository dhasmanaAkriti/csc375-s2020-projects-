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
      printf("ID.%c\n", tval );
  // Keyword
    case IF:
      printf("IF\n");
      break;
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
      printf("UNOP.%c\n", tval )
    case BINOP:
      printf("BINOP.%c\n" tval)
    default:
      printf("token %c\n", tval);
      break;
  }
}
