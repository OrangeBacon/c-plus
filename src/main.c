#include "input.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, const char* argv[]) {
  InputStream input;
  bool out = initInputStream(&input, "cmake_install.cmake");
  if(!out){
    printf("Failed to open file");
    return -1;
  }
  printf("%i",matchInputStream(&input,'j'));
  printf("%i",matchInputStream(&input,'#'));
  printf("%c",advanceInputStream(&input));
  printf("\nStart:\n");
  while(!isEndInputStream(&input)){
    printf("%c",advanceInputStream(&input));
  }
  printf("%i",advanceInputStream(&input));
  freeInputStream(&input);

  return 0;
}