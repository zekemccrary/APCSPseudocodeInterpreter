typedef enum TokenType {
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
} TokenType;

typedef struct Token {
    TokenType kind;
    char * chars;
    unsigned int chars_length;
    int line_number;
} Token;

typedef struct {
    Token * tokens;
    unsigned int length;
} TokenList;


int main() {
    char * temp_input = "DISPLAY(\"HI\")";

    

    return 0;
}