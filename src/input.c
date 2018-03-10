#include "input.h"

bool initInputStream(InputStream* input, const char* path){
  input->pos = 0;
  input->col = 0;
  input->line = 1;
  input->path = path;
  input->file = fopen(path, "r");
  if(input->file==NULL){
    return false; // fail if file did not open
  }
  // goto end of file
  fseek(input->file, 0L, SEEK_END);
  // get index of current location in file (end) and store as file length
  input->length = (int)ftell(input->file);
  rewind(input->file); // goto start of file
  return true;
}

bool isEndInputStream(InputStream* input){
  return input->pos >= input->length;
}

void freeInputStream(InputStream* input){
  fclose(input->file);
}

int advanceInputStream(InputStream* input){
  input->pos++;
  int out = fgetc(input->file);
  if(out == EOF){
    return -1;
  }
  if(out=='\n'){ // new line - column 0, increase line count
    input->col = 0;
    input->line++;
  } else input->col++;
  return out;
}

int peekInputStream(InputStream* input){
  // get next character in file without advancing stream.
  if(input->pos+1 >= input->length){
    return -1;
  }
  int out = fgetc(input->file);
  fseek(input->file, -1, SEEK_CUR); // go back one character
  if(out == EOF){
    return -1;
  }
  return out;
}

int peekNextInputStream(InputStream* input){
  // like peek but with character after next
  if(input->pos+2 >= input->length){
    return -1;
  }
  fgetc(input->file);
  int out = fgetc(input->file);
  fseek(input->file, -2, SEEK_CUR);
  if(out == EOF){
    return -1;
  }
  return out;
}

bool matchInputStream(InputStream* input, char expected){
  // if peek is provided character consume it and return true
  // else do not consume and return false
  if(isEndInputStream(input)) return false;
  if(peekInputStream(input)!=expected) return false;
  advanceInputStream(input);
  return true;
}