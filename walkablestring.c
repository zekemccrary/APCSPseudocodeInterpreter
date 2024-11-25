#include "walkablestring.h"

#include <stddef.h>
#include <stdio.h>



char peek(WalkableString* wstr_ptr) {
    if (wstr_ptr->current_idx >= wstr_ptr->length) {
        return '\0';
    }

    return wstr_ptr->chars[wstr_ptr->current_idx + 1];
}

int advance(WalkableString* wstr_ptr) {
    if (wstr_ptr->current_idx >= wstr_ptr->length) {
        return -1;
    }

    wstr_ptr->current_idx += 1;
    return wstr_ptr->current_idx;
}

char get_current_char(WalkableString* wstr_ptr) {
    return wstr_ptr->chars[wstr_ptr->current_idx];
}

char* get_current_location(WalkableString* wstr_ptr) {
    return wstr_ptr->chars + wstr_ptr->current_idx;
}