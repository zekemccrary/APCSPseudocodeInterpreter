#include "walkablestring.h"

#include <stddef.h>

char peek(WalkableString* wstr_ptr) {
    if (wstr_ptr->current_idx >= wstr_ptr->length) {
        return '\0';
    }

    return wstr_ptr->chars[wstr_ptr->current_idx + 1];
}

size_t advance(WalkableString* wstr_ptr) {
    if (wstr_ptr->current_idx >= wstr_ptr->length) {
        return 0;
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