#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#define BASE_HT_SIZE 64
#define BASE_HASH_FUNC DJB2_HASH // maybe try xor version later
#define LOAD_FACTOR 0.75
#define REHASH_FACTOR 2
/* 
I don't know if load factor needs to be 0.75 in a linear probing scenario but i think it might
If it ends up being a problem i'll fix it later
*/


void test_hashtables() {
    int test_val = 13;
    size_t test_names_len = 129;
    char* test_names[] = {"x", "y", "z", "i", "j", "k", "reallySuperDuperLongVariableName", "mediumLengthName", "no_more_camel_case", "SCREAMING_SNAKE_CASE", "hi", "test_val", "int1", "int2", "int3", "int4", "int5", "int6", "int7", "int8", "int9", "int10", "a", "b", "c", "d", "e", "f", "size", "count", "num_collisions", "test_names_len", "x2", "y2", "z2", "i2", "j2", "k2", "reallySuperDuperLongVariableName2", "mediumLengthName2", "no_more_camel_case2", "SCREAMING_SNAKE_CASE2", "hi2", "test_val2", "int12", "int22", "int32", "int42", "int52", "int62", "int72", "int82", "int92", "int102", "a2", "b2", "c2", "d2", "e2", "f2", "size2", "count2", "num_collisions2", "test_names_len2", "x3", "y3", "z3", "i3", "j3", "k3", "reallySuperDuperLongVariableName3", "mediumLengthName3", "no_more_camel_case3", "SCREAMING_SNAKE_CASE3", "hi3", "test_val3", "int13", "int23", "int33", "int43", "int53", "int63", "int73", "int83", "int93", "int103", "a3", "b3", "c3", "d3", "e3", "f3", "size3", "count3", "num_collisions3", "test_names_len3", "bruh", "x4", "y4", "z4", "i4", "j4", "k4", "reallySuperDuperLongVariableName4", "mediumLengthName4", "no_more_camel_case4", "SCREAMING_SNAKE_CASE4", "hi4", "test_val4", "int14", "int24", "int34", "int44", "int54", "int64", "int74", "int84", "int94", "int104", "a4", "b4", "c4", "d4", "e4", "f4", "size4", "count4", "num_collisions4", "test_names_len4"};
    HashTable* test_ht = create_ht();
    printf("Created HashTable at %zu with elements at %zu of size %zu with %zu elements and %zu collisions\n", (size_t)test_ht, (size_t)test_ht->elements, test_ht->size, test_ht->count, test_ht->num_collisions);


    for (int i = 0; i < test_names_len; i++) {
        put_ht(test_ht, test_names[i], &test_val);
    }

    print_ht(test_ht);
}



// HASH FUNCTIONS

unsigned int DJB2_HASH(char* chars) {
    unsigned int hash = 5381;
    char c;

    while ((c = *chars++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

unsigned int DJB2XOR_HASH(char* chars) {
    unsigned int hash = 5381;
    char c;

    while ((c = *chars++)) {
        hash = ((hash << 5) + hash) ^ c; /* (hash * 33) ^ c */
    }

    return hash;
}

unsigned int SUPERFAST_HASH(char* chars) {
    // maybe later
    return 0;
}



// UTILITY FUNCTIONS

HashTable* create_ht() {
    return create_ht_ofsize(BASE_HT_SIZE);
}

HashTable* create_ht_ofsize(size_t size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));

    ht->elements = (HashElem*)malloc(size * sizeof(HashElem));;
    ht->size = size;
    ht->count = 0;
    ht->hash_ptr = &BASE_HASH_FUNC;
    ht->num_collisions = 0;

    return ht;
}

size_t put_ht(HashTable* ht, char* key, void* value) {
    // first thing we should really do is check the load factor of the hashtable
    if (ht->count > LOAD_FACTOR * ht->size) {
        rehash_ht(ht);
    }

    // ok moving on

    // save this for later
    size_t max = ht->size;
    // get hash value for key, modulus with HashTable size to stay within bounds
    unsigned int hashed = ht->hash_ptr(key) % max;
    // a value to stop at later
    unsigned int orig_hash_val = hashed;
    // current HashElem
    HashElem* he;


    for (; hashed <= max; hashed++) {
        // get HashElem at that index
        he = ht->elements + hashed; // &(ht->elements[hashed]);

        // if the key is null, then this is a new key that did not collide with anything
        // which is good. So just put the key value pair in and be done with it
        if (he->key == NULL) {
            ht->count++;

            he->key = key;
            he->value = value;
            return hashed;
        }
        // or if this element has the correct key
        // if it does then yay! we will just write in the new value and be done
        if (strcmp(key, he->key) == 0) {
            he->value = value;
            return hashed;
        }

        // unfortunately here neither of those cases were true and there was a collision :(
        ht->num_collisions++;

        // here we have to reset hashed and max if we have ended up reaching the end of the list
        if (hashed == ht->size) {
            hashed = 0;
            max = orig_hash_val - 1;
        }
    }
    

    // if we get here it really is unfortunate because something went very wrong with the LOAD_FACTOR and the table is full somehow
    return (size_t)(-1); // size_t::MAX_VAL
}

HashElem* get_ht_elem(HashTable* ht, char* key) {
    // this variable is gonna be used again later
    size_t max = ht->size;

    unsigned int hashed = ht->hash_ptr(key) % max;
    // this variable will also be used again later
    unsigned int orig_hash_val = hashed;

    HashElem* he = ht->elements + hashed;

    // in this scenario everything works out perfectly the first time
    if (strcmp(key, he->key) == 0) return he;
    // unfortunately not everybody gets what they want
    hashed++;

    // if it comes to this is the hashmap basically as bad as a normal array with way more overhead?
    for (; hashed <= max; hashed++) {
        he = ht->elements + hashed; // im addicted to pointer arithmetic

        if (strcmp(key, he->key) == 0) return he;

        // if end of hashtable reached start from the beginning
        if (hashed == ht->size) {
            hashed = 0;
            // but stop before we started earlier
            max = orig_hash_val - 1;
        }
    }

    // and if we don't find an element I guess just return NULL
    return NULL;
}

void free_ht(HashTable* ht) {
    free(ht->elements);
    free(ht);
}


// STATIC FUNCTIONS

static void rehash_ht(HashTable* old_ht) {
    HashTable* new_ht = create_ht_ofsize(REHASH_FACTOR * old_ht->size);

    HashElem* temp_elem;

    for (int i = 0; i < old_ht->size; i++) {
        temp_elem = old_ht->elements + i;

        if (temp_elem->key != NULL) {
            put_ht(new_ht, temp_elem->key, temp_elem->value);
        }
    }

    *old_ht = *new_ht;
}

static void print_ht(HashTable* ht) {
    printf("HashTable(%zu slots, %zu filled, %zu collision(s), LOAD_FACTOR: %f):\n{\n", ht->size, ht->count, ht->num_collisions, (double)ht->count / (double)ht->size);

    HashElem* temp_elem;

    for (int i = 0; i < ht->size; i++) {
        temp_elem = ht->elements + i;

        printf("\t%d:\t[", i);
        
        if (temp_elem->key != NULL) {
            printf("%s: @%zu,", temp_elem->key, (size_t)temp_elem->value);
        }

        printf("],\n");
    }

    printf("}\n");
}