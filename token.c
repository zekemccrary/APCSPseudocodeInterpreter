#include <stddef.h>
#include <stdlib.h>
#include "token.h"

#define LIST_COEFF 2

enum TokenType {
    LPARENS,
    RPARENS,
    LBRACE,
    RBRACE,
    PLUS,
    MINUS,
    ASTERISK,
    FSLASH,
    EQ,
    NEQ,
    GTHAN,
    LTHAN,
    GTEQ,
    LTEQ,
    COMMA,
    LBRACKET,
    RBRACKET,
    LARROW,
    MOD,
    NOT,
    AND,
    OR,
    IF,
    ELSE,
    REPEAT,
    TIMES,
    UNTIL,
    FOR,
    EACH,
    IN,
    PROCEDURE,
    STRING,
    NUMBER,
    IDENTIFIER
};

struct Token {
    enum TokenType kind;

    // NULL-terminated
    char * chars;

    // line number in file for errors
    unsigned long line_number;
};

struct TokenList {
    // ptr to first token in list
    struct Token * tokens;

    // # of elems
    unsigned long length;

    // in bytes
    unsigned long size;
};

/* 
    Helper functions:
    
    get_token:
        returns ptr to Token at given index, or NULL ptr if index out of bounds

    push_token:
        adds token to end of TokenList, increasing TokenList->size if necessary
        updates TokenList->length
        returns length of TokenList or 0 if push failed

    pop_token:
        frees last element of the array
        updates TokenList->length
        returns the removed element or a NULL ptr if TokenList was empty

    new_token_list:
        create new token list, allocating enough memory for one element
    token_list_from:
        create new token list, function caller guarantees the token_ptr isn't NULL
*/
struct Token * get_token(struct TokenList * list_ptr, unsigned long idx);
int push_token(struct TokenList * list_ptr, struct Token * token_ptr);

struct TokenList * new_token_list();
struct TokenList * token_list_from(struct Token * token_ptr);




struct Token * get_token(struct TokenList * list_ptr, unsigned long idx) {
    if (idx >= list_ptr->length) {
        return NULL;
    }

    return &list_ptr->tokens[idx];
}

int push_token(struct TokenList * list_ptr, struct Token * token_ptr) {
    // if we need to allocate more memory
    if ( (list_ptr->length + 1) * sizeof(struct Token) >= list_ptr->size ) {
        // allocate new memory
        struct Token * new_buf = (struct Token *)malloc(LIST_COEFF * list_ptr->size);

        // copy over list to new memory
        for (int i = 0; i < list_ptr->length; i++) {
            // i is guaranteed to be within the bounds of both
            // assuming i didn't make any mistakes
            new_buf[i] = list_ptr->tokens[i];
            // do NOT forget to free your memory
            // this is how pointer arithmetic works right?
            free(list_ptr->tokens + i);
        }

        list_ptr->tokens = new_buf;
    }

    // copy the new token into the list
    list_ptr->tokens[list_ptr->length] = *token_ptr;
    // update list length
    list_ptr->length += 1;

    return list_ptr->length;
}


struct TokenList * new_token_list() {
    struct TokenList list;

    list.tokens = (struct Token *)malloc(sizeof(struct Token));
    list.length = 0;
    list.size = sizeof(struct Token);

    return &list;
}

struct TokenList * token_list_from(struct Token * token_ptr) {
    struct TokenList list;

    list.tokens = token_ptr;
    list.length = 1;
    list.size = sizeof(struct Token);

    return &list;
}