#ifndef WALKABLESTRING_H_
#define WALKABLESTRING_H_

#include <stddef.h>

typedef struct WalkableString {
    char* chars;
    unsigned long length;
    unsigned long current_idx;
} WalkableString;

char take(WalkableString* wstr_ptr);
char peek(WalkableString* wstr_ptr);

// don't implement for now
// char* taken(WalkableString* wstr_ptr, size_t n);
// char* peekn(WalkableString* wstr_ptr, size_t n);

#endif