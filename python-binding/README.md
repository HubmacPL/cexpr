# Python bindings for cexpr

This folder contains sources and usage notes for the CPython extension that wraps the `cexpr` C library.

## Quick Overview

- Module name: `cexpr`
- Exposed functions:
  - `cexpr.evaluate(expr: str) -> float` — evaluate expression without variables
  - `cexpr.evaluate_with_x(expr: str, x: float) -> float` — evaluate expression with variable `x`

## Installation

Recommended: install a prebuilt wheel (fast, no compilation). Wheels for supported platforms are produced in `dist/` or in `PyCexpr-Installation/`.

System-wide installation (may require `--break-system-packages` on Debian/Ubuntu):

```bash
sudo python3 -m pip install dist/cexpr-<version>-<tag>.whl --break-system-packages
```

Recommended (isolated):

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install dist/cexpr-<version>-<tag>.whl
```

If you must build from source (other platform / no wheel available):

```bash
# prerequisites (Debian/Ubuntu)
sudo apt install build-essential python3-dev

# build and install
python3 -m pip install --upgrade build wheel setuptools
python3 -m build
python3 -m pip install dist/cexpr-*.whl
```

## Usage examples

Simple import (when module is installed):

```python
import cexpr
print(cexpr.evaluate("1+2"))          # -> 3.0
print(cexpr.evaluate_with_x("x*x", 3)) # -> 9.0
```

If you are developing in the repo and did not install the package, add the binding folder to `sys.path` at runtime:

```python
import sys
sys.path.insert(0, 'python-binding')  # run from repo root
import cexpr
```

Example: evaluate many x values (vectorized with numpy):

```python
import sys
sys.path.insert(0, 'python-binding')
import cexpr
import numpy as np

xs = np.linspace(-5, 5, 11)
ys = [cexpr.evaluate_with_x('sin(x) + x*x', float(x)) for x in xs]
print(list(zip(xs, ys)))
```

## API reference

- `evaluate(expr: str) -> float` — parses and evaluates `expr`. On error may return `nan`.
- `evaluate_with_x(expr: str, x: float) -> float` — same as above but variable `x` is set to provided value.

Supported functions and operators mirror the C library (see project root README).

## Troubleshooting

- `Python.h: No such file or directory` — install Python dev headers (`sudo apt install python3-dev`).
- Wheel incompatibility (`cp37`, `cp38`, etc) — build from source on target platform or provide a matching wheel.

## Examples & installer

Prebuilt wheel and a simple installer script are available in `PyCexpr-Installation/` for convenience.

## Files of interest

- `cexprmodule.c` — CPython extension wrapper.
- `requirements.txt` — example deps (`numpy`, `matplotlib`) if you add plotting examples.


