#include <stdio.h>
#include <string.h>
#include <math.h>
#include "include/cexpr.h"

int main(void){
    char buf[256];
    while (1){
        printf("Wprowadź wyrażenie (lub 'exit' aby zakończyć): ");
        if (!fgets(buf, sizeof buf, stdin)) break;
        size_t n = strlen(buf);
        if (n && buf[n-1] == '\n') buf[n-1] = '\0';
        if (strcmp(buf, "exit") == 0) break;
        double r = evaluate_expression(buf);
        if (isnan(r)) fprintf(stderr, "Błąd podczas obliczania wyrażenia\n");
        else printf("Wynik: %f\n", r);
    }
    return 0;
}
