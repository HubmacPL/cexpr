// Internal header shared between tokenizer/parser/ast/eval implementations
#ifndef CALC_INTERNAL_H
#define CALC_INTERNAL_H

#include <stddef.h>

#define MAX_TOKENS 128

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN
} TokenType;

typedef struct {
    TokenType type;
    double value; // for numbers
    char operator; // for operators
} Token;

typedef enum { NODE_NUMBER, NODE_UNARY, NODE_BINARY } NodeType;
typedef struct Node {
    NodeType type;
    double value;
    char op;
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
void free_node(Node* n);

/* eval */
double eval_node(Node* n);

#endif // CALC_INTERNAL_H
