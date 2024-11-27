#include "futils.h"

#include <stdlib.h>
#include <stdio.h>

#define GB 1073741824

char* fcload(const char* fname) {
    // declare variables
    char* buf;
    size_t len;
    FILE* file = fopen(fname, "rb");
    size_t read_len;

    // first error check in my code that could actually happen!
    // figure out if I want to do errors later
    if (file == NULL) {
        fprintf(stderr, "File could not be opened");
        return NULL;
    }

    // find file length
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);

    // C standard is to accept up to 2 GB files but the stackoverflow guy did 1 GB so that's what we're doing
    if (len > GB) {
        fprintf(stderr, "File larger than 1 GB");
        return NULL;
    }

    // allocate memory
    buf = (char*)malloc(len + 1); // add one for the null byte

    // wouldn't have thought to check this damn
    if (len > 0) {
        read_len = fread(buf, sizeof(char), len, file);

        // or this lmao
        if (len != read_len) {
            free(buf);
            fprintf(stderr, "File read error");
            return NULL;
        }
    }

    (void)fclose(file);

    return buf;
}