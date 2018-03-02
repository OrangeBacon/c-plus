#include "input.h"

bool initInputStream(InputStream* input, const char* path){
  input->pos = 0;
  input->col = 0;
  input->line = 1;
  input->path = path;
  input->file = fopen(path, "r");
  if(input->file==NULL){
    return false;
  }
  fseek(input->file, 0L, SEEK_END);
  input->length = (int)ftell(input->file);
  rewind(input->file);
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
  if(out=='\n'){
    input->col = 0;
    input->line++;
  } else input->col++;
  return out;
}

int peekInputStream(InputStream* input){
  if(input->pos+1 >= input->length){
    return -1;
  }
  int out = fgetc(input->file);
  fseek(input->file, -1, SEEK_CUR);
  if(out == EOF){
    return -1;
  }
  return out;
}

int peekNextInputStream(InputStream* input){
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
  if(isEndInputStream(input)) return false;
  if(peekInputStream(input)!=expected) return false;
  advanceInputStream(input);
  return true;
}