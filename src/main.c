#include "nicetop.h"

void run_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "오류: 파일 '%s'을 찾을 수 없습니다.\n", filename);
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* source = (char*)malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);
    
    // 렉싱
    Lexer lexer;
    lexer_init(&lexer, source);
    lexer_tokenize(&lexer);
    
    // 인터프리터 실행
    Interpreter interp;
    interpreter_init(&interp, lexer.tokens, lexer.token_count);
    interpreter_run(&interp);
    
    free(source);
    // free(interp.env);
}

void repl() {
    printf("NiceTop REPL v1.0 - 절차지향 프로그래밍 언어\n");
    printf("종료하려면 'exit' 입력\n\n");
    
    Interpreter interp;
    Token tokens[MAX_TOKENS];
    interp.tokens = tokens;
    // interp.env = env_create(NULL);
    // interp.function_count = 0;
    interp.returning = false;
    
    char line[1024];
    while (true) {
        printf("nicetop> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        
        if (strcmp(line, "exit\n") == 0 || strcmp(line, "quit\n") == 0) {
            break;
        }
        
        Lexer lexer;
        lexer_init(&lexer, line);
        lexer_tokenize(&lexer);
        
        interp.tokens = lexer.tokens;
        interp.pos = 0;
        interp.token_count = lexer.token_count;
        
        while (interp.tokens[interp.pos].type != TOKEN_EOF) {
            execute_statement(&interp);
        }
    }
    
    // free(interp.env);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        repl();
    } else {
        run_file(argv[1]);
    }
    
    return 0;
}
