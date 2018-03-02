#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int pos;
  int line;
  int col;
  int length;
  const char* path;
  FILE* file;
} InputStream;

bool initInputStream(InputStream* input, const char* path);
bool isEndInputStream(InputStream* input);
void freeInputStream(InputStream* input);
int advanceInputStream(InputStream* input);
int peekInputStream(InputStream* input);
int peekNextInputStream(InputStream* input);
bool matchInputStream(InputStream* input, char expected);

#endif // INPUT_H