#include <stddef.h>
#include "walkablestring.h"


int advance(WalkableString* wstr_ptr) {
    if (wstr_ptr->current_idx >= wstr_ptr->length - 1) {
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