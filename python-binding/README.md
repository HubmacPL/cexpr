Python bindings (ctypes) for cexpr

This folder contains a minimal ctypes-based wrapper and an example plot script.

Quick start:
1. Build shared library:

   make shared

   resulting file: build/libcexpr.so (Linux/macOS) or create a DLL on Windows.

2. Install Python deps:

   python3 -m pip install -r python-binding/requirements.txt

3. Run example:

   python3 python-binding/plot_expr.py

Files:
- `ctypes_wrapper.py` — simple ctypes loader and helper `evaluate(expr, x)`.
- `plot_expr.py` — example that plots expression over range using matplotlib.
- `requirements.txt` — numpy, matplotlib
