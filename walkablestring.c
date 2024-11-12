#include "walkablestring.h"

char take(WalkableString* wstr_ptr) {
    if (wstr_ptr->length >= wstr_ptr->current_idx) {
        return 0;
    }

    return wstr_ptr->chars[wstr_ptr->current_idx++];
}

char peek(WalkableString* wstr_ptr) {
    // possibly remove later
    if (wstr_ptr->length >= wstr_ptr->current_idx) {
        return 0;
    }

    return wstr_ptr->chars[wstr_ptr->current_idx];
}


// char* taken(WalkableString* wtr_ptr, int n) {

// }

// char* peekn(WalkableString* wstr_ptr, int n) {

// }