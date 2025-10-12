#include "nicetop.h"

static Token current_token(Interpreter* interp) {
    if (interp->pos >= interp->token_count) {
        return interp->tokens[interp->token_count - 1];
    }
    return interp->tokens[interp->pos];
}

static void advance_interp(Interpreter* interp) {
    if (interp->pos < interp->token_count - 1) {
        interp->pos++;
    }
}

static Value eval_primary(Interpreter* interp);
static Value eval_term(Interpreter* interp);
static Value eval_comparison(Interpreter* interp);

static Value eval_primary(Interpreter* interp) {
    Token token = current_token(interp);
    
    if (token.type == TOKEN_NUMBER) {
        advance_interp(interp);
        return value_number(atof(token.value));
    }
    
    if (token.type == TOKEN_STRING) {
        advance_interp(interp);
        return value_string(token.value);
    }
    
    if (token.type == TOKEN_NTRUE) {
        advance_interp(interp);
        return value_bool(true);
    }
    
    if (token.type == TOKEN_NFALSE) {
        advance_interp(interp);
        return value_bool(false);
    }
    
    if (token.type == TOKEN_IDENTIFIER) {
        char name[MAX_TOKEN_LENGTH];
        strcpy(name, token.value);
        advance_interp(interp);
        
        // 함수 호출
        if (current_token(interp).type == TOKEN_LPAREN) {
            advance_interp(interp); // skip (
            
            // 함수 찾기
            Function* func = NULL;
            for (int i = 0; i < interp->function_count; i++) {
                if (strcmp(interp->functions[i].name, name) == 0) {
                    func = &interp->functions[i];
                    break;
                }
            }
            
            if (func == NULL) {
                fprintf(stderr, "Error: Undefined function '%s'\n", name);
                return value_null();
            }
            
            // 인자 평가
            Value args[10];
            int arg_count = 0;
            while (current_token(interp).type != TOKEN_RPAREN) {
                args[arg_count++] = interpreter_eval_expression(interp);
                if (current_token(interp).type == TOKEN_COMMA) {
                    advance_interp(interp);
                }
            }
            advance_interp(interp); // skip )
            
            // 새 환경 생성
            Environment* func_env = env_create(interp->env);
            for (int i = 0; i < func->param_count; i++) {
                env_define(func_env, func->params[i], args[i]);
            }
            
            // 함수 실행
            Environment* prev_env = interp->env;
            interp->env = func_env;
            int prev_pos = interp->pos;
            interp->pos = func->body_start;
            interp->returning = false;
            
            while (interp->pos < func->body_end && !interp->returning) {
                execute_statement(interp);
            }
            
            Value result = interp->returning ? interp->return_value : value_null();
            interp->returning = false;
            interp->env = prev_env;
            interp->pos = prev_pos;
            free(func_env);
            
            return result;
        }
        
        return env_get(interp->env, name);
    }
    
    if (token.type == TOKEN_LPAREN) {
        advance_interp(interp);
        Value val = interpreter_eval_expression(interp);
        advance_interp(interp); // skip )
        return val;
    }
    
    if (token.type == TOKEN_MINUS) {
        advance_interp(interp);
        Value val = eval_primary(interp);
        return value_number(-val.as.number);
    }
    
    if (token.type == TOKEN_NOT) {
        advance_interp(interp);
        Value val = eval_primary(interp);
        return value_bool(!value_is_truthy(val));
    }
    
    return value_null();
}

static Value eval_term(Interpreter* interp) {
    Value left = eval_primary(interp);
    
    while (current_token(interp).type == TOKEN_MULTIPLY || 
           current_token(interp).type == TOKEN_DIVIDE ||
           current_token(interp).type == TOKEN_MODULO) {
        TokenType op = current_token(interp).type;
        advance_interp(interp);
        Value right = eval_primary(interp);
        
        if (op == TOKEN_MULTIPLY) {
            left = value_number(left.as.number * right.as.number);
        } else if (op == TOKEN_DIVIDE) {
            left = value_number(left.as.number / right.as.number);
        } else {
            left = value_number((int)left.as.number % (int)right.as.number);
        }
    }
    
    return left;
}

static Value eval_additive(Interpreter* interp) {
    Value left = eval_term(interp);
    
    while (current_token(interp).type == TOKEN_PLUS || 
           current_token(interp).type == TOKEN_MINUS) {
        TokenType op = current_token(interp).type;
        advance_interp(interp);
        Value right = eval_term(interp);
        
        if (op == TOKEN_PLUS) {
            if (left.type == VAL_STRING || right.type == VAL_STRING) {
                char buffer[MAX_TOKEN_LENGTH * 2];
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

static Value eval_comparison(Interpreter* interp) {
    Value left = eval_additive(interp);
    
    TokenType op = current_token(interp).type;
    if (op == TOKEN_EQUAL || op == TOKEN_NOT_EQUAL ||
        op == TOKEN_LESS || op == TOKEN_GREATER ||
        op == TOKEN_LESS_EQUAL || op == TOKEN_GREATER_EQUAL) {
        advance_interp(interp);
        Value right = eval_additive(interp);
        
        bool result = false;
        if (op == TOKEN_EQUAL) result = (left.as.number == right.as.number);
        else if (op == TOKEN_NOT_EQUAL) result = (left.as.number != right.as.number);
        else if (op == TOKEN_LESS) result = (left.as.number < right.as.number);
        else if (op == TOKEN_GREATER) result = (left.as.number > right.as.number);
        else if (op == TOKEN_LESS_EQUAL) result = (left.as.number <= right.as.number);
        else if (op == TOKEN_GREATER_EQUAL) result = (left.as.number >= right.as.number);
        
        return value_bool(result);
    }
    
    return left;
}

static Value eval_logical(Interpreter* interp) {
    Value left = eval_comparison(interp);
    
    while (current_token(interp).type == TOKEN_AND || 
           current_token(interp).type == TOKEN_OR) {
        TokenType op = current_token(interp).type;
        advance_interp(interp);
        Value right = eval_comparison(interp);
        
        if (op == TOKEN_AND) {
            left = value_bool(value_is_truthy(left) && value_is_truthy(right));
        } else {
            left = value_bool(value_is_truthy(left) || value_is_truthy(right));
        }
    }
    
    return left;
}

Value interpreter_eval_expression(Interpreter* interp) {
    return eval_logical(interp);
}

void execute_statement(Interpreter* interp) {
    Token token = current_token(interp);
    
    if (token.type == TOKEN_NOUT) {
        advance_interp(interp);
        advance_interp(interp); // skip (
        Value val = interpreter_eval_expression(interp);
        advance_interp(interp); // skip )
        value_print(val);
    }
    else if (token.type == TOKEN_NINT || token.type == TOKEN_NFLOAT || 
             token.type == TOKEN_NSTRING || token.type == TOKEN_NBOOL) {
        advance_interp(interp); // skip type
        Token name = current_token(interp);
        advance_interp(interp);
        advance_interp(interp); // skip =
        Value val = interpreter_eval_expression(interp);
        env_define(interp->env, name.value, val);
    }
    else if (token.type == TOKEN_IDENTIFIER) {
        Token name = current_token(interp);
        advance_interp(interp);
        if (current_token(interp).type == TOKEN_ASSIGN) {
            advance_interp(interp);
            Value val = interpreter_eval_expression(interp);
            env_set(interp->env, name.value, val);
        } else {
            interp->pos--;
            interpreter_eval_expression(interp);
        }
    }
    else if (token.type == TOKEN_NIF) {
        advance_interp(interp);
        advance_interp(interp); // skip (
        Value condition = interpreter_eval_expression(interp);
        advance_interp(interp); // skip )
        advance_interp(interp); // skip {
        
        int brace_count = 1;
        int then_start = interp->pos;
        while (brace_count > 0) {
            if (current_token(interp).type == TOKEN_LBRACE) brace_count++;
            if (current_token(interp).type == TOKEN_RBRACE) brace_count--;
            advance_interp(interp);
        }
        int then_end = interp->pos - 1;
        
        int else_start = -1, else_end = -1;
        if (current_token(interp).type == TOKEN_NELSE) {
            advance_interp(interp);
            advance_interp(interp); // skip {
            else_start = interp->pos;
            brace_count = 1;
            while (brace_count > 0) {
                if (current_token(interp).type == TOKEN_LBRACE) brace_count++;
                if (current_token(interp).type == TOKEN_RBRACE) brace_count--;
                advance_interp(interp);
            }
            else_end = interp->pos - 1;
        }
        
        int saved_pos = interp->pos;
        if (value_is_truthy(condition)) {
            interp->pos = then_start;
            while (interp->pos < then_end && !interp->returning) {
                execute_statement(interp);
            }
        } else if (else_start >= 0) {
            interp->pos = else_start;
            while (interp->pos < else_end && !interp->returning) {
                execute_statement(interp);
            }
        }
        interp->pos = saved_pos;
    }
    else if (token.type == TOKEN_NLOOP) {
        advance_interp(interp);
        int cond_start = interp->pos;
        advance_interp(interp); // skip (
        int expr_start = interp->pos;
        
        int paren_count = 1;
        while (paren_count > 0) {
            if (current_token(interp).type == TOKEN_LPAREN) paren_count++;
            if (current_token(interp).type == TOKEN_RPAREN) paren_count--;
            advance_interp(interp);
        }
        int expr_end = interp->pos - 1;
        
        advance_interp(interp); // skip {
        int body_start = interp->pos;
        int brace_count = 1;
        while (brace_count > 0) {
            if (current_token(interp).type == TOKEN_LBRACE) brace_count++;
            if (current_token(interp).type == TOKEN_RBRACE) brace_count--;
            advance_interp(interp);
        }
        int body_end = interp->pos - 1;
        int saved_pos = interp->pos;
        
        while (true) {
            interp->pos = expr_start;
            Value condition = interpreter_eval_expression(interp);
            if (!value_is_truthy(condition)) break;
            
            interp->pos = body_start;
            while (interp->pos < body_end && !interp->returning) {
                execute_statement(interp);
            }
            if (interp->returning) break;
        }
        interp->pos = saved_pos;
    }
    else if (token.type == TOKEN_NFOR) {
        advance_interp(interp);
        advance_interp(interp); // skip (
        
        // 초기화 실행
        if (current_token(interp).type != TOKEN_SEMICOLON) {
            execute_statement(interp);
        }
        
        // 첫 번째 세미콜론까지 건너뛰기
        while (current_token(interp).type != TOKEN_SEMICOLON && current_token(interp).type != TOKEN_EOF) {
            advance_interp(interp);
        }
        advance_interp(interp); // skip ;
        
        // 조건식 시작 위치
        int cond_start = interp->pos;
        
        // 두 번째 세미콜론까지 건너뛰기
        while (current_token(interp).type != TOKEN_SEMICOLON && current_token(interp).type != TOKEN_EOF) {
            advance_interp(interp);
        }
        advance_interp(interp); // skip ;
        
        // 증가식 시작 위치
        int incr_start = interp->pos;
        
        // ) 까지 건너뛰기
        while (current_token(interp).type != TOKEN_RPAREN && current_token(interp).type != TOKEN_EOF) {
            advance_interp(interp);
        }
        int incr_end = interp->pos;
        advance_interp(interp); // skip )
        
        // { 건너뛰기
        advance_interp(interp);
        
        // 본문 시작 위치
        int body_start = interp->pos;
        
        // } 찾기
        int brace_count = 1;
        while (brace_count > 0 && current_token(interp).type != TOKEN_EOF) {
            if (current_token(interp).type == TOKEN_LBRACE) brace_count++;
            if (current_token(interp).type == TOKEN_RBRACE) brace_count--;
            advance_interp(interp);
        }
        int body_end = interp->pos - 1;
        int saved_pos = interp->pos;
        
        // for 루프 실행
        while (true) {
            // 조건 체크
            interp->pos = cond_start;
            Value condition = interpreter_eval_expression(interp);
            if (!value_is_truthy(condition)) break;
            
            // 본문 실행
            interp->pos = body_start;
            while (interp->pos < body_end && !interp->returning) {
                execute_statement(interp);
            }
            if (interp->returning) break;
            
            // 증가식 실행
            interp->pos = incr_start;
            while (interp->pos < incr_end && current_token(interp).type != TOKEN_EOF) {
                execute_statement(interp);
            }
        }
        
        interp->pos = saved_pos;
    }
    else if (token.type == TOKEN_NRET) {
        advance_interp(interp);
        if (current_token(interp).type != TOKEN_RBRACE) {
            interp->return_value = interpreter_eval_expression(interp);
        } else {
            interp->return_value = value_null();
        }
        interp->returning = true;
    }
    else if (token.type == TOKEN_NFUNC) {
        advance_interp(interp);
        Function func;
        strcpy(func.name, current_token(interp).value);
        advance_interp(interp);
        advance_interp(interp); // skip (
        
        func.param_count = 0;
        while (current_token(interp).type != TOKEN_RPAREN) {
            strcpy(func.params[func.param_count++], current_token(interp).value);
            advance_interp(interp);
            if (current_token(interp).type == TOKEN_COMMA) {
                advance_interp(interp);
            }
        }
        advance_interp(interp); // skip )
        advance_interp(interp); // skip {
        
        func.body_start = interp->pos;
        int brace_count = 1;
        while (brace_count > 0) {
            if (current_token(interp).type == TOKEN_LBRACE) brace_count++;
            if (current_token(interp).type == TOKEN_RBRACE) brace_count--;
            advance_interp(interp);
        }
        func.body_end = interp->pos - 1;
        
        interp->functions[interp->function_count++] = func;
    }
}

void interpreter_init(Interpreter* interp, Token* tokens, int count) {
    interp->tokens = tokens;
    interp->pos = 0;
    interp->token_count = count;
    interp->env = env_create(NULL);
    interp->function_count = 0;
    interp->returning = false;
}

void interpreter_run(Interpreter* interp) {
    while (current_token(interp).type != TOKEN_EOF) {
        execute_statement(interp);
    }
}
