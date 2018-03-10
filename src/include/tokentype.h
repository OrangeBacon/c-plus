#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

// list of all token types
#define FOR_EACH_TOKEN(gen) \
  gen(LEFT_BRACE) gen(RIGHT_BRACE) \
  gen(LEFT_BRACKET) gen(RIGHT_BRACKET) \
  gen(SEMICOLON) \
  gen(IDENTIFIER) gen(NUMBER) \
  gen(RETURN)

#define GEN_ENUM(NAME) NAME,

#define GEN_STRING_ARR(NAME) #NAME,

// Enum of all tokens
typedef enum {
  FOR_EACH_TOKEN(GEN_ENUM)
} TokenType;

// String list of all tokens
static const char* TokenNames[] = {
  FOR_EACH_TOKEN(GEN_STRING_ARR)
};

#endif // TOKEN_TYPE_H