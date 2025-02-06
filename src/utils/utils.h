#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>


/*  FUTILS  */
/* –––––––– */
/*
    Source: https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c

    Load contents of file into memory
    Returns a pointer to the beginning of the file contents
*/
char* fcload(const char* fname);



/*  WALKABLESTRING  */
/* –––––––––––––––– */

typedef struct WalkableString {
    char* chars;
    size_t length;
    size_t current_idx;
} WalkableString;


/*
    Returns the char after current_idx
    Returns '\0' instead if there is no char there
*/
char peek(WalkableString* wstr_ptr);

/*
    Increments current_idx by 1 and returns it
    Returns 0 instead if current_idx is now out of bounds of the string
*/
size_t advance(WalkableString* wstr_ptr);

/*
    Returns the char at current_idx *unchecked*
*/
char get_current_char(WalkableString* wstr_ptr);

/*
    Returns the address current_idx points to *unchecked*
*/
char* get_current_location(WalkableString* wstr_ptr);



/*   STR HASHTABLE   */
/* –––––––––––––––––– */


/*
    Run tests on functions from hashtable.c file
    Print the results of the tests
*/
void test_hashtables();


typedef struct HashElem {
    char* key;
    void* value;
} HashElem;

typedef struct HashTable {
    HashElem* elements;
    size_t size;
    size_t count;
    unsigned int (*hash_ptr)(char*);
    // debug information and because i wanna know
    // probably gonna be annoying to remove later but who cares
    size_t num_collisions;
} HashTable;



// HASH FUNCTIONS

/*
    DJB2 hash
    Old, commonly used string hash function because it is easy to write and fairly effective 
*/
unsigned int DJB2_HASH(char* chars);

/*
    Xor variant of DJB2 hash
*/
unsigned int DJB2XOR_HASH(char* chars);

/*
    SuperFastHash by Paul Hsieh
    https://www.azillionmonkeys.com/qed/hash.html
*/
unsigned int SUPERFAST_HASH(char* chars);



// UTILITY FUNCTIONS

/*
    Creates an empty hashtable using `BASE_SIZE` and `BASE_HASH_FUNC`
    the hashtable MUST be freed by the caller
*/
HashTable* create_ht();

/*
    Creates an empty hashtable using `size` and `BASE_HASH_FUNC`
    the hashtable MUST be freed by the caller
*/
HashTable* create_ht_ofsize(size_t size);

/*
    Adds a key-value pair to the `HashTable`, or updates an existing pair if the key has already been added
    Returns index of `HashElem` that was modified
    figure out error value later
*/
size_t put_ht(HashTable* ht, char* key, void* value);

/*
    return the `HashElem` that contains key
*/
HashElem* get_ht_elem(HashTable* ht, char* key);

/*
    Free `HashTable` and all `HashElem`s
*/
void free_ht(HashTable* ht);



// STATIC FUNCTIONS

/*
    Replaces old `HashTable` with new `HashTable` containing all pairs from the passed in `HashTable`, but with twice the capacity
*/
static void rehash_ht(HashTable* old_ht);

/*
    Print `HashTable` in dictionary format
*/
static void print_ht(HashTable* ht);



#endif