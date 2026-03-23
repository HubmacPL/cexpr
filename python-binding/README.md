CPython extension bindings for cexpr

This folder contains a CPython extension scaffold and an example plot script.

Quick start:
1. Build the static library and extension module:

   make
   make pyext

   - `make` builds `build/libcexpr.a` and `build/calc_test`.
   - `make pyext` builds the CPython extension `python-binding/cexpr.so` (requires Python development headers and `python3-config`).

2. Install Python deps:

   python3 -m pip install -r python-binding/requirements.txt

3. Run example:

   python3 python-binding/plot_expr.py

Notes:
- If `make pyext` fails with `Python.h: No such file or directory`, install Python development headers (e.g. `sudo apt install python3-dev` on Debian/Ubuntu) and ensure `python3-config` is available.
- On Windows you will need an appropriate build toolchain (MSVC or MinGW) and may need to build a `.pyd` instead; instructions vary by environment.

Files:
- `cexprmodule.c` — CPython extension source.
- `plot_expr.py` — example that imports the `cexpr` module and plots f(x).
- `requirements.txt` — numpy, matplotlib
