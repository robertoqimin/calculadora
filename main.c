#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculadora.c"
#include "calculadora.h"

int main() {
	setlocale(LC_ALL,"");
    Expressao expr;
    strcpy(expr.posFixa, "3 4 + 5 *");

    expr.valor = getValor(expr.posFixa);
    printf("expressão: %f\n", expr.valor);

    char *infixa = getFormaInFixa(expr.posFixa);
    strcpy(expr.inFixa, infixa);
    printf("expressão infixa: %s\n", expr.inFixa);

    free(infixa);
    return 0;
}

