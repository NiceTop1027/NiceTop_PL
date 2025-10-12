#include "nicescript.h"

// 간단한 인터프리터 (표현식 평가만)
typedef struct {
    Token* tokens;
    int pos;
    int count;
    Environment* env;
} Parser;

static Token current_token(Parser* p) {
    if (p->pos >= p->count) {
        return p->tokens[p->count - 1];
    }
    return p->tokens[p->pos];
}

static void advance_parser(Parser* p) {
    if (p->pos < p->count - 1) {
        p->pos++;
    }
}

static Value parse_primary(Parser* p);
static Value parse_expression(Parser* p);

static Value parse_primary(Parser* p) {
    Token token = current_token(p);
    
    if (token.type == TOKEN_NUMBER) {
        advance_parser(p);
        return value_number(atof(token.value));
    }
    
    if (token.type == TOKEN_STRING) {
        advance_parser(p);
        return value_string(token.value);
    }
    
    if (token.type == TOKEN_TRUE) {
        advance_parser(p);
        return value_bool(true);
    }
    
    if (token.type == TOKEN_FALSE) {
        advance_parser(p);
        return value_bool(false);
    }
    
    if (token.type == TOKEN_IDENTIFIER) {
        advance_parser(p);
        return env_get(p->env, token.value);
    }
    
    if (token.type == TOKEN_LPAREN) {
        advance_parser(p);
        Value val = parse_expression(p);
        advance_parser(p); // skip )
        return val;
    }
    
    return value_null();
}

static Value parse_term(Parser* p) {
    Value left = parse_primary(p);
    
    while (current_token(p).type == TOKEN_MULTIPLY || 
           current_token(p).type == TOKEN_DIVIDE) {
        Token op = current_token(p);
        advance_parser(p);
        Value right = parse_primary(p);
        
        if (op.type == TOKEN_MULTIPLY) {
            left = value_number(left.as.number * right.as.number);
        } else {
            left = value_number(left.as.number / right.as.number);
        }
    }
    
    return left;
}

static Value parse_expression(Parser* p) {
    Value left = parse_term(p);
    
    while (current_token(p).type == TOKEN_PLUS || 
           current_token(p).type == TOKEN_MINUS) {
        Token op = current_token(p);
        advance_parser(p);
        Value right = parse_term(p);
        
        if (op.type == TOKEN_PLUS) {
            if (left.type == VAL_STRING || right.type == VAL_STRING) {
                // 문자열 연결
                char buffer[1024];
                if (left.type == VAL_STRING && right.type == VAL_STRING) {
                    snprintf(buffer, sizeof(buffer), "%s%s", left.as.string, right.as.string);
                } else if (left.type == VAL_STRING) {
                    snprintf(buffer, sizeof(buffer), "%s%g", left.as.string, right.as.number);
                } else {
                    snprintf(buffer, sizeof(buffer), "%g%s", left.as.number, right.as.string);
                }
                left = value_string(buffer);
            } else {
                left = value_number(left.as.number + right.as.number);
            }
        } else {
            left = value_number(left.as.number - right.as.number);
        }
    }
    
    return left;
}

static void parse_statement(Parser* p) {
    Token token = current_token(p);
    
    if (token.type == TOKEN_PRINT) {
        advance_parser(p);
        advance_parser(p); // skip (
        Value val = parse_expression(p);
        advance_parser(p); // skip )
        value_print(val);
    }
    else if (token.type == TOKEN_LET) {
        advance_parser(p);
        Token name = current_token(p);
        advance_parser(p);
        advance_parser(p); // skip =
        Value val = parse_expression(p);
        env_define(p->env, name.value, val);
    }
    else if (token.type == TOKEN_IDENTIFIER) {
        Token name = current_token(p);
        advance_parser(p);
        if (current_token(p).type == TOKEN_ASSIGN) {
            advance_parser(p);
            Value val = parse_expression(p);
            env_set(p->env, name.value, val);
        }
    }
}

void run_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* source = (char*)malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);
    
    // 렉싱
    Lexer* lexer = lexer_create(source);
    lexer_tokenize(lexer);
    
    // 파싱 및 실행
    Parser parser;
    parser.tokens = lexer->tokens;
    parser.pos = 0;
    parser.count = lexer->token_count;
    parser.env = env_create(NULL);
    
    while (current_token(&parser).type != TOKEN_EOF) {
        parse_statement(&parser);
    }
    
    // 정리
    env_free(parser.env);
    lexer_free(lexer);
    free(source);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <file.ns>\n", argv[0]);
        return 1;
    }
    
    run_file(argv[1]);
    return 0;
}
