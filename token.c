#include "token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GROWTH_COEFF 2



struct Token * get_token(struct TokenList* list_ptr, size_t idx) {
    if (idx >= list_ptr->count) {
        fprintf(stderr, "Index out of bounds");
        return NULL;
    }

    return list_ptr->tokens + idx;
}

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


struct TokenList* new_token_list() {
    return token_list_with_capacity(1);
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
    
    // use strlcpy because it will append a null byte to buf and returns the size of the written string
    // however strlcpy won't return the right length, probably because of the lack of null byte, so we return separately
    (void)strlcpy(buf, tok_ptr->chars, tok_ptr->chars_length + 1); // plus one for the null byte

    return tok_ptr->chars_length + 1;
}

size_t token_type_len(TokenType kind) {
    switch (kind) {
        case LPARENS:
            return 8;
        case RPARENS:
            return 8;
        case LBRACE:
            return 7;
        case RBRACE:
            return 7;
        case LBRACKET:
            return 9;
        case RBRACKET:
            return 9;
        case COMMA:
            return 6;
        case EQ:
            return 3;
        case NEQ:
            return 4;
        case GTEQ:
            return 5;
        case LTEQ:
            return 5;
        case PLUS:
            return 5;
        case MINUS:
            return 6;
        case ASTERISK:
            return 9;
        case FSLASH:
            return 7;
        case GTHAN:
            return 6;
        case LTHAN:
            return 6;
        case LARROW:
            return 7;
        case MOD:
            return 4;
        case NOT:
            return 4;
        case AND:
            return 4;
        case OR:
            return 3;
        case IF:
            return 3;
        case ELSE:
            return 5;
        case REPEAT:
            return 7;
        case TIMES:
            return 6;
        case UNTIL:
            return 6;
        case FOR:
            return 4;
        case EACH:
            return 5;
        case IN:
            return 3;
        case PROCEDURE:
            return 10;
        case NEWLINE:
            return 8;
        case STRING:
            return 7;
        case NUMBER:
            return 7;
        case IDENTIFIER:
            return 11;
        case UNKNOWN:
            return 8;
    }

    return 0;
}

size_t write_token_type(TokenType kind, char* buf) {
    switch (kind) {
        // this is where you would use strcpy isnt it
        case LPARENS:
            strcpy(buf, "LPARENS");
            return 8;
        case RPARENS:
            strcpy(buf, "RPARENS");
            return 8;
        case LBRACE:
            strcpy(buf, "LBRACE");
            return 7;
        case RBRACE:
            strcpy(buf, "RBRACE");
            return 7;
        case LBRACKET:
            strcpy(buf, "LBRACKET");
            return 9;
        case RBRACKET:
            strcpy(buf, "RBRACKET");
            return 9;
        case COMMA:
            strcpy(buf, "COMMA");
            return 6;
        case EQ:
            strcpy(buf, "EQ");
            return 3;
        case NEQ:
            strcpy(buf, "NEQ");
            return 4;
        case GTEQ:
            strcpy(buf, "GTEQ");
            return 5;
        case LTEQ:
            strcpy(buf, "LTEQ");
            return 5;
        case PLUS:
            strcpy(buf, "PLUS");
            return 5;
        case MINUS:
            strcpy(buf, "MINUS");
            return 6;
        case ASTERISK:
            strcpy(buf, "ASTERISK");
            return 9;
        case FSLASH:
            strcpy(buf, "FSLASH");
            return 7;
        case GTHAN:
            strcpy(buf, "GTHAN");
            return 6;
        case LTHAN:
            strcpy(buf, "LTHAN");
            return 6;
        case LARROW:
            strcpy(buf, "LARROW");
            return 7;
        case MOD:
            strcpy(buf, "MOD");
            return 4;
        case NOT:
            strcpy(buf, "NOT");
            return 4;
        case AND:
            strcpy(buf, "AND");
            return 4;
        case OR:
            strcpy(buf, "OR");
            return 3;
        case IF:
            strcpy(buf, "IF");
            return 3;
        case ELSE:
            strcpy(buf, "ELSE");
            return 5;
        case REPEAT:
            strcpy(buf, "REPEAT");
            return 7;
        case TIMES:
            strcpy(buf, "TIMES");
            return 6;
        case UNTIL:
            strcpy(buf, "UNTIL");
            return 6;
        case FOR:
            strcpy(buf, "FOR");
            return 4;
        case EACH:
            strcpy(buf, "EACH");
            return 5;
        case IN:
            strcpy(buf, "IN");
            return 3;
        case PROCEDURE:
            strcpy(buf, "PROCEDURE");
            return 10;
        case NEWLINE:
            strcpy(buf, "NEWLINE");
            return 8;
        case STRING:
            strcpy(buf, "STRING");
            return 7;
        case NUMBER:
            strcpy(buf, "NUMBER");
            return 7;
        case IDENTIFIER:
            strcpy(buf, "IDENTIFIER");
            return 11;
        case UNKNOWN:
            strcpy(buf, "UNKNOWN");
            return 8;
            
    }

    return 0;
}


char* token_list_as_str(TokenList* list_ptr) {
    // calculate memory needed
    size_t len = 0;
    for (int i = 0; i < list_ptr->count; i++) {
        len += token_type_len(list_ptr->tokens[i].kind) - 1; // minus one because token_type_len includes the null byte
        len += list_ptr->tokens[i].chars_length;
        len += 6; // '(', '\"', '\"', ')', ',', ' '
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

        str_idx += write_token_type(current_tok->kind, buf_start + str_idx);
        buf_start[str_idx - 1] = '('; // minus one to overwrite the null byte from write_token_type
        buf_start[str_idx] = '\"';
        str_idx++;

        str_idx += write_token_chars(current_tok, buf_start + str_idx);
        buf_start[str_idx - 1] = '\"'; // minus one overwrite the null byte from write_token_chars
        buf_start[str_idx] = ')';
        str_idx++;

        buf_start[str_idx] = ',';
        buf_start[str_idx + 1] = ' ';
        str_idx += 2;
    }

    buf_start[str_idx - 2] = '\0'; // remove trailing comma

    return buf_start;
}