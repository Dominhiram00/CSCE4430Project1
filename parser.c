#include <stdio.h>
#include "parser.h"

int yylval;
int lookahead;

void error() {
    fprintf(stderr, "Syntax error\n");
    exit(1);
}

void match(int token) {
    if (lookahead == token) lookahead = yylex();
    else error();
}

Node* expression();
Node* term();
Node* factor();

Node* newIntegerNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = TYPE_INTEGER;
    node->value = value;
    return node;
}

Node* newBinaryOpNode(int opToken, Node* left, Node* right) {
    char operator;
    switch (opToken) {
        case PLUS: operator = '+'; break;
        case MINUS: operator = '-'; break;
        case MULTIPLY: operator = '*'; break;
        case DIVIDE: operator = '/'; break;
        default: operator = '?'; // Unknown operator
    }

    Node* node = (Node*)malloc(sizeof(Node));
    node->type = TYPE_BINARY_OP;
    node->bin_op.operator = operator;
    node->bin_op.left = left;
    node->bin_op.right = right;
    return node;
}

Node* factor() {
    if (lookahead == INTEGER) {
        Node* node = newIntegerNode(yylval);
        match(INTEGER);
        return node;
    } else if (lookahead == LPAREN) {
        match(LPAREN);
        Node* e = expression();
        match(RPAREN);
        return e;
    } else {
        error();
        return NULL;
    }
}

Node* term() {
    Node* n = factor();
    while (lookahead == MULTIPLY || lookahead == DIVIDE) {
        int op = lookahead;
        match(op);
        n = newBinaryOpNode(op, n, factor());
    }
    return n;
}

Node* expression() {
    Node* n = term();
    while (lookahead == PLUS || lookahead == MINUS) {
        int op = lookahead;
        match(op);
        n = newBinaryOpNode(op, n, term());
    }
    return n;
}

void printAST(Node* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) printf("    ");
    
    if (node->type == TYPE_INTEGER) {
        printf("%d(int)\n", node->value);
    } else if (node->type == TYPE_BINARY_OP) {
        const char* opStr = "";
        switch (node->bin_op.operator) {
            case '+': opStr = "+ (Add)"; break;
            case '-': opStr = "- (Minus)"; break;
            case '*': opStr = "* (Multiply)"; break;
            case '/': opStr = "/ (Divide)"; break;
            default: opStr = "? (Unknown)";
        }
        printf("%s\n", opStr);
        printAST(node->bin_op.left, level + 1);
        printAST(node->bin_op.right, level + 1);
    }
}

int main() {
    lookahead = yylex();
    Node* root = expression();
    printAST(root, 0);
    // Freeing the AST should be done here
    return 0;
}
