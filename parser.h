#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

typedef enum {
    INTEGER = 256, PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, UNKNOWN
} TokenType;

typedef enum { TYPE_INTEGER, TYPE_BINARY_OP } NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value; // For integer nodes
        struct { // For binary operation nodes
            char operator; // Operator character: '+', '-', '*', '/'
            struct Node* left;
            struct Node* right;
        } bin_op;
    };
} Node;

extern int yylval;
int yylex(void);

#endif
