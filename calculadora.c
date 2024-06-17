#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calculadora.h"

#define MAXPILHA 512
#define PI 3.14159

typedef struct {
    char *pilha[MAXPILHA];
    int topo;
} PilhaString;

typedef struct {
    float pilha[MAXPILHA];
    int topo;
} PilhaFloat;

void inicializaPilhaString(PilhaString *p) {
    p->topo = -1;
}

int pilhaStringVazia(PilhaString *p) {
    return p->topo == -1;
}

int pilhaStringCheia(PilhaString *p) {
    return p->topo == MAXPILHA - 1;
}

void empilhaString(PilhaString *p, char *val) {
    if (!pilhaStringCheia(p)) {
        p->pilha[++(p->topo)] = val;
    }
}

char *desempilhaString(PilhaString *p) {
    if (!pilhaStringVazia(p)) {
        return p->pilha[(p->topo)--];
    }
    return NULL;
}

void inicializaPilhaFloat(PilhaFloat *p) {
    p->topo = -1;
}

int pilhaFloatVazia(PilhaFloat *p) {
    return p->topo == -1;
}

int pilhaFloatCheia(PilhaFloat *p) {
    return p->topo == MAXPILHA - 1;
}

void empilhaFloat(PilhaFloat *p, float val) {
    if (!pilhaFloatCheia(p)) {
        p->pilha[++(p->topo)] = val;
    }
}

float desempilhaFloat(PilhaFloat *p) {
    if (!pilhaFloatVazia(p)) {
        return p->pilha[(p->topo)--];
    }
    return 0.0;
}

float getValor(const char *str) {
    PilhaFloat pilha;
    inicializaPilhaFloat(&pilha);

    char expressao[512];
    strncpy(expressao, str, 512);
    char *token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhaFloat(&pilha, atof(token));
        } else if (strcmp(token, "log") == 0) {
            float op = desempilhaFloat(&pilha);
            float resultado = log10f(op);
            empilhaFloat(&pilha, resultado);
        } else if (strcmp(token, "sen") == 0) {
            float op = desempilhaFloat(&pilha);
            float resultado = sin(op * PI / 180.0);
            empilhaFloat(&pilha, resultado);
        } else if (strcmp(token, "cos") == 0) {
            float op = desempilhaFloat(&pilha);
            float resultado = cos(op * PI / 180.0);
            empilhaFloat(&pilha, resultado);
        } else if (strcmp(token, "tg") == 0) {
            float op = desempilhaFloat(&pilha);
            float resultado = tan(op * PI / 180.0);
            empilhaFloat(&pilha, resultado);
        } else {
            float op2 = desempilhaFloat(&pilha);
            float op1 = desempilhaFloat(&pilha);
            float resultado;

            switch (token[0]) {
                case '+':
                    resultado = op1 + op2;
                    break;
                case '-':
                    resultado = op1 - op2;
                    break;
                case '*':
                    resultado = op1 * op2;
                    break;
                case '/':
                    resultado = op1 / op2;
                    break;
                case '^':
                    resultado = powf(op1, op2);
                    break;
                default:
                    printf("inválido: %s\n", token);
                    return 0;
            }
            empilhaFloat(&pilha, resultado);
        }
        token = strtok(NULL, " ");
    }

    return desempilhaFloat(&pilha);
}

char *getFormaInFixa(const char *str) {
    PilhaString pilha;
    inicializaPilhaString(&pilha);

    char expressao[512];
    strncpy(expressao, str, 512);
    char *token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            char *num = (char *)malloc(strlen(token) + 1);
            strcpy(num, token);
            empilhaString(&pilha, num);
        } else if (strcmp(token, "log") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0) {
            char *op = desempilhaString(&pilha);

            int newSize = strlen(op) + strlen(token) + 3;
            char *newExpr = (char *)malloc(newSize);
            snprintf(newExpr, newSize, "%s(%s)", token, op);

            free(op);
            empilhaString(&pilha, newExpr);
        } else {
            char *op2 = desempilhaString(&pilha);
            char *op1 = desempilhaString(&pilha);

            int newSize = strlen(op1) + strlen(op2) + strlen(token) + 4;
            char *newExpr = (char *)malloc(newSize);
            snprintf(newExpr, newSize, "(%s %s %s)", op1, token, op2);

            free(op1);
            free(op2);
            empilhaString(&pilha, newExpr);
        }
        token = strtok(NULL, " ");
    }

    char *resultado = desempilhaString(&pilha);
    return resultado;
}
