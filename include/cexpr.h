// Public API for cexpr library (C Expression)
#ifndef CEXPR_H
#define CEXPR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

// Evaluate expression string. Returns computed double value.
// On error returns NaN.
double evaluate_expression(const char *expr);
// Evaluate expression with variable x set to given value
double evaluate_expression_with_x(const char *expr, double x);

#ifdef __cplusplus
}
#endif

#endif // CEXPR_H
