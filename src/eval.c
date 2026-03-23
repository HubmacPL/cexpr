#include <stdio.h>
#include <math.h>
#include "calc_internal.h"

double eval_node(Node* n){
    if (!n) return 0.0;
    if (n->type == NODE_NUMBER) return n->value;
    if (n->type == NODE_UNARY){
        double v = eval_node(n->left);
        if (n->op == '-') return -v;
        if (n->op == 's') return v * v;
        return v;
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
