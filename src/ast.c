#include <stdlib.h>
#include "calc_internal.h"
#include <string.h>

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

Node* node_function(const char *name, Node* arg){
    Node* n = malloc(sizeof *n); if (!n) return NULL;
    n->type = NODE_FUNCTION;
    n->op = 0;
    n->left = arg;
    n->right = NULL;
    n->fname = NULL;
    if (name){
        n->fname = malloc(strlen(name) + 1);
        if (n->fname) strcpy(n->fname, name);
    }
    return n;
}

Node* node_variable(const char *name){
    Node* n = malloc(sizeof *n); if (!n) return NULL;
    n->type = NODE_VARIABLE;
    n->op = 0;
    n->left = NULL;
    n->right = NULL;
    n->fname = NULL;
    if (name){
        n->fname = malloc(strlen(name) + 1);
        if (n->fname) strcpy(n->fname, name);
    }
    return n;
}

void free_node(Node* n){
    if (!n) return;
    free_node(n->left);
    free_node(n->right);
    if ((n->type == NODE_FUNCTION || n->type == NODE_VARIABLE) && n->fname) free(n->fname);
    free(n);
}
