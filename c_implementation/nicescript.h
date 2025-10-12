#ifndef NICESCRIPT_H
#define NICESCRIPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 토큰 타입
typedef enum {
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_LET,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_PRINT,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

// 토큰 구조체
typedef struct {
    TokenType type;
    char* value;
    int line;
} Token;

// 값 타입
typedef enum {
    VAL_NUMBER,
    VAL_STRING,
    VAL_BOOL,
    VAL_NULL
} ValueType;

// 값 구조체
typedef struct {
    ValueType type;
    union {
        double number;
        char* string;
        bool boolean;
    } as;
} Value;

// 변수 구조체
typedef struct Variable {
    char* name;
    Value value;
    struct Variable* next;
} Variable;

// 환경 (스코프)
typedef struct Environment {
    Variable* variables;
    struct Environment* parent;
} Environment;

// 렉서
typedef struct {
    const char* source;
    int pos;
    int line;
    Token* tokens;
    int token_count;
    int token_capacity;
} Lexer;

// 함수 선언
Lexer* lexer_create(const char* source);
void lexer_tokenize(Lexer* lexer);
void lexer_free(Lexer* lexer);

Environment* env_create(Environment* parent);
void env_define(Environment* env, const char* name, Value value);
Value env_get(Environment* env, const char* name);
void env_set(Environment* env, const char* name, Value value);
void env_free(Environment* env);

Value value_number(double num);
Value value_string(const char* str);
Value value_bool(bool b);
Value value_null(void);
void value_print(Value val);
bool value_is_truthy(Value val);

#endif
