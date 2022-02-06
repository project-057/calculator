#include "string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

String NewString(const char* stroke)
{
    String string;
    string.size = strlen(stroke);
    string.string_ = AllocateString(string.size + 1);
    string.capacity_ = string.size + 1;
    strcpy(string.string_, stroke);
    return string;
}

char* AllocateString(int size)
{
    char* string = (char*)malloc(size * sizeof(char));
    return string;
}

void StringCopy(String from, String* const to)
{
    if (to->capacity_ < from.capacity_) {
        FreeString(to);
        to->capacity_ = from.size + 1;
        to->string_ = AllocateString(to->capacity_);
    }
    to->size = from.size;
    strcpy(to->string_, from.string_);
}

void Append(String* const string, char val)
{

    if (string->size + 1 >= string->capacity_) {
        IncreaseCapacity(string, string->capacity_ * 2);
    }
    string->string_[string->size++] = val;
    string->string_[string->size] = '\0';
}

char Pop(String* const string)
{
    assert(string->size != 0);
    return string->string_[--string->size];
}

char Top(String string)
{
    assert(string.size != 0);
    return string.string_[string.size - 1];
}

char At(String string, int index)
{
    if (index < 0 || index >= string.size)
        return '\0';

    return string.string_[index];
}

bool isEmpty(String string)
{
    return string.size == 0;
}

void ReverseString(String* val, int idx, int count)
{
    assert(idx + count <= val->size);

    char* string = val->string_;
    int n = val->size;
    for (int i = 0; i < count / 2; ++i) {
        char tmp = string[i + idx];
        string[i + idx] = string[idx + count - 1 - i];
        string[idx + count - 1 - i] = tmp;
    }
}

int Find(String string, char val)
{
    char* s = string.string_;
    for (int i = 0; i < string.size; ++i) {
        if (s[i] == val) {
            return i;
        }
    }
    return -1;
}

void FreeString(String* const val)
{
    free(val->string_);
    val->size = 0;
    val->capacity_ = 0;
}

void TrimString(String* const val)
{
    int pos = val->size - 1;
    if (val->string_[pos] == '\n') {
        val->string_[pos] = '\0';
        val->size--;
    }
}

void StringConcat(String* dest, String source)
{
    IncreaseCapacity(dest, dest->size + source.size + 1);
    strcpy(dest->string_ + dest->size, source.string_);
    dest->size += source.size;
}

void PrintLnString(String string)
{
    puts(string.string_);
}

void PrintString(String string)
{
    printf("%s", string.string_);
}

void IncreaseCapacity(String* const string, int expected_capacity)
{
    if (string->capacity_ < expected_capacity) {
        string->capacity_ = (string->capacity_ * 2 < expected_capacity ? expected_capacity : string->capacity_ * 2);
        char* new_string = AllocateString(string->capacity_);
        strcpy(new_string, string->string_);
        free(string->string_);
        string->string_ = new_string;
    }
}

void Erase(String* string, int idx, int count)
{
    assert(idx + count <= string->size);
    for (int i = 0; i + idx + count < string->size + 1; ++i) {
        string->string_[i + idx] = string->string_[i + idx + count];
    }
    string->size -= count;
}

void GetString(String* string)
{
    char s[MAX_INPUT_LEN];
    scanf("%s", s);
    *string = NewString(s);
}

void GetLine(String* string)
{
    char s[MAX_INPUT_LEN];
    fgets(s, MAX_INPUT_LEN, stdin);
    *string = NewString(s);
}

String SubString(String string, int idx, int count)
{
    assert(string.size >= idx + count);
    char new_str[MAX_INPUT_LEN];
    for (int i = 0; i < count; ++i) {
        new_str[i] = string.string_[i + idx];
    }
    new_str[count] = '\0';
    return NewString(new_str);
}

int FindSubString(String string, String val)
{
    assert(string.size >= val.size);
    for (int i = 0; i < string.size - val.size + 1; ++i) {
        bool mismatch = false;
        for (int j = 0; j < val.size; ++j) {
            if (At(string, i + j) != At(val, j)) {
                mismatch = true;
            }
        }
        if (!mismatch) {
            return i;
        }
    }
    return -1;
}

String StringToken(String string)
{
    static int pos = 0;
    for (int i = pos; i < string.size; ++i)
        if (At(string, i) != ' ') {
            pos = i;
            break;
        }

    int count = 0;
    for (int i = pos; i < string.size; ++i) {
        if (At(string, i) == ' ')
            break;
        count++;
    }

    String out = SubString(string, pos, count);
    pos += count;
    return out;
}

void ReplaceEl(String* string, int idx, char val)
{
    assert(idx < string->size && idx >= 0);
    string->string_[idx] = val;
}
