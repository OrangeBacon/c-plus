#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include <stdio.h>
#include "tokentype.h"

typedef enum { // tagged union type
  TOKEN_NUMBER, TOKEN_STRING
} TokenUnionType;

typedef struct {
  TokenType type;
  char* lexeme;
  // tagged union
  TokenUnionType unionType;
  union {
    int numLit;
    char* strLit;
  };
  int line;
} Token;

void numberToken(Token* Token, TokenType type, char* lexeme, int numLit, int line);
void stringToken(Token* token, TokenType type, char* lexeme, char* strLit, int line);
const char* tokenToString(Token* token);

typedef struct {
  int count;
  int capacity;
  Token** tokens;
} TokenList;

void initTokenList(TokenList* tokenList);
void addToken(TokenList* tokenList, Token* token);

// wrappers around numberToken and stringToken
void addNumberToken(TokenList* tokenList, TokenType type, char* lexeme, int numLit, int line);
void addStringToken(TokenList* tokenList, TokenType type, char* lexeme, char* strLit, int line);
Token* getToken(TokenList* tokenList, int idx);
void freeTokenList(TokenList* tokenList);

void printTokenList(TokenList* tokenList);

#endif // TOKEN_H