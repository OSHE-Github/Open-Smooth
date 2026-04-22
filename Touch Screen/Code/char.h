#include <EEPROM.h>
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

//this file is the methods that allow you to use a char array as a string
//Author: Austin Deegan
//Date: 3/21/2026
//This file is in the public domain

//finds the index of a given char in a char array. if not found returns -1
int index(const char* in, char c, int start, int size){
  if(start<0)return -1;
  for(; start<size; start++){
    if(in[start]==c) return start;
  }
  return -1;
}

//fills out with a subset of in given the start and end indexse
void subchar(char* out, const char* in, int start, int end){
  if(start<0 || end<0 ){
    out[0] = 0;
    return;
  }
  for(int i = 0; i+start<end; i++){
    out[i]=in[i+start];
  }
  out[end-start] = 0;
}

//parses a char array to an int from the start and end index.
unsigned int toInt(const char* in, int start, int end){
  if(start<0 || end<0 )return 0;
  unsigned int out = 0;
  for(int i = 0; i+start<end; i++){
    out = out*10;
    out += in[i+start]-48;
  }
  return out;
}

//checks to see if two char arrays are equal until the size given
bool equal(const char* in, const char* test, int size){
  for(int i = 0; i <size; i++){
    if(in[i]!=test[i]) return 0;
  }
  return 1;
}

//turns a int to a char array
void intToChar(char* out, long in) {
  int i = 0;
  long ten = 1;

  while(ten*10<=in){
    ten = ten * 10;
  }
  
  while(ten>=1){
    out[i] = (in - in%ten)/ten+48; 
    in = (in)-(out[i]-48)*ten; 
    i++; 
    ten = ten / 10;
  }
  out[i] = 0; 
}

//adds the input char array to the output array at the location of null terminater
void charBuilder(char* out, const char* in){
  int i = 0;
  int j = 0;
  for(j = 0; out[j]!=0; j++) i = j + 1;
  for(j = 0; in[j]!=0; j++){
    out[i+j] = in[j];
  }
  out[j+i] = 0;

}


