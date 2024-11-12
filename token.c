#include <stdlib.h>
#include <stdio.h>
#include "token.h"

#define GROWTH_COEFF 2


/*
    returns ptr to Token at given index, or NULL ptr if index out of bounds
*/
struct Token* get_token(struct TokenList* list_ptr, size_t idx);
/*
    adds token to end of TokenList, increasing TokenList->size if necessary
    updates TokenList->length
    returns length of TokenList or 0 if push failed
*/
size_t push_token(struct TokenList* list_ptr, struct Token* token_ptr);

/*
    create new token list, allocating enough memory for one element
*/
struct TokenList* new_token_list();
/*
    create new token list, function caller guarantees the token_ptr isn't NULL
*/
struct TokenList* token_list_from(struct Token* token_ptr, size_t size);





struct Token * get_token(struct TokenList* list_ptr, size_t idx) {
    if (idx >= list_ptr->length) {
        fprintf(stderr, "Index out of bounds");
        return NULL;
    }

    return list_ptr->tokens + idx;
}

size_t push_token(struct TokenList* list_ptr, struct Token* token_ptr) {
    // if we need to allocate more memory
    if ( (list_ptr->length + 1) * sizeof(struct Token) >= list_ptr->size ) {
        list_ptr->size *= GROWTH_COEFF;

        // allocate new memory
        struct Token* new_buf = (struct Token*)malloc(list_ptr->size);

        // check if malloc failed
        if (new_buf == NULL) {
            return 0;
        }

        // copy over list to new memory
        for (int i = 0; i < list_ptr->length; i++) {
            // i is guaranteed to be within the bounds of both
            // assuming i didn't make any mistakes
            new_buf[i] = list_ptr->tokens[i];
        }

        // do NOT forget to free your memory (attempt 2)
        free(list_ptr->tokens);
        list_ptr->tokens = new_buf;
    }

    // copy the new token into the list
    list_ptr->tokens[list_ptr->length] = *token_ptr;
    // update list length
    list_ptr->length += 1;

    return list_ptr->length;
}


struct TokenList* new_token_list() {
    struct TokenList* list = (struct TokenList*)malloc(sizeof(struct TokenList));

    list->tokens = (struct Token*)malloc(sizeof(struct Token));
    list->length = 0;
    list->size = sizeof(struct Token);

    return list;
}

struct TokenList* token_list_from(struct Token* token_ptr, size_t size) {
    struct TokenList* list = (struct TokenList*)malloc(sizeof(struct TokenList));

    list->tokens = token_ptr;
    list->length = size / sizeof(struct Token);
    list->size = size;

    return list;
}