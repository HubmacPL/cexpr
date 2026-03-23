#include <stdio.h>
#include <math.h>
#include "calc_internal.h"
#include <string.h>

/* current value for variable 'x' (set by calc.c before evaluation) */
extern double current_var_x;

double eval_node(Node* n){
    if (!n) return 0.0;
    if (n->type == NODE_NUMBER) return n->value;
    if (n->type == NODE_UNARY){
        double v = eval_node(n->left);
        if (n->op == '-') return -v;
        if (n->op == 's') return v * v;
        return v;
    }
    if (n->type == NODE_FUNCTION){
        double v = eval_node(n->left);
        if (!n->fname) return v;
        if (strcmp(n->fname, "sin") == 0) return sin(v);
        if (strcmp(n->fname, "cos") == 0) return cos(v);
        if (strcmp(n->fname, "tan") == 0) return tan(v);
        if (strcmp(n->fname, "sqrt") == 0) return v < 0.0 ? (fprintf(stderr, "Błąd: sqrt z ujemnej liczby\n"), 0.0) : sqrt(v);
        if (strcmp(n->fname, "ln") == 0) return v <= 0.0 ? (fprintf(stderr, "Błąd: ln z niepozytywnej liczby\n"), 0.0) : log(v);
        if (strcmp(n->fname, "log") == 0) return v <= 0.0 ? (fprintf(stderr, "Błąd: log z niepozytywnej liczby\n"), 0.0) : log10(v);
        if (strcmp(n->fname, "log10") == 0) return v <= 0.0 ? (fprintf(stderr, "Błąd: log10 z niepozytywnej liczby\n"), 0.0) : log10(v);
        if (strcmp(n->fname, "exp") == 0) return exp(v);
        if (strcmp(n->fname, "abs") == 0) return fabs(v);
        /* unknown function */
        fprintf(stderr, "Nieznana funkcja: %s\n", n->fname);
        return 0.0;
    }
    if (n->type == NODE_VARIABLE){
        if (!n->fname) return 0.0;
        if (strcmp(n->fname, "x") == 0) return current_var_x;
        fprintf(stderr, "Nieznana zmienna: %s\n", n->fname);
        return 0.0;
    }
    double a = eval_node(n->left);
    double b = eval_node(n->right);
    switch (n->op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b == 0.0 ? (fprintf(stderr, "Błąd: dzielenie przez zero\n"), 0.0) : a / b;
        case '^': return pow(a, b);
    }
    return 0.0;
}
