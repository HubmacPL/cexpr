#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc_internal.h"

int tokenize(const char* expression, Token* tokens, int* token_count){
    int index = 0;
    Token prev_token = {.type = TOKEN_OPERATOR};

    for (int i=0; expression[i] != '\0'; i++){
        if(expression[i] == ' ') continue;

        // superscript ² (UTF-8 C2 B2) as postfix square
        if ((unsigned char)expression[i] == 0xC2 && (unsigned char)expression[i+1] == 0xB2) {
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_OPERATOR;
            tokens[index].operator = 's';
            index++;
            prev_token.type = TOKEN_NUMBER; // postfix produces a number-like token
            i++; // skip second byte
            continue;
        }

        if (isdigit((unsigned char)expression[i]) || (expression[i] == '-' && (prev_token.type == TOKEN_OPERATOR || prev_token.type == TOKEN_LPAREN || index == 0) && (isdigit((unsigned char)expression[i+1]) || expression[i+1]=='.')) || expression[i]=='.'){
            double value = 0;
            int sign = 1;
            if (expression[i] == '-') { sign = -1; i++; }

            while (isdigit((unsigned char)expression[i])){
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            if(expression[i] == '.'){
                double decimal_place = 0.1;
                i++;
                while (isdigit((unsigned char)expression[i])){
                    value += (expression[i] - '0') * decimal_place;
                    decimal_place *= 0.1;
                    i++;
                }
            }
            value *= sign;
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_NUMBER;
            tokens[index].value = value;
            index++;
            prev_token = tokens[index - 1];
            i--;
        }
        else if (isalpha((unsigned char)expression[i])){
            /* identifier/function name */
            int len = 0;
            char buf[31];
            while (isalnum((unsigned char)expression[i]) || expression[i]=='_'){
                if (len < 30) buf[len++] = (char)tolower((unsigned char)expression[i]);
                i++;
            }
            buf[len] = '\0';
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_IDENT;
            strncpy(tokens[index].name, buf, sizeof tokens[index].name);
            tokens[index].name[sizeof tokens[index].name - 1] = '\0';
            index++;
            prev_token = tokens[index - 1];
            i--;
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^'){
            if(prev_token.type == TOKEN_OPERATOR || prev_token.type == TOKEN_LPAREN || index == 0){
                return 0;
            }
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_OPERATOR;
            tokens[index].operator = expression[i];
            index++;
            prev_token = tokens[index - 1];
        }
        else if (expression[i] == '('){
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_LPAREN;
            index++;
            prev_token = tokens[index - 1];
        }
        else if (expression[i] == ')'){
            if (index >= MAX_TOKENS) return 0;
            tokens[index].type = TOKEN_RPAREN;
            index++;
            prev_token = tokens[index - 1];
        }
        else {
            // unknown char
            return 0;
        }
    }
    *token_count = index;
    return 1;
}
