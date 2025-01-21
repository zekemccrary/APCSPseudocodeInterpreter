#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stddef.h>

#include "token.h"


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




/*
    Tokenize string
    Returns TokenList pointer to dynamically allocated TokenList
    Remember to free memory at pointer address
*/
TokenList* parse_to_tokens(char* str);

/*
    Advances WalkableString->current_idx to next quote
    Returns number of characters advanced
*/
size_t find_string_len(WalkableString* wstr_ptr);

/*
    Advances WalkableString->current_idx to next non-alphanumberic character
    Returns number of characters advanced
*/
size_t find_number_len(WalkableString* wstr_ptr);

/*
    Advances WalkableString->current_idx to next non-alphanumberic non-underscore character
    Returns number of characters advanced
*/
size_t find_identifier_len(WalkableString* wstr_ptr);

/*
    Returns a pointer to a heap-allocated string representation of a TokenList
    meaning it NEEDS TO BE FREED don't forget
*/
char* token_list_to_str(TokenList* list_ptr);

#endif