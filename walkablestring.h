#ifndef WALKABLESTRING_H_
#define WALKABLESTRING_H_

#include <stddef.h>

typedef struct WalkableString {
    char* chars;
    size_t length;
    size_t current_idx;
} WalkableString;


/*
    Returns the char after current_idx
    Returns '\0' instead if there is no char there
*/
char peek(WalkableString* wstr_ptr);

/*
    Increments current_idx by 1 and returns it
    Returns 0 instead if current_idx is now out of bounds of the string
*/
size_t advance(WalkableString* wstr_ptr);

/*
    Returns the char at current_idx *unchecked*
*/
char get_current_char(WalkableString* wstr_ptr);

/*
    Returns the address current_idx points to *unchecked*
*/
char* get_current_location(WalkableString* wstr_ptr);

#endif