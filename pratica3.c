#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* createStack() {
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack* s, double value) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->value = value;
    n->next = s->top;
    s->top = n;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

double pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Erro: pilha vazia!\n");
        exit(1);
    }
    Node* t = s->top;
    double val = t->value;
    s->top = t->next;
    free(t);
    return val;
}

void freeStack(Stack* s) {
    while (!isEmpty(s)) pop(s);
    free(s);
}

double evaluateRPN(char* expr) {
    Stack* s = createStack();
    char* token = strtok(expr, " ");

    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(s, atof(token));
        } else {
            double b = pop(s);
            double a = pop(s);
            double r;

            switch (token[0]) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0) { printf("Erro: divisao por zero.\n"); exit(1); }
                    r = a / b; break;
                default:
                    printf("Erro: operador desconhecido %s\n", token);
                    exit(1);
            }
            push(s, r);
        }
        token = strtok(NULL, " ");
    }

    double result = pop(s);
    if (!isEmpty(s)) {
        printf("Erro: expressao malformada.\n");
        exit(1);
    }
    freeStack(s);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s \"expressao posfixa\"\n", argv[0]);
        return 1;
    }
    char expr[200];
    strcpy(expr, argv[1]);
    printf("Resultado: %.2f\n", evaluateRPN(expr));
    return 0;
}
