// Internal header shared between tokenizer/parser/ast/eval implementations
#ifndef CALC_INTERNAL_H
#define CALC_INTERNAL_H

#include <stddef.h>

#define MAX_TOKENS 128

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENT,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN
} TokenType;

typedef struct {
    TokenType type;
    double value; // for numbers
    char operator; // for operators
    char name[32]; // for identifiers (function names)
} Token;

typedef enum { NODE_NUMBER, NODE_UNARY, NODE_BINARY, NODE_FUNCTION, NODE_VARIABLE } NodeType;
typedef struct Node {
    NodeType type;
    double value;
    char op;
    char *fname; /* for function and variable nodes */
    struct Node *left, *right;
} Node;

/* tokenizer */
int tokenize(const char* expression, Token* tokens, int* token_count);

/* parser */
Node* parse_expression(Token* tokens, int *pos, int token_count);

/* ast helpers */
Node* node_number(double v);
Node* node_unary(char op, Node* child);
Node* node_binary(char op, Node* l, Node* r);
Node* node_function(const char *name, Node* arg);
Node* node_variable(const char *name);
void free_node(Node* n);

/* eval */
double eval_node(Node* n);

#endif // CALC_INTERNAL_H
