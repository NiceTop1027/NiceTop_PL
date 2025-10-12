#include "nicescript.h"

Lexer* lexer_create(const char* source) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->token_count = 0;
    lexer->token_capacity = 100;
    lexer->tokens = (Token*)malloc(sizeof(Token) * lexer->token_capacity);
    return lexer;
}

static char current_char(Lexer* lexer) {
    if (lexer->pos >= strlen(lexer->source)) {
        return '\0';
    }
    return lexer->source[lexer->pos];
}

static void advance(Lexer* lexer) {
    if (current_char(lexer) == '\n') {
        lexer->line++;
    }
    lexer->pos++;
}

static void skip_whitespace(Lexer* lexer) {
    while (current_char(lexer) == ' ' || current_char(lexer) == '\t' || 
           current_char(lexer) == '\r' || current_char(lexer) == '\n') {
        advance(lexer);
    }
}

static void skip_comment(Lexer* lexer) {
    if (current_char(lexer) == '#') {
        while (current_char(lexer) != '\n' && current_char(lexer) != '\0') {
            advance(lexer);
        }
    }
}

static void add_token(Lexer* lexer, TokenType type, const char* value) {
    if (lexer->token_count >= lexer->token_capacity) {
        lexer->token_capacity *= 2;
        lexer->tokens = (Token*)realloc(lexer->tokens, sizeof(Token) * lexer->token_capacity);
    }
    
    Token token;
    token.type = type;
    token.value = value ? strdup(value) : NULL;
    token.line = lexer->line;
    lexer->tokens[lexer->token_count++] = token;
}

static void read_number(Lexer* lexer) {
    char buffer[256];
    int i = 0;
    
    while (isdigit(current_char(lexer)) || current_char(lexer) == '.') {
        buffer[i++] = current_char(lexer);
        advance(lexer);
    }
    buffer[i] = '\0';
    
    add_token(lexer, TOKEN_NUMBER, buffer);
}

static void read_string(Lexer* lexer) {
    char buffer[1024];
    int i = 0;
    char quote = current_char(lexer);
    advance(lexer); // skip opening quote
    
    while (current_char(lexer) != quote && current_char(lexer) != '\0') {
        buffer[i++] = current_char(lexer);
        advance(lexer);
    }
    buffer[i] = '\0';
    advance(lexer); // skip closing quote
    
    add_token(lexer, TOKEN_STRING, buffer);
}

static void read_identifier(Lexer* lexer) {
    char buffer[256];
    int i = 0;
    
    while (isalnum(current_char(lexer)) || current_char(lexer) == '_') {
        buffer[i++] = current_char(lexer);
        advance(lexer);
    }
    buffer[i] = '\0';
    
    // 키워드 체크
    TokenType type = TOKEN_IDENTIFIER;
    if (strcmp(buffer, "let") == 0) type = TOKEN_LET;
    else if (strcmp(buffer, "if") == 0) type = TOKEN_IF;
    else if (strcmp(buffer, "else") == 0) type = TOKEN_ELSE;
    else if (strcmp(buffer, "while") == 0) type = TOKEN_WHILE;
    else if (strcmp(buffer, "function") == 0) type = TOKEN_FUNCTION;
    else if (strcmp(buffer, "return") == 0) type = TOKEN_RETURN;
    else if (strcmp(buffer, "print") == 0) type = TOKEN_PRINT;
    else if (strcmp(buffer, "true") == 0) type = TOKEN_TRUE;
    else if (strcmp(buffer, "false") == 0) type = TOKEN_FALSE;
    else if (strcmp(buffer, "and") == 0) type = TOKEN_AND;
    else if (strcmp(buffer, "or") == 0) type = TOKEN_OR;
    else if (strcmp(buffer, "not") == 0) type = TOKEN_NOT;
    
    add_token(lexer, type, buffer);
}

void lexer_tokenize(Lexer* lexer) {
    while (current_char(lexer) != '\0') {
        skip_whitespace(lexer);
        
        if (current_char(lexer) == '\0') break;
        
        if (current_char(lexer) == '#') {
            skip_comment(lexer);
            continue;
        }
        
        if (isdigit(current_char(lexer))) {
            read_number(lexer);
            continue;
        }
        
        if (current_char(lexer) == '"' || current_char(lexer) == '\'') {
            read_string(lexer);
            continue;
        }
        
        if (isalpha(current_char(lexer)) || current_char(lexer) == '_') {
            read_identifier(lexer);
            continue;
        }
        
        char c = current_char(lexer);
        switch (c) {
            case '+': add_token(lexer, TOKEN_PLUS, "+"); advance(lexer); break;
            case '-': add_token(lexer, TOKEN_MINUS, "-"); advance(lexer); break;
            case '*': add_token(lexer, TOKEN_MULTIPLY, "*"); advance(lexer); break;
            case '/': add_token(lexer, TOKEN_DIVIDE, "/"); advance(lexer); break;
            case '(': add_token(lexer, TOKEN_LPAREN, "("); advance(lexer); break;
            case ')': add_token(lexer, TOKEN_RPAREN, ")"); advance(lexer); break;
            case '{': add_token(lexer, TOKEN_LBRACE, "{"); advance(lexer); break;
            case '}': add_token(lexer, TOKEN_RBRACE, "}"); advance(lexer); break;
            case ',': add_token(lexer, TOKEN_COMMA, ","); advance(lexer); break;
            case ';': add_token(lexer, TOKEN_SEMICOLON, ";"); advance(lexer); break;
            case '=':
                advance(lexer);
                if (current_char(lexer) == '=') {
                    add_token(lexer, TOKEN_EQUAL, "==");
                    advance(lexer);
                } else {
                    add_token(lexer, TOKEN_ASSIGN, "=");
                }
                break;
            case '!':
                advance(lexer);
                if (current_char(lexer) == '=') {
                    add_token(lexer, TOKEN_NOT_EQUAL, "!=");
                    advance(lexer);
                }
                break;
            case '<':
                advance(lexer);
                if (current_char(lexer) == '=') {
                    add_token(lexer, TOKEN_LESS_EQUAL, "<=");
                    advance(lexer);
                } else {
                    add_token(lexer, TOKEN_LESS, "<");
                }
                break;
            case '>':
                advance(lexer);
                if (current_char(lexer) == '=') {
                    add_token(lexer, TOKEN_GREATER_EQUAL, ">=");
                    advance(lexer);
                } else {
                    add_token(lexer, TOKEN_GREATER, ">");
                }
                break;
            default:
                advance(lexer);
                break;
        }
    }
    
    add_token(lexer, TOKEN_EOF, NULL);
}

void lexer_free(Lexer* lexer) {
    for (int i = 0; i < lexer->token_count; i++) {
        if (lexer->tokens[i].value) {
            free(lexer->tokens[i].value);
        }
    }
    free(lexer->tokens);
    free(lexer);
}
