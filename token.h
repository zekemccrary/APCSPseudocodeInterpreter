#ifndef TOKEN_H_
#define TOKEN_H_

#include <stddef.h>

typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct TokenList TokenList;

Token* get_token(TokenList* list, size_t idx);
size_t push_token(struct TokenList* list_ptr, struct Token* token_ptr);
TokenList* new_token_list();
TokenList* token_list_from(struct Token* token_ptr, size_t size);


enum TokenType {
    LPARENS,
    RPARENS,
    LBRACE,
    RBRACE,
    PLUS,
    MINUS,
    ASTERISK,
    FSLASH,
    EQ,
    NEQ,
    GTHAN,
    LTHAN,
    GTEQ,
    LTEQ,
    COMMA,
    LBRACKET,
    RBRACKET,
    LARROW,
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
    STRING,
    NUMBER,
    IDENTIFIER
};

struct Token {
    enum TokenType kind;

    // NULL-terminated
    char* chars;

    // line number in file for errors
    size_t line_number;
};

struct TokenList {
    // ptr to first token in list
    struct Token* tokens;

    // # of elems
    size_t length;

    // in bytes
    size_t size;
};

#endif