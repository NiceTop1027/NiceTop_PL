#include "nicescript.h"

Value value_number(double num) {
    Value val;
    val.type = VAL_NUMBER;
    val.as.number = num;
    return val;
}

Value value_string(const char* str) {
    Value val;
    val.type = VAL_STRING;
    val.as.string = strdup(str);
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
    env->variables = NULL;
    env->parent = parent;
    return env;
}

void env_define(Environment* env, const char* name, Value value) {
    Variable* var = (Variable*)malloc(sizeof(Variable));
    var->name = strdup(name);
    var->value = value;
    var->next = env->variables;
    env->variables = var;
}

Value env_get(Environment* env, const char* name) {
    Variable* var = env->variables;
    while (var != NULL) {
        if (strcmp(var->name, name) == 0) {
            return var->value;
        }
        var = var->next;
    }
    
    if (env->parent != NULL) {
        return env_get(env->parent, name);
    }
    
    fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    return value_null();
}

void env_set(Environment* env, const char* name, Value value) {
    Variable* var = env->variables;
    while (var != NULL) {
        if (strcmp(var->name, name) == 0) {
            var->value = value;
            return;
        }
        var = var->next;
    }
    
    if (env->parent != NULL) {
        env_set(env->parent, name, value);
    } else {
        fprintf(stderr, "Error: Undefined variable '%s'\n", name);
    }
}

void env_free(Environment* env) {
    Variable* var = env->variables;
    while (var != NULL) {
        Variable* next = var->next;
        free(var->name);
        if (var->value.type == VAL_STRING) {
            free(var->value.as.string);
        }
        free(var);
        var = next;
    }
    free(env);
}
