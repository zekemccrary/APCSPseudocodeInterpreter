#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "walkablestring.h"

// change to accept a WalkableString later
TokenList* parse_str(WalkableString* wstr_ptr);

int main() {
    char* temp_input = "DISPLAY(\"HI\")";

    char* token_char = "(";

    Token new_token;
    new_token.kind = LPARENS;
    new_token.chars = token_char;
    new_token.line_number = 2;

    TokenList* list_ptr = new_token_list();
    push_token(list_ptr, &new_token);
    push_token(list_ptr, &new_token);
    push_token(list_ptr, &new_token);
    push_token(list_ptr, &new_token);

    printf("list: %lu elements, %lu bytes\n\n", list_ptr->length, list_ptr->size);


    printf("Token 1:\nkind: %d, chars: %s, line_number: %lu\n", (list_ptr->tokens[0]).kind, (list_ptr->tokens[0]).chars, (list_ptr->tokens[0]).line_number);
    printf("Token 2:\nkind: %d, chars: %s, line_number: %lu\n", (list_ptr->tokens[1]).kind, (list_ptr->tokens[1]).chars, (list_ptr->tokens[1]).line_number);
    printf("Token 3:\nkind: %d, chars: %s, line_number: %lu\n", (list_ptr->tokens[2]).kind, (list_ptr->tokens[2]).chars, (list_ptr->tokens[2]).line_number);
    printf("Token 4:\nkind: %d, chars: %s, line_number: %lu\n", (list_ptr->tokens[3]).kind, (list_ptr->tokens[3]).chars, (list_ptr->tokens[3]).line_number);


    free(list_ptr);

    return 0;
}

TokenList* parse_str(WalkableString* wstr_ptr) {
    // todo!
    return NULL;
}