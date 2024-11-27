#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"
#include "futils.h"

// this will be changed to command-line argument later
#define FILENAME "main.csp"

int main() {
    // this input will be taken from a file later
    char* temp_input = fcload(FILENAME);
    
    // create heap-allocated structures
    TokenList* list_ptr = parse_to_tokens(temp_input);
    char* list_str = token_list_to_str(list_ptr);

    printf("%s\n", list_str);

    // no memory leaks
    free(list_str);
    free_token_list(list_ptr);
    free(temp_input);

    return 0;
}