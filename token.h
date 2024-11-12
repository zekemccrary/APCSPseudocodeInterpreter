#ifndef TOKEN_H_
#define TOKEN_H_

typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct TokenList TokenList;

Token* get_token(TokenList* list, unsigned long idx);
unsigned long push_token(struct TokenList* list_ptr, struct Token* token_ptr);
TokenList* new_token_list();
TokenList* token_list_from(struct Token* token_ptr, unsigned long size);


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
    unsigned long line_number;
};

struct TokenList {
    // ptr to first token in list
    struct Token* tokens;

    // # of elems
    unsigned long length;

    // in bytes
    unsigned long size;
};

#endif