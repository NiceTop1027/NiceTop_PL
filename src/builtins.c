#include "nicetop.h"

// 내장 함수 구현

// ninput - 사용자 입력 받기
Value builtin_ninput(const char* prompt) {
    if (prompt && strlen(prompt) > 0) {
        printf("%s", prompt);
    }
    
    char buffer[MAX_TOKEN_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        // 개행 문자 제거
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        return value_string(buffer);
    }
    
    return value_string("");
}

// nlen - 문자열 길이 또는 배열 크기
Value builtin_nlen(Value val) {
    if (val.type == VAL_STRING) {
        return value_number((double)strlen(val.as.string));
    }
    return value_number(0);
}

// ntype - 값의 타입 반환
Value builtin_ntype(Value val) {
    switch (val.type) {
        case VAL_NUMBER:
            return value_string("number");
        case VAL_STRING:
            return value_string("string");
        case VAL_BOOL:
            return value_string("bool");
        case VAL_NULL:
            return value_string("null");
        default:
            return value_string("unknown");
    }
}

// nstr - 값을 문자열로 변환
Value builtin_nstr(Value val) {
    char buffer[MAX_TOKEN_LENGTH];
    
    switch (val.type) {
        case VAL_NUMBER:
            if (val.as.number == (int)val.as.number) {
                snprintf(buffer, sizeof(buffer), "%d", (int)val.as.number);
            } else {
                snprintf(buffer, sizeof(buffer), "%g", val.as.number);
            }
            return value_string(buffer);
        case VAL_STRING:
            return val;
        case VAL_BOOL:
            return value_string(val.as.boolean ? "true" : "false");
        case VAL_NULL:
            return value_string("null");
        default:
            return value_string("");
    }
}

// nnum - 문자열을 숫자로 변환
Value builtin_nnum(Value val) {
    if (val.type == VAL_STRING) {
        return value_number(atof(val.as.string));
    } else if (val.type == VAL_NUMBER) {
        return val;
    }
    return value_number(0);
}

// nrand - 난수 생성 (0 ~ max-1)
Value builtin_nrand(int max) {
    if (max <= 0) max = 100;
    return value_number((double)(rand() % max));
}

// nsleep - 밀리초 단위 대기
void builtin_nsleep(int milliseconds) {
    usleep(milliseconds * 1000);
}

// ntime - 현재 시간 (초)
Value builtin_ntime() {
    return value_number((double)time(NULL));
}
