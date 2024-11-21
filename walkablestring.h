#ifndef WALKABLESTRING_H_
#define WALKABLESTRING_H_

#include <stddef.h>

typedef struct WalkableString {
    char* chars;
    size_t length;
    size_t current_idx;
} WalkableString;

/*
    Increments current_idx by 1 and returns it
    Returns -1 instead if current_idx is now out of bounds of the string
*/
int advance(WalkableString* wstr_ptr);

/*
    Returns the char at current_idx *unchecked*
*/
char get_current_char(WalkableString* wstr_ptr);

/*
    Returns the address current_idx points to *unchecked*
*/
char* get_current_location(WalkableString* wstr_ptr);

#endif