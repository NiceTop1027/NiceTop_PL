#ifndef NICETOP_H
#define NICETOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 10000
#define MAX_VARIABLES 1000

// 토큰 타입
typedef enum {
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_NINT,
    TOKEN_NFLOAT,
    TOKEN_NSTRING,
    TOKEN_NBOOL,
    TOKEN_NIF,
    TOKEN_NELSE,
    TOKEN_NLOOP,
    TOKEN_NFOR,
    TOKEN_NBREAK,
    TOKEN_NCONTINUE,
    TOKEN_NFUNC,
    TOKEN_NRET,
    TOKEN_NOUT,
    TOKEN_NTRUE,
    TOKEN_NFALSE,
    TOKEN_NINPUT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MODULO,
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

// 토큰
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
    int line;
} Token;

// 값 타입
typedef enum {
    VAL_NUMBER,
    VAL_STRING,
    VAL_BOOL,
    VAL_NULL,
    VAL_FUNCTION
} ValueType;

// 함수 정의
typedef struct Function {
    char name[MAX_TOKEN_LENGTH];
    char params[10][MAX_TOKEN_LENGTH];
    int param_count;
    int body_start;
    int body_end;
} Function;

// 값
typedef struct {
    ValueType type;
    union {
        double number;
        char string[MAX_TOKEN_LENGTH];
        bool boolean;
        Function* function;
    } as;
} Value;

// 변수
typedef struct {
    char name[MAX_TOKEN_LENGTH];
    Value value;
} Variable;

// 환경 (스코프)
typedef struct Environment {
    Variable variables[MAX_VARIABLES];
    int var_count;
    struct Environment* parent;
} Environment;

// 렉서
typedef struct {
    const char* source;
    int pos;
    int line;
    Token tokens[MAX_TOKENS];
    int token_count;
} Lexer;

// 파서/인터프리터
typedef struct {
    Token* tokens;
    int token_count;
    int pos;
    Variable variables[MAX_VARIABLES];
    int var_count;
    Function functions[100];
    int func_count;
    Value return_value;
    bool returning;
    bool breaking;
    bool continuing;
} Interpreter;

// 함수 선언
void lexer_init(Lexer* lexer, const char* source);
void lexer_tokenize(Lexer* lexer);

Environment* env_create(Environment* parent);
void env_define(Environment* env, const char* name, Value value);
Value env_get(Environment* env, const char* name);
void env_set(Environment* env, const char* name, Value value);

Value value_number(double num);
Value value_string(const char* str);
Value value_bool(bool b);
Value value_null(void);
void value_print(Value val);
bool value_is_truthy(Value val);

void interpreter_init(Interpreter* interp, Token* tokens, int count);
void interpreter_run(Interpreter* interp);
Value interpreter_eval_expression(Interpreter* interp);
void execute_statement(Interpreter* interp);

#endif
