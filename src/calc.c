#include <stdio.h>
#include <string.h>
#include "../include/cexpr.h"
#include "calc_internal.h"
#include <math.h>

/* internal evaluator with error reporting */
static double calc_eval_internal(const char *expr, int *err){
    if (err) *err = 0;
    if (!expr){ if (err) *err = 1; return NAN; }
    Token tokens[MAX_TOKENS];
    int token_count = 0;
    if (!tokenize(expr, tokens, &token_count)){
        if (err) *err = 2;
        return NAN;
    }
    int pos = 0;
    Node* root = parse_expression(tokens, &pos, token_count);
    if (!root){
        if (err) *err = 3;
        return NAN;
    }
    double res = eval_node(root);
    free_node(root);
    return res;
}

/* public API */
double evaluate_expression(const char *expr){
    int err = 0;
    double r = calc_eval_internal(expr, &err);
    (void)err; // caller only gets NaN on error
    return r;
}
