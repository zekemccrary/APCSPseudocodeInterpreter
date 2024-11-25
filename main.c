#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"



int main() {
    // this input will be taken from a file later
    char* temp_input = "DISPLAY(\"HI There\"+34+456)\nx<-1\ny<-RANDOM(0,10)\nz <- \"why me\"\n";
    

    // create heap-allocated structures
    TokenList* list_ptr = parse_to_tokens(temp_input);
    char* list_str = token_list_to_str(list_ptr);

    printf("%s\n", list_str);

    // no memory leaks
    free(list_str);
    free_token_list(list_ptr);

    return 0;
}