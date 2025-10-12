#include "nicetop.h"

void lexer_init(Lexer* lexer, const char* source) {
    lexer->source = source;
    lexer->pos = 0;
    lexer->line = 1;
    lexer->token_count = 0;
}

static char current_char(Lexer* lexer) {
    if (lexer->pos >= strlen(lexer->source)) {
        return '\0';
    }
    return lexer->source[lexer->pos];
}

static char peek_char(Lexer* lexer, int offset) {
    int pos = lexer->pos + offset;
    if (pos >= strlen(lexer->source)) {
        return '\0';
    }
    return lexer->source[pos];
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
    Token token;
    token.type = type;
    strncpy(token.value, value ? value : "", MAX_TOKEN_LENGTH - 1);
    token.value[MAX_TOKEN_LENGTH - 1] = '\0';
    token.line = lexer->line;
    lexer->tokens[lexer->token_count++] = token;
}

static void read_number(Lexer* lexer) {
    char buffer[MAX_TOKEN_LENGTH];
    int i = 0;
    
    while (isdigit(current_char(lexer)) || current_char(lexer) == '.') {
        buffer[i++] = current_char(lexer);
        advance(lexer);
    }
    buffer[i] = '\0';
    add_token(lexer, TOKEN_NUMBER, buffer);
}

static void read_string(Lexer* lexer) {
    char buffer[MAX_TOKEN_LENGTH];
    int i = 0;
    char quote = current_char(lexer);
    advance(lexer);
    
    while (current_char(lexer) != quote && current_char(lexer) != '\0') {
        if (current_char(lexer) == '\\') {
            advance(lexer);
            // 이스케이프 문자 처리
            if (current_char(lexer) == 'n') buffer[i++] = '\n';        // 개행
            else if (current_char(lexer) == 't') buffer[i++] = '\t';   // 탭
            else if (current_char(lexer) == 'r') buffer[i++] = '\r';   // 캐리지 리턴
            else if (current_char(lexer) == '\\') buffer[i++] = '\\';  // 백슬래시
            else if (current_char(lexer) == '\'') buffer[i++] = '\'';  // 작은따옴표
            else if (current_char(lexer) == '\"') buffer[i++] = '\"';  // 큰따옴표
            else if (current_char(lexer) == '0') buffer[i++] = '\0';   // NULL
            else if (current_char(lexer) == 'a') buffer[i++] = '\a';   // 벨
            else if (current_char(lexer) == 'b') buffer[i++] = '\b';   // 백스페이스
            else if (current_char(lexer) == 'f') buffer[i++] = '\f';   // 폼피드
            else if (current_char(lexer) == 'v') buffer[i++] = '\v';   // 수직탭
            else buffer[i++] = current_char(lexer);
            advance(lexer);
        } else {
            buffer[i++] = current_char(lexer);
            advance(lexer);
        }
    }
    buffer[i] = '\0';
    advance(lexer);
    add_token(lexer, TOKEN_STRING, buffer);
}

static void read_identifier(Lexer* lexer) {
    char buffer[MAX_TOKEN_LENGTH];
    int i = 0;
    
    while (isalnum(current_char(lexer)) || current_char(lexer) == '_') {
        buffer[i++] = current_char(lexer);
        advance(lexer);
    }
    buffer[i] = '\0';
    
    TokenType type = TOKEN_IDENTIFIER;
    if (strcmp(buffer, "nint") == 0) type = TOKEN_NINT;
    else if (strcmp(buffer, "nfloat") == 0) type = TOKEN_NFLOAT;
    else if (strcmp(buffer, "nstring") == 0) type = TOKEN_NSTRING;
    else if (strcmp(buffer, "nbool") == 0) type = TOKEN_NBOOL;
    else if (strcmp(buffer, "nif") == 0) type = TOKEN_NIF;
    else if (strcmp(buffer, "nelse") == 0) type = TOKEN_NELSE;
    else if (strcmp(buffer, "nloop") == 0) type = TOKEN_NLOOP;
    else if (strcmp(buffer, "nfunc") == 0) type = TOKEN_NFUNC;
    else if (strcmp(buffer, "nret") == 0) type = TOKEN_NRET;
    else if (strcmp(buffer, "nout") == 0) type = TOKEN_NOUT;
    else if (strcmp(buffer, "ntrue") == 0) type = TOKEN_NTRUE;
    else if (strcmp(buffer, "nfalse") == 0) type = TOKEN_NFALSE;
    else if (strcmp(buffer, "ninput") == 0) type = TOKEN_NINPUT;
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
            case '%': add_token(lexer, TOKEN_MODULO, "%"); advance(lexer); break;
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
