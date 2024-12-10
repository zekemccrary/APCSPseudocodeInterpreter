#include "token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GROWTH_COEFF 2
#define MAX_TOKENTYPE_LENGTH 11

const int TOKENTYPE_LENGTHS[ENUM_COUNT] = {8, 8, 7, 7, 9, 9, 6, 3, 4, 5, 5, 5, 6, 9, 7, 6, 6, 7, 4, 4, 4, 3, 3, 5, 7, 6, 6, 4, 5, 3, 10, 5, 6, 8, 7, 7, 11, 8};
const char* TOKENTYPE_NAMES[ENUM_COUNT] = {"LPARENS", "RPARENS", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "EQ", "NEQ", "GTEQ", "LTEQ", "PLUS", "MINUS", "ASTERISK", "FSLASH", "GTHAN", "LTHAN", "LARROW", "MOD", "NOT", "AND", "OR", "IF", "ELSE", "REPEAT", "TIMES", "UNTIL", "FOR", "EACH", "IN", "PROCEDURE", "TRUE", "FALSE", "NEWLINE", "STRING", "NUMBER", "IDENTIFIER", "UNKNOWN"};




size_t push_token(struct TokenList* list_ptr, struct Token* token_ptr) {
    // if we need to allocate more memory
    if ( (list_ptr->count + 1) * sizeof(Token) >= list_ptr->capacity ) {
        size_t temp = list_ptr->capacity;
        list_ptr->capacity *= GROWTH_COEFF;

        // allocate new memory
        struct Token* new_buf = (struct Token*)malloc(list_ptr->capacity);

        // check if malloc failed
        if (new_buf == NULL) {
            return 0;
        }

        // copy over list to new memory
        for (int i = 0; i < list_ptr->count; i++) {
            // i is guaranteed to be within the bounds of both
            // assuming i didn't make any mistakes
            new_buf[i] = list_ptr->tokens[i];
        }

        // do NOT forget to free your memory (attempt 2)
        free(list_ptr->tokens);
        list_ptr->tokens = new_buf;
    }


    // copy the new token into the list
    list_ptr->tokens[list_ptr->count] = *token_ptr;
    // update list count
    list_ptr->count++;

    return list_ptr->count;
}


struct TokenList* token_list_with_capacity(size_t tokens) {
    struct TokenList* list = (struct TokenList*)malloc(sizeof(struct TokenList));

    list->tokens = (struct Token*)malloc(tokens * sizeof(struct Token*));
    list->count = 0;
    list->capacity = tokens * sizeof(struct Token*);

    return list;
}

struct TokenList* token_list_from(struct Token* token_ptr, size_t size) {
    struct TokenList* list = (struct TokenList*)malloc(sizeof(struct TokenList));

    list->tokens = token_ptr;
    list->count = size / sizeof(struct Token*);
    list->capacity = size;

    return list;
}

void free_token_list(TokenList* list_ptr) {
    // i hope this is how you're supposed to do this
    free(list_ptr->tokens);
    free(list_ptr);
}



size_t write_token_chars(Token* tok_ptr, char* buf) {
    // unchecked because the calling function should be allocating the perfect amount of memory already
    // if (tok_ptr->chars_length > buf_size) { return 0; }
    
    // use strncpy because strlcpy is not available everywhere
    // return separately because I don't trust strncpy to get the number of chars right (strlcpy didn't for some reason)
    (void)strncpy(buf, tok_ptr->chars, tok_ptr->chars_length + 1); // plus one for the null byte

    return tok_ptr->chars_length + 1;
}

size_t token_type_len(TokenType kind) {
    return TOKENTYPE_LENGTHS[kind];
}

size_t write_token_type(TokenType kind, char* buf) {
    strcpy(buf, TOKENTYPE_NAMES[kind]);
    return TOKENTYPE_LENGTHS[kind];
}


char* token_list_as_str(TokenList* list_ptr) {
    // calculate memory needed
    size_t len = 0;
    for (int i = 0; i < list_ptr->count; i++) {
        len += token_type_len(list_ptr->tokens[i].kind) - 1; // minus one because token_type_len includes the null byte
        len += list_ptr->tokens[i].chars_length;
        len += 6; // '(', '\"', '\"', ')', ',', ' '

        // displaying single-character '\n' as two-character string "\\n"
        if (list_ptr->tokens[i].kind == NEWLINE) {
            len++;
        }
    }
    // no trailing comma and space
    // len -= 2;

    // allocate memory
    char* buf_start = (char*)malloc(len * sizeof(char)); // sizeof(char) is 1 I think but better safe than sorry
    if (buf_start == NULL) { return NULL; }

    // write string
    Token* current_tok;
    size_t str_idx = 0;

    for (int i = 0; i < list_ptr->count; i++) {
        current_tok = &list_ptr->tokens[i];
        TokenType tkind = current_tok->kind;

        // TOKEN TYPE
        str_idx += write_token_type(tkind, buf_start + str_idx);
        buf_start[str_idx - 1] = '('; // minus one to overwrite the null byte from write_token_type
        buf_start[str_idx] = '\"';
        str_idx++;

        // TOKEN CHARS
        if (tkind == NEWLINE) {
            buf_start[str_idx] = '\\';
            buf_start[str_idx + 1] = 'n';
            str_idx += 3; // three because write_token_chars adds a null byte so this has to do that too
        } else {
            str_idx += write_token_chars(current_tok, buf_start + str_idx);
        }

        // CONNECTING TOKENS
        buf_start[str_idx - 1] = '\"'; // minus one overwrite the null byte from write_token_chars
        buf_start[str_idx] = ')';
        buf_start[str_idx + 1] = ',';
        buf_start[str_idx + 2] = tkind == NEWLINE ? '\n' : ' ';

        str_idx += 3;
    }

    buf_start[str_idx - 2] = '\0'; // remove trailing comma space

    return buf_start;
}