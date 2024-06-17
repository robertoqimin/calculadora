#ifndef CALCULADORA_H
#define CALCULADORA_H

typedef struct {
    char posFixa[512];  // Express�o na forma p�s-fixada, como 3 12 4 + *
    char inFixa[512];   // Express�o na forma infixada, como 3 * (12 + 4)
    float valor;        // Valor num�rico da express�o
} Expressao;

char *getFormaInFixa(const char *str);   // Retorna a forma infixada de uma express�o p�s-fixada
float getValor(const char *str);         // Calcula o valor de uma express�o p�s-fixada

#endif
