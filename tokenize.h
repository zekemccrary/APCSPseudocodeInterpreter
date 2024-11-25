#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stddef.h>

#include "token.h"
#include "walkablestring.h"

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