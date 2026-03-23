# cexpr

A lightweight C library for parsing and evaluating mathematical expressions using an AST-based engine. Designed for performance, clean API usage, and easy integration with Python via bindings. Supports operators, precedence, functions and variables.

## Quick overview
- Public API: `double evaluate_expression(const char *expr)`
- Variable API: `double evaluate_expression_with_x(const char *expr, double x)` — evaluate expression with variable `x` set to a value.

Supported features:
- Numbers (integers and decimals)
- Binary operators: `+ - * / ^` (power is `^`, right-associative)
- Unary minus and postfix square (superscript `²`)
- Parentheses
- Functions: `sin, cos, tan, sqrt, ln, log, log10, exp, abs`
- Variable: `x`

## Building

Prerequisites:
- `gcc`, `make`
- `python3` and `python3-dev` (for building CPython extension)

Common targets:
- `make` — build static library `build/libcexpr.a` and test binary `build/calc_test`.
- `make shared` — build shared library `build/libcexpr.so` (for ctypes or dynamic linking).
- `make pyext` — build CPython extension `python-binding/cexpr.so` (requires `python3-config` and Python dev headers).
- `make clean` — remove build artifacts.

Example:
```bash
make
make pyext    # optional, to enable Python CPython extension
```

If `make pyext` fails with `Python.h: No such file or directory`, install Python headers, e.g. on Debian/Ubuntu:
```bash
sudo apt update
sudo apt install python3-dev
```

## Using the C API

Include the public header:
```c
#include "include/cexpr.h"
```

Example:
```c
#include <stdio.h>
#include <math.h>
#include "include/cexpr.h"

int main(void){
	const char *expr = "2*x + 3";
	double r = evaluate_expression_with_x(expr, 5.0);
	printf("%s -> %f\n", expr, r);
	return 0;
}
```

## Python bindings (CPython extension)

I provide a CPython extension in `python-binding/cexprmodule.c` which exposes:
- `cexpr.evaluate(expr: str) -> float` — evaluate expression (no variables)
- `cexpr.evaluate_with_x(expr: str, x: float) -> float` — evaluate expression with variable `x`

Build and test the extension:
```bash
make pyext
python3 -c "import sys; sys.path.insert(0,'python-binding'); import cexpr; print(cexpr.evaluate_with_x('2*x+3',5))"
```

Example plotting script: `python-binding/plot_expr.py` — run after `make pyext` and installing Python deps:
```bash
python3 -m pip install -r python-binding/requirements.txt
python3 python-binding/plot_expr.py
```

## Tests

Simple manual tests are available by running the `build/calc_test` binary (after `make`). Use the interactive prompt to evaluate expressions.

## Contributing
- Fork and create a PR. Please follow code style in `src/` and add tests for new features.

## License
MIT

