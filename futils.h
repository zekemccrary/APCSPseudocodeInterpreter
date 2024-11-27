#ifndef FUTILS_H
#define FUTILS_H

/*
    Source: https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c
*/

/*
    Load contents of file into memory
    Returns a pointer to the beginning of the file contents
*/
char* fcload(const char* fname);

#endif