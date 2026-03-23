#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../include/cexpr.h"

/* Wrapper: evaluate_expression(const char*) -> double */
static PyObject *py_evaluate(PyObject *self, PyObject *args){
    const char *expr;
    if (!PyArg_ParseTuple(args, "s", &expr)) return NULL;
    double r = evaluate_expression_with_x(expr, 0.0);
    return PyFloat_FromDouble(r);
}

/* Wrapper: evaluate_expression_with_x(const char*, double) -> double */
static PyObject *py_evaluate_with_x(PyObject *self, PyObject *args){
    const char *expr;
    double x;
    if (!PyArg_ParseTuple(args, "sd", &expr, &x)) return NULL;
    double r = evaluate_expression_with_x(expr, x);
    return PyFloat_FromDouble(r);
}

static PyMethodDef CexprMethods[] = {
    {"evaluate", py_evaluate, METH_VARARGS, "Evaluate expression (no variables)"},
    {"evaluate_with_x", py_evaluate_with_x, METH_VARARGS, "Evaluate expression with variable x"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cexprmodule = {
    PyModuleDef_HEAD_INIT,
    "cexpr",
    "C Expression evaluator bindings",
    -1,
    CexprMethods
};

PyMODINIT_FUNC PyInit_cexpr(void){
    return PyModule_Create(&cexprmodule);
}
