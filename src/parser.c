#include <stdio.h>
#include <string.h>
#include "calc_internal.h"

static Node* parse_factor(Token* tokens, int *pos, int token_count){
    if (*pos >= token_count) return NULL;
    Token t = tokens[*pos];
    if (t.type == TOKEN_NUMBER){
        (*pos)++;
        return node_number(t.value);
    }
    if (t.type == TOKEN_IDENT){
        /* identifier: either function call name(expr) or variable */
        char fname[32];
        strncpy(fname, t.name, sizeof fname);
        fname[sizeof fname - 1] = '\0';
        (*pos)++;
        if (*pos < token_count && tokens[*pos].type == TOKEN_LPAREN){
            (*pos)++; /* skip '(' */
            Node* arg = parse_expression(tokens, pos, token_count);
            if (*pos < token_count && tokens[*pos].type == TOKEN_RPAREN) (*pos)++;
            else { fprintf(stderr, "Nieprawidłowa składnia: brak nawiasu zamykającego po funkcji %s\n", fname); }
            return node_function(fname, arg);
        } else {
            /* treat as variable */
            return node_variable(fname);
        }
    }
    if (t.type == TOKEN_LPAREN){
        (*pos)++;
        Node* n = parse_expression(tokens, pos, token_count);
        if (*pos < token_count && tokens[*pos].type == TOKEN_RPAREN) (*pos)++;
        else { fprintf(stderr, "Nieprawidłowa składnia: brak nawiasu zamykającego\n"); }
        return n;
    }
    if (t.type == TOKEN_OPERATOR && t.operator == '-'){
        (*pos)++;
        Node* child = parse_factor(tokens, pos, token_count);
        return node_unary('-', child);
    }
    return NULL;
}

static Node* parse_power(Token* tokens, int *pos, int token_count){
    Node* left = parse_factor(tokens, pos, token_count);
    if (!left) return NULL;
    // postfix square 's'
    while (*pos < token_count && tokens[*pos].type == TOKEN_OPERATOR && tokens[*pos].operator == 's'){
        (*pos)++;
        left = node_unary('s', left);
    }
    if (*pos < token_count && tokens[*pos].type == TOKEN_OPERATOR && tokens[*pos].operator == '^'){
        (*pos)++;
        Node* right = parse_power(tokens, pos, token_count);
        return node_binary('^', left, right);
    }
    return left;
}

static Node* parse_term(Token* tokens, int *pos, int token_count){
    Node* node = parse_power(tokens, pos, token_count);
    while (*pos < token_count && tokens[*pos].type == TOKEN_OPERATOR && (tokens[*pos].operator == '*' || tokens[*pos].operator == '/')){
        char op = tokens[*pos].operator; (*pos)++;
        Node* right = parse_power(tokens, pos, token_count);
        node = node_binary(op, node, right);
    }
    return node;
}

Node* parse_expression(Token* tokens, int *pos, int token_count){
    Node* node = parse_term(tokens, pos, token_count);
    while (*pos < token_count && tokens[*pos].type == TOKEN_OPERATOR && (tokens[*pos].operator == '+' || tokens[*pos].operator == '-')){
        char op = tokens[*pos].operator; (*pos)++;
        Node* right = parse_term(tokens, pos, token_count);
        node = node_binary(op, node, right);
    }
    return node;
}
