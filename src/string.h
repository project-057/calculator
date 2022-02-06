#pragma once
#include <stdbool.h>

#define MAX_INPUT_LEN 1000000

typedef struct String {
    int size;
    int capacity_;
    char* string_;
} String;

String NewString(const char* stroke);
char* AllocateString(int size);
void StringCopy(String from, String* const to);
void Append(String* const string, char val);
char Pop(String* const string);
char Top(String string);
char At(String string, int index);
bool isEmpty(String string);
void ReverseString(String* val, int idx, int count);
int Find(String string, char val);
int FindSubString(String string, String val);
void FreeString(String* const val);
void TrimString(String* const val);
void StringConcat(String* dest, String source);
int Size(const String* string);
void IncreaseCapacity(String* const string, int size);
void Erase(String* string, int idx, int count);
String SubString(String string, int idx, int count);
void ReplaceEl(String* string, int idx, char val);
