#ifndef TOKEN_H_
#define TOKEN_H_

#include <stddef.h>

typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct TokenList TokenList;

/*
    Returns ptr to Token at given index, or NULL ptr if index out of bounds
*/
Token* get_token(TokenList* list, size_t idx);
/*
    Adds token to end of TokenList, increasing TokenList->capacityif necessary
    Updates TokenList->count
    Returns count of TokenList or 0 if push failed
*/
size_t push_token(TokenList* list_ptr, Token* token_ptr);
/*
    Create new token list, allocating enough memory for one element
*/
TokenList* new_token_list();
/*
    Create new token list, allocating enough memory for tokens tokens
*/
TokenList* token_list_with_capacity(size_t tokens);
/*
    Create new token list without allocating memory for token_ptr, function caller guarantees the token_ptr isn't NULL
*/
TokenList* token_list_from(Token* token_ptr, size_t size);
/*
    Frees memory of all tokens in list, then the list itself
*/
void free_token_list(TokenList* list_ptr);

/*
    Returns a pointer to a heap-allocated string representation of a TokenList
    meaning it NEEDS TO BE FREED don't forget
*/
char* token_list_as_str(TokenList* list_ptr);
/*
    Writes a string representation of a Token to buf, returning the string length
    Buf should be at least Token->chars_length + 1 bytes to make room for the null byte
*/
size_t write_token_chars(Token* tok_ptr, char* buf);
/*
    to_string() method for TokenType
    buf needs to be 11 characters because that's the largest size the token name could be
    Returns size of string written to buf
    Remember to make buf large enough because I don't know how to check that in the function
    Change to use strcpy later
    Please dont read this function code
*/
size_t write_token_type(TokenType kind, char* buf);


enum TokenType {
    // single-character tokens
    LPARENS,
    RPARENS,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    COMMA,
    EQ,
    NEQ,
    GTEQ,
    LTEQ,
    PLUS,
    MINUS,
    ASTERISK,
    FSLASH,

    // possible double-character tokens
    GTHAN,
    LTHAN,
    LARROW,

    // keywords
    MOD,
    NOT,
    AND,
    OR,
    IF,
    ELSE,
    REPEAT,
    TIMES,
    UNTIL,
    FOR,
    EACH,
    IN,
    PROCEDURE,

    // other
    NEWLINE,
    STRING,
    NUMBER,
    IDENTIFIER,
    UNKNOWN
};


struct Token {
    enum TokenType kind;

    // NOT NULL-terminated
    char* chars;
    size_t chars_length;

    // line number in file for errors
    size_t line_number;
};

struct TokenList {
    // ptr to first token in list
    struct Token* tokens;

    // # of elems
    size_t count;

    // in bytes
    size_t capacity;
};

#endif