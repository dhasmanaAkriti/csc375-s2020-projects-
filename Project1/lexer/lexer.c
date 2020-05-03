/* Starter code provided to students */

/* The lexical analyzer for the C-- Programming Language
 */
// TODO: you are welcome to completely wipe out the contents of this
// file and start from scratch, or use this as your starting point.

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lexer.h"


// these are likely values that will be needed by the parser, so
// making them global variables is okay
char lexbuf[MAXLEXSIZE];  // stores current lexeme
char* string_so_far = "";
int  tokenval;          // stores current token's value                          // (might not be used for every token)
char curr;
char next;
int size = 1;

int  src_lineno=0;        // current line number in source code input


// function prototypes:
static void print_lineno();  // static limits its scope to only in this .c file

/***************************************************************************/
/*
 *  Main lexer routine:  returns the next token in the input
 *
 *  param fd: file pointer for reading input file (source C-- program)
 *            TODO: you may want to add more parameters
 *
 *  returns: the next token, or
 *           DONE if there are no more tokens, or
 *           LEXERROR if there is a token parsing error
 */
int lexan(FILE *fd) {

  // here is an example of how to use the debug macros defined in lexer.h
  //   uncomment #define DEBUG_LEXER, and recompile to see debug output
  //   comment #define DEBUG_LEXER, and recompile to see debug output
  //
  lexer_debug0("in lexan\n");
  lexer_debug1("in lexan, lineno = %d\n", src_lineno);
  lexer_debug1("in lexan, message = %s\n", "hello there");


  if(curr == EOF){
    return DONE;}
  else{
    curr = fgetc(fd);
    return matches_token(fd);
  }
}
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
static void print_lineno() {

  printf("line no = %d\n", src_lineno);

}

static int keyword_id(FILE *fd){
  next = fgetc(fd);
  // printf("%c\n", next );
  while ((next >= 'a' && next <= 'z') || (next >= 'A' && next <= 'Z') || (next >= '0' && next <= '9') || (next == '_')) {
    lexbuf[size-1] = curr;
    size = size + 1;
    curr = next;
    next = fgetc(fd);
  }
  lexbuf[size - 1] = curr;
  size = size + 1;

  ungetc(next, fd);
  if (curr >= '0' && curr <= '9'){
      tokenval = atoi(string_so_far);
      if(tokenval == 0){
        if(curr = '0'){
          return NUM;
        }else{
          return LEXERROR;
        }
      }else{
        return NUM;
      }
  }else{
  //  printf("%s\n", lexbuf);
    if(strcmp(lexbuf, "break")== 0){
      //printf("%s\n",lexbuf );
      return BREAK;
    }else if(strcmp(lexbuf, "read") == 0){
      return READ;
    }else if(strcmp(lexbuf, "write")== 0){
      return WRITE;
    }else if(strcmp(lexbuf, "writeln") == 0){
      return WRITELN;
    }else if(strcmp(lexbuf, "while") == 0){
      return WHILE;
    }else if(strcmp(lexbuf, "if") == 0){
      //printf("%s\n", lexbuf );
      return IF;
    }else if(strcmp(lexbuf, "else") == 0){
      return ELSE;
    }else if(strcmp(lexbuf, "return") == 0){
      return RETURN;
    }else if(strcmp(lexbuf, "char") == 0){
      return CHAR;
    }else if(strcmp(lexbuf, "int") == 0){
      //printf("%s\n", lexbuf);
      return INT;
    }else{
      return ID;
    }
  }
}

int matches_token(FILE *fd){
  lexbuf[0] = '\0';
  size = 1;

  switch (curr) {
    case '\n':
      curr = fgetc(fd);
      matches_token(fd);
      break;
    case '\t':
      curr = fgetc(fd);
      matches_token(fd);
      break;
    case ' ':
      curr = fgetc(fd);
      return matches_token(fd);
      break;
    case '\r':
      curr = fgetc(fd);
      return matches_token(fd);
      break;
    case '\f':
      curr = fgetc(fd);
      return matches_token(fd);
      break;
    case '*':
      tokenval = MULTIPLY;
      return BINOP;
      break;
    case '+':
      tokenval = PLUS;
      return BINOP;
      break;
    case '|':
      curr = fgetc(fd);
      if(next == '|'){
        tokenval = OR;
        return BINOP;
      }else{
        ungetc(curr, fd);
        return LEXERROR;
      }
      break;
    case '&':
      curr = fgetc(fd);
      if(curr == '&'){
        tokenval = AND;
        return BINOP;
      }else{
        ungetc(curr, fd);
        return LEXERROR;
      }
        break;
    case '=':
      curr = fgetc(fd);
      if(curr == '='){
        tokenval = E;
        return BINOP;
      }else{
        tokenval = ASSIGN;
        return UNOP;
      } break;
    case '<':
        curr = fgetc(fd);
        if(curr == '='){
          tokenval = LE;
          return BINOP;
        }else{
          ungetc(curr, fd);
          tokenval = LT;
          return BINOP;
        } break;

    case '>':
      curr = fgetc(fd);
      if(curr == '='){
        tokenval = GE;
        return BINOP;
      }else{
        ungetc(curr, fd);
        tokenval = GT;
        return BINOP;
      } break;
    case '!':
      curr = fgetc(fd);
      if(curr == '='){
        tokenval = NE;
        return BINOP;
      }else{
        ungetc(curr, fd);
        tokenval = NOT ;
        return UNOP;
      } break;
    case '{':
      tokenval = LCB;
      return PUNCT;
    case '}':
      tokenval = RCB;
      return PUNCT;
    case '(':
      tokenval = LP;
      return PUNCT;
      break;
    case ')':
      tokenval = RP;
      return PUNCT;
      break;
    case '[':
      tokenval = LB;
      return PUNCT;
      break;
    case ']':
      tokenval = RB;
      return PUNCT;
      break;
    case ';':
      tokenval = SEMICOLON;
      return PUNCT;
      break;
    case '/':
      curr = fgetc(fd);
      if (curr == '/'){
        curr = fgetc(fd);
        while (curr != '\n'){
          curr = fgetc(fd);
        }
        curr = fgetc(fd);
        return matches_token(fd);
      }else if (curr == '*'){
        curr = fgetc(fd);
        next = fgetc(fd);
        while (curr != '*' || next != '/'){
          curr = next;
          next = fgetc(fd);
        }
        curr = fgetc(fd);
        return matches_token(fd);
      } else{
        ungetc(curr, fd);
        tokenval = DIVIDE;
        return BINOP;
      }
      break;
    default:
      if((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z') || (curr >= '0' && curr <= '9') || (curr == '_')){
        return keyword_id(fd);
      }else{
        return LEXERROR;
      }
  }
}
