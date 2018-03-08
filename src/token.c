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

const char* tokenToString(Token* token){
  const char* typeName = TokenNames[token->type];
  int typeNameLen = strlen(typeName);
  return typeName;
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
  Token token;
  numberToken(&token, type, lexeme, numLit, line);
  addToken(tokenList, &token);
}

void addStringToken(TokenList* tokenList, TokenType type, char* lexeme, char* strLit, int line){
  Token token;
  stringToken(&token, type, lexeme, strLit, line);
  addToken(tokenList, &token);
}

Token* getToken(TokenList* tokenList, int idx){
  return tokenList->tokens[idx * sizeof(Token)];
}

void freeTokenList(TokenList* tokenList){
  FREE_ARRAY(Token*, tokenList->tokens, tokenList->capacity);
  initTokenList(tokenList);
}

void printTokenList(TokenList* tokenList){
  printf("== TokenArray ==\n");
  for(int i = 0; i < tokenList->count * sizeof(Token); i++){
    printf("%s\n", tokenToString(tokenList->tokens[i]));
  }
}
