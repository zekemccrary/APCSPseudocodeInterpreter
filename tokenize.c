#include "tokenize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "walkablestring.h"

#define NUM_IDENTIFIERS 13



TokenList* parse_to_tokens(char* str) {
    /*
        VARIABLE DEFINITIONS:
    */

    // wstr
    WalkableString wstr;
    wstr.chars = str;
    wstr.length = strlen(str);
    wstr.current_idx = 0;

    // identifiers
    TokenType identifiers[] =  {MOD, NOT, AND, OR, IF, ELSE, REPEAT, TIMES, UNTIL, FOR, EACH, IN, PROCEDURE};
    //char** identifier_names = {"MOD", "NOT", "AND", "OR", "IF", "ELSE", "REPEAT", "TIMES", "UNTIL", "FOR", "EACH", "IN", "PROCEDURE"};
    // should I return NULL here or an empty list?
    if (wstr.length == 0 || wstr.chars == NULL) { fprintf(stderr, "null list"); return token_list_from(NULL, 0); }

    // spaces
    size_t spaces = 0;
    // count the number of spaces to estimate how much memory we will need
    // is this a good idea?
    for (int i = 0; i < wstr.length; i++) {
        spaces += (size_t) (wstr.chars[i] == ' ');
    }

    // list_ptr
    // remember to free this please
    TokenList* list_ptr = token_list_with_capacity(spaces);
    // always good to check
    if ( list_ptr == NULL) { fprintf(stderr, "list malloc failed"); return list_ptr; }

    // token fields
    TokenType kind;
    size_t chars_length = 1;
    size_t line_number = 0;



    /*
        LOOP OVER CHARACTERS:
    */

    // loop variables
    char* current_ref;
    char currentc;
    size_t at_end_of_str = wstr.length; // if length is 0 the loop won't run otherwise it will

    while (at_end_of_str != 0) {
        // instantiate / update variables
        current_ref = get_current_location(&wstr);
        currentc = get_current_char(&wstr);
        at_end_of_str = advance(&wstr);
        if (at_end_of_str == 0) { break; } // have to add this check because I moved variable updating to the top of the loop

        switch(currentc) {
            // skip spaces
            case ' ':
                continue; // continue to not add a token

            // increment line number
            case '\n':
                kind = NEWLINE;
                chars_length = 1;
                line_number++;
                break; // should newline have a token? I think so

            // numbers
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                kind = NUMBER;
                chars_length = find_number_len(&wstr);
                break;

            // strings
            case '\"':
                kind = STRING;
                chars_length = find_string_len(&wstr);
                // skip first quote
                current_ref += 1;
                break;
            
            // single characters
            case '(':
                kind = LPARENS;
                chars_length = 1;
                break;
            case ')':
                kind = RPARENS;
                chars_length = 1;
                break;
            case '{':
                kind = LBRACE;
                chars_length = 1;
                break;
            case '}':
                kind = RBRACE;
                chars_length = 1;
                break;
            case '[':
                kind = LBRACKET;
                chars_length = 1;
                break;
            case ']':
                kind = RBRACKET;
                chars_length = 1;
                break;
            case ',':
                kind = COMMA;
                chars_length = 1;
                break;
            case '=':
                kind = EQ;
                chars_length = 1;
                break;
            case '+':
                kind = PLUS;
                chars_length = 1;
                break;
            case '-':
                kind = MINUS;
                chars_length = 1;
                break;
            case '*':
                kind = ASTERISK;
                chars_length = 1;
                break;
            case '/':
                kind = FSLASH;
                chars_length = 1;
                break;
            /* 
            // these will be represented by 8-bit ascii codes generated by a preprocessor
            // todo!
            case NEQ:
                kind = NEQ;
                chars_length = 1;
                break;
            case GTEQ:
                kind = GTEQ;
                chars_length = 1;
                break;
            case LTEQ:
                kind = LTEQ;
                chars_length = 1;
                break;
            */

            // possibly double characters
            case '>':
                if (get_current_char(&wstr) == '=') {
                    kind = GTEQ;
                    chars_length = 2;
                }
                else {
                    kind = GTHAN;
                    chars_length = 1;
                }
                break;
            case '<':
                if (get_current_char(&wstr) == '=') {
                    kind = GTEQ;
                    chars_length = 2;
                    // skip the '=' because it is part of the token
                    (void)advance(&wstr);
                }
                else if (get_current_char(&wstr) == '-') {
                    kind = LARROW;
                    chars_length = 2;
                    // skip the '-' because it is part of the token
                    (void)advance(&wstr);
                }
                else {
                    kind = LTHAN;
                    chars_length = 1;
                }
                break;
            
            // everything else is parsed as an identifier or an unknown
            default:
                if (
                    (currentc >= 'A' && currentc <= 'Z') ||
                    (currentc >= 'a' && currentc <= 'z') ||
                    currentc == '_'
                ) {
                    kind = IDENTIFIER;
                    chars_length = find_identifier_len(&wstr);
                }
                else {
                    kind = UNKNOWN;
                    chars_length = 1;
                }
        }


        // identifiers require further parsing
        if (kind == IDENTIFIER) {
            // if the identifier matches one of these keywords change kind to specify that keyword
            for (int i = 0; i < NUM_IDENTIFIERS; i++) {
                char ident_buf[11];
                (void)write_token_type(kind, ident_buf);

                // use strncmp bc current_ref has no null byte
                if (strncmp(current_ref, ident_buf, chars_length) == 0) {
                    kind = identifiers[i];
                    break;
                }
            }
        }

        // create token
        Token* tok = (Token*)malloc(sizeof(Token));
        tok->chars = current_ref;
        tok->chars_length = chars_length;
        tok->kind = kind;
        tok->line_number = line_number;


        // add token to list
        push_token(list_ptr, tok);
    }
    // endwhile

    return list_ptr;
}




size_t find_string_len(WalkableString* wstr_ptr) {
    size_t len = 1;
    char currentc = get_current_char(wstr_ptr);
    size_t at_end_of_str = advance(wstr_ptr);

    while (at_end_of_str != 0) {
        switch (currentc) {
            // backslash means next char is escaped so just automatically add it no matter what it is
            case '\\':
                // if the file ends before the string does what to do?
                // i''ll figure it out later
                
                // advance past the escaped character
                if (advance(wstr_ptr) == 0) {
                    return len;
                }
                len++;
                break;
            case '\"':
                return len - 1; // subtract one to not include quotation mark
            default:
                len++;
        }

        // update variables
        currentc = get_current_char(wstr_ptr);
        at_end_of_str = advance(wstr_ptr);
    }

    // if the file is over return len
    return len;
}


size_t find_number_len(WalkableString* wstr_ptr) {
    // we know that the first char is a number so len starts at 1
    size_t len = 1;
    char currentc = get_current_char(wstr_ptr);
    char nextc = peek(wstr_ptr);

    while (nextc != '\0') {
        // if it's a number just keep going
        // if it's a letter just keep going even though its probably a typo
        if (
            (currentc >= '0' && currentc <= '9') ||
            (currentc >= 'A' && currentc <= 'Z') ||
            (currentc >= 'a' && currentc <= 'z')
            )
        {
            len++;
            (void)advance(wstr_ptr);
            currentc = get_current_char(wstr_ptr);
            nextc = peek(wstr_ptr);
            continue;
        }

        // otherwise the number literal is over so return
        return len;
    }

    // if the file is over
    return len;
}


size_t find_identifier_len(WalkableString* wstr_ptr) {
    // first char has already been parsed so start len at 1
    size_t len = 1;
    char currentc = get_current_char(wstr_ptr);
    char nextc = peek(wstr_ptr);

    while (nextc != '\0') {
        // the parsing is actually very similar to parsing a number
        // the only difference is identifiers can contain underscores
        if (
            (currentc >= '0' && currentc <= '9') ||
            (currentc >= 'A' && currentc <= 'Z') ||
            (currentc >= 'a' && currentc <= 'z') ||
             currentc == '_'
            )
        {
            len++;
            (void)advance(wstr_ptr);
            currentc = get_current_char(wstr_ptr);
            nextc = peek(wstr_ptr);
            continue;
        }

        // if it's not one of those characters the identifier is over so return len
        return len;
    }

    return len;
}




/*
    Returns a pointer to a heap-allocated string representation of a TokenList
    Don't forget to free the string when you're done with it
*/
char* token_list_to_str(TokenList* list_ptr) {
    return token_list_as_str(list_ptr);
}