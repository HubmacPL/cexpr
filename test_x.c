#include <stdio.h>
#include "include/cexpr.h"

int main(void){
    const char *expr = "2*x + 3";
    double r = evaluate_expression_with_x(expr, 5.0);
    printf("expr: %s, x=5 -> %f\n", expr, r);
    return 0;
}
