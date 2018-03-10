#include <stdlib.h>
#include "token.h"
#include "memory.h"

void numberToken(Token* token, TokenType type, char* lexeme, int numLit, int line){
  token->type = type;
  token->lexeme = lexeme;
  token->numLit = numLit;
  token->unionType = TOKEN_NUMBER;
  token->line = line;
}

void stringToken(Token* token, TokenType type, char* lexeme, char* strLit, int line){
  token->type = type;
  token->lexeme = lexeme;
  token->strLit = strLit;
  token->unionType = TOKEN_STRING;
  token->line = line;
}

char tokenNameBuffer[1024]; // use buffer to avoid having to malloc and free string
const char* tokenToString(Token* token){
  tokenNameBuffer[0] = '\0';
  const char* typeName = TokenNames[token->type];
  snprintf(tokenNameBuffer, 1024, "%s(%s)", typeName, token->lexeme);
  return tokenNameBuffer;
}

void initTokenList(TokenList* tokenList){
  tokenList->count = 0;
  tokenList->capacity = 0;
  tokenList->tokens = NULL;
}

void addToken(TokenList* tokenList, Token* token){
  if(tokenList->capacity < tokenList->count + 1){
    int oldCapacity = tokenList->capacity;
    tokenList->capacity = GROW_CAPACITY(oldCapacity);
    tokenList->tokens = GROW_ARRAY(tokenList->tokens, Token*,
      oldCapacity, tokenList->capacity);
  }

  tokenList->tokens[tokenList->count] = token;
  tokenList->count++;
}

void addNumberToken(TokenList* tokenList, TokenType type, char* lexeme, int numLit, int line){
  // malloc new token, adding local variable is undefined behaviour
  Token* token = (Token*)malloc(sizeof(Token));
  numberToken(token, type, lexeme, numLit, line);
  addToken(tokenList, token);
}

void addStringToken(TokenList* tokenList, TokenType type, char* lexeme, char* strLit, int line){
  // malloc new token, adding local variable is undefined behaviour
  Token* token = (Token*)malloc(sizeof(Token));;
  stringToken(token, type, lexeme, strLit, line);
  addToken(tokenList, token);
}

Token* getToken(TokenList* tokenList, int idx){
  return tokenList->tokens[idx];
}

void freeTokenList(TokenList* tokenList){
  for(int i = 0; i < tokenList->count; i++){
    free(tokenList->tokens[i]); // free each token malloc'd in list
  }
  // realloc array to 0 size
  FREE_ARRAY(Token*, tokenList->tokens, tokenList->capacity);
  // set capacity and count to 0
  initTokenList(tokenList);
}

void printTokenList(TokenList* tokenList){
  printf("== TokenArray ==\n");
  for(int i = 0; i < tokenList->count; i++){
    printf("%i : %s\n", i, tokenToString(tokenList->tokens[i]));
  }
}
