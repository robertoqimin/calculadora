#ifndef CALCULADORA_H
#define CALCULADORA_H

typedef struct {
    char posFixa[512];  // Expressão na forma pós-fixada, como 3 12 4 + *
    char inFixa[512];   // Expressão na forma infixada, como 3 * (12 + 4)
    float valor;        // Valor numérico da expressão
} Expressao;

char *getFormaInFixa(const char *str);   // Retorna a forma infixada de uma expressão pós-fixada
float getValor(const char *str);         // Calcula o valor de uma expressão pós-fixada

#endif
