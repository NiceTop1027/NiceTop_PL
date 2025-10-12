#include "nicetop.h"

Value value_number(double num) {
    Value val;
    val.type = VAL_NUMBER;
    val.as.number = num;
    return val;
}

Value value_string(const char* str) {
    Value val;
    val.type = VAL_STRING;
    strncpy(val.as.string, str, MAX_TOKEN_LENGTH - 1);
    val.as.string[MAX_TOKEN_LENGTH - 1] = '\0';
    return val;
}

Value value_bool(bool b) {
    Value val;
    val.type = VAL_BOOL;
    val.as.boolean = b;
    return val;
}

Value value_null(void) {
    Value val;
    val.type = VAL_NULL;
    return val;
}

Value value_array(int capacity) {
    Value val;
    val.type = VAL_ARRAY;
    val.as.array = (Array*)malloc(sizeof(Array));
    val.as.array->elements = (Value*)malloc(sizeof(Value) * capacity);
    val.as.array->length = 0;
    val.as.array->capacity = capacity;
    return val;
}

Value value_file(FILE* f) {
    Value val;
    val.type = VAL_FILE;
    val.as.file = f;
    return val;
}

void array_push(Array* arr, Value val) {
    if (arr->length >= arr->capacity) {
        arr->capacity *= 2;
        arr->elements = (Value*)realloc(arr->elements, sizeof(Value) * arr->capacity);
    }
    arr->elements[arr->length++] = val;
}

Value array_get(Array* arr, int index) {
    if (index < 0 || index >= arr->length) {
        return value_null();
    }
    return arr->elements[index];
}

void array_set(Array* arr, int index, Value val) {
    if (index >= 0 && index < arr->length) {
        arr->elements[index] = val;
    }
}

void value_print(Value val) {
    switch (val.type) {
        case VAL_NUMBER:
            if (val.as.number == (int)val.as.number) {
                printf("%d\n", (int)val.as.number);
            } else {
                printf("%g\n", val.as.number);
            }
            break;
        case VAL_STRING:
            printf("%s\n", val.as.string);
            break;
        case VAL_BOOL:
            printf("%s\n", val.as.boolean ? "true" : "false");
            break;
        case VAL_NULL:
            printf("null\n");
            break;
        case VAL_ARRAY:
            printf("[");
            for (int i = 0; i < val.as.array->length; i++) {
                if (i > 0) printf(", ");
                Value elem = val.as.array->elements[i];
                if (elem.type == VAL_NUMBER) {
                    if (elem.as.number == (int)elem.as.number) {
                        printf("%d", (int)elem.as.number);
                    } else {
                        printf("%g", elem.as.number);
                    }
                } else if (elem.type == VAL_STRING) {
                    printf("\"%s\"", elem.as.string);
                } else if (elem.type == VAL_BOOL) {
                    printf("%s", elem.as.boolean ? "true" : "false");
                }
            }
            printf("]\n");
            break;
        default:
            printf("unknown\n");
            break;
    }
}

bool value_is_truthy(Value val) {
    switch (val.type) {
        case VAL_NULL:
            return false;
        case VAL_BOOL:
            return val.as.boolean;
        case VAL_NUMBER:
            return val.as.number != 0;
        case VAL_STRING:
            return strlen(val.as.string) > 0;
        default:
            return false;
    }
}

Environment* env_create(Environment* parent) {
    Environment* env = (Environment*)malloc(sizeof(Environment));
    env->var_count = 0;
    env->parent = parent;
    return env;
}

void env_define(Environment* env, const char* name, Value value) {
    for (int i = 0; i < env->var_count; i++) {
        if (strcmp(env->variables[i].name, name) == 0) {
            env->variables[i].value = value;
            return;
        }
    }
    
    strncpy(env->variables[env->var_count].name, name, MAX_TOKEN_LENGTH - 1);
    env->variables[env->var_count].name[MAX_TOKEN_LENGTH - 1] = '\0';
    env->variables[env->var_count].value = value;
    env->var_count++;
}

Value env_get(Environment* env, const char* name) {
    for (int i = 0; i < env->var_count; i++) {
        if (strcmp(env->variables[i].name, name) == 0) {
            return env->variables[i].value;
        }
    }
    
    if (env->parent != NULL) {
        return env_get(env->parent, name);
    }
    
    fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    return value_null();
}

void env_set(Environment* env, const char* name, Value value) {
    for (int i = 0; i < env->var_count; i++) {
        if (strcmp(env->variables[i].name, name) == 0) {
            env->variables[i].value = value;
            return;
        }
    }
    
    if (env->parent != NULL) {
        env_set(env->parent, name, value);
    } else {
        fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    }
}
