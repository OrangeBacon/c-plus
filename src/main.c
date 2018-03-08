#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "tokentype.h"

int main(int argc, const char* argv[]) {
  TokenList list;
  initTokenList(&list);
  addStringToken(&list, IDENTIFIER, "int", "int", 6);
  addStringToken(&list, IDENTIFIER, "main", "main", 6);
  printTokenList(&list);
  freeTokenList(&list);

  return 0;
}