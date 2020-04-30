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
char lexbuf[MAXLEXSIZE];
int  tokenval=0;          // stores current token's value
                          // (might not be used for every token)

char curr;
char next;
char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
          'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char bigAlphabets[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
          'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'v', 'w', 'x', 'y', 'z'};
char whitespace[7] = {' ', '\t', '\f', '\r' , '\t', '\n'};

char keywords[8][20] = {"break", "while", "writeln", "write", "read", "if", "else", "return"};

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
  curr = fgetc(fd);
  strcpy(lexbuf, "");
  for(int i = 0; i < MAXLEXSIZE-1; i++){
      char to_add[2];
      to_add[0] = curr;
      to_add[1] = '\0';
      strcat(lexbuf, to_add);
      next = fgetc(fd);
      int token = matches_token();
      if (token){
        return token;}
      else{
        curr = next;
      }
  } return (int) DONE;

}
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
static void print_lineno() {

  printf("line no = %d\n", src_lineno);

}

// static void populate_lexbuf(*fd){
//   if(lexbuf == ""){
//     for(i = 1; i < MAXLEXSIZE, i++){
//       c = fgetc(fd)
//       lexbuf[i] = c
//     }lexbuf[MAXLEXSIZE-1] = '\0'
//   } if strlen()
// }
static int check_membership(char val, char list[]){
  for (int i = 0; i < sizeof(list)/sizeof(list[0]); i++){
    if(list[i] == val){return 1;}
  }return 0;
}

static int compare(char val1[], char val2[]){
  int size1 = sizeof(val1)/sizeof(val1[0]);
  int size2 = sizeof(val2)/sizeof(val2[0]);
  int to_return = 0;
  if(size1 == size2){
    for (int i = 0; i < size1; i++){
      if(val1[i] != val2[i]){
        to_return = 1;
      }
    }
  }else{
    to_return= 1;
  }return to_return;
}

int matches_token(){

  //checking for comment
  char new[2];

  if(lexbuf[0] == '/' ){
    if(lexbuf[1] == '/'){
      //checks if the end of comment
      if(curr == '\n'){
        //clears the string in that case
        strcpy(lexbuf, "");
        return 0;
      }else{
        new[0] = curr;
        strcat(lexbuf, new);
        return 0;
      }
    }else if (lexbuf[1] == '*'){
      if (curr == '*' && next == '/') {
        strcpy(lexbuf, "");
        next = '\0';
        return 0;
      }else{
        new[0] = curr;
        new[1] = '\0';
        strcat(lexbuf, new);
        return 0;
      }
    }
  }if(curr == '\0'){
    return 0;
  }else if(check_membership(curr, whitespace)){
    return 0;
  }else if(curr == '/'){
    if(next == '/'||next == '*'){
      new[0] = curr;
      new[1] = '\0';
      strcat(lexbuf, new);
      return 0;
      new[0] = next;
      new[1] = '\0';
      strcat(lexbuf, new);
      return 0;

      next = '\0';

    }else{
      tokenval = DIVIDE;
      return BINOP;
    }
  }else if(curr == '*'){
    tokenval = MULTIPLY;
    return BINOP;
  }else if(curr == '+'){
    tokenval = PLUS;
    return BINOP;

  }else if(curr == '|'){
    if(next == '|'){
      next = '\0';
      tokenval = OR;
      return BINOP;
    }else{
      return LEXERROR;
    }
  }else if(curr == '&'){
    if(next == '&'){
      next = '\0';
      tokenval = AND;
      return BINOP;
    }else{
      return LEXERROR;
    }
  }else if(curr == '='){
    if(curr == '='){
      next = '\0';
      tokenval = E;
      return BINOP;
    }else{
      tokenval = ASSIGN;
      return UNOP;}
  }else if(curr == '<'){
    if(next == '='){
      next = '\0';
      tokenval = LE;
      return BINOP;
    }else{
      tokenval = LT;
      return BINOP;}
  }else if(curr == '>'){
    if(next == '='){
      next = '\0';
      tokenval = GE;
      return BINOP;
    }else{
      tokenval = GT;
      return BINOP;}
  }else if(curr == '!'){
    if(next == '='){
      next = '\0';
      tokenval = NE;
      return BINOP;
    }else{
      tokenval = NOT ;
      return UNOP;}
  }else if(curr == '{'){
    tokenval = LCB;
    return PUNCT;
  }else if(curr == '}'){
    tokenval = RCB;
    return PUNCT;
  }else if(curr == '('){
    tokenval = LP;
    return PUNCT;
  }else if(curr == ')'){
    tokenval = RP;
    return PUNCT;
  }else if(curr == '['){
    tokenval = LB;
    return PUNCT;
  }else if(curr == ']'){
    tokenval = RB;
    return PUNCT;
  }else if(curr == ';'){
    tokenval = SEMICOLON;
    return PUNCT;
  }else if(!check_membership(next, digits)|| !check_membership(next, alphabet) || !check_membership(next, bigAlphabets)){
    if(check_membership(curr, digits)){
      int plausible = atoi(lexbuf);
      if (compare(lexbuf, "0") != 0 && plausible == 0){
        return LEXERROR;
      }else{
        tokenval = plausible;
        return NUM;
      }
    }else if(check_membership(curr, alphabet)|| check_membership(curr, bigAlphabets)){
      if(compare(lexbuf, "break")== 0){
        return BREAK;
      }else if(compare(lexbuf, "read") == 0){
        return READ;
      }else if(compare(lexbuf, "write")== 0){
        return WRITE;
      }else if(compare(lexbuf, "writeln") == 0){
        return WRITELN;
      }else if(compare(lexbuf, "while") == 0){
        return WHILE;
      }else if(compare(lexbuf, "if") == 0){
        return IF;
      }else if(compare(lexbuf, "else") == 0){
        return ELSE;
      }else if(compare(lexbuf, "return") == 0){
        return RETURN;
      }else if(compare(lexbuf, "char") == 0){
        return CHAR;
      }else if(compare(lexbuf, "int") == 0){
        return INT;
      }else{
        return ID;
      }
    }else{
      return 0;
    }

  }else{
    new[0] = curr;
    new[1] = '\0';
    strcat(lexbuf, new);
    return 0;
  }
}
