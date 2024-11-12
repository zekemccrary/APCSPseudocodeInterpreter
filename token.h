#ifndef TOKEN_H_
#define TOKEN_H_

typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct TokenList TokenList;

Token * get_token(TokenList * list, int index);
int push_token(struct TokenList * list_ptr, struct Token * token_ptr);
struct TokenList * new_token_list();
struct TokenList * token_list_from(struct Token * token_ptr);

#endif