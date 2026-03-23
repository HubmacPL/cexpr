#include <stdlib.h>
#include "calc_internal.h"

Node* node_number(double v){
    Node* n = malloc(sizeof *n);
    if (!n) return NULL;
    n->type = NODE_NUMBER; n->value = v; n->op = 0; n->left = n->right = NULL; return n;
}
Node* node_unary(char op, Node* child){
    Node* n = malloc(sizeof *n); if (!n) return NULL;
    n->type = NODE_UNARY; n->op = op; n->left = child; n->right = NULL; return n;
}
Node* node_binary(char op, Node* l, Node* r){
    Node* n = malloc(sizeof *n); if (!n) return NULL;
    n->type = NODE_BINARY; n->op = op; n->left = l; n->right = r; return n;
}

void free_node(Node* n){
    if (!n) return;
    free_node(n->left);
    free_node(n->right);
    free(n);
}
