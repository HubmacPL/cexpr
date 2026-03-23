import platform
from ctypes import CDLL, c_char_p, c_double
import os

def load_lib():
    system = platform.system()
    if system == 'Windows':
        libname = 'cexpr.dll'
        path = os.path.join('build', libname)
    else:
        libname = 'libcexpr.so'
        path = os.path.join('build', libname)
    if not os.path.exists(path):
        raise FileNotFoundError(f"Library not found: {path}. Build it with 'make shared'.")
    lib = CDLL(path)
    lib.evaluate_expression_with_x.argtypes = [c_char_p, c_double]
    lib.evaluate_expression_with_x.restype = c_double
    return lib

_lib = None

def ensure():
    global _lib
    if _lib is None:
        _lib = load_lib()
    return _lib

def evaluate(expr: str, x: float = 0.0) -> float:
    lib = ensure()
    b = expr.encode('utf-8')
    return lib.evaluate_expression_with_x(c_char_p(b), c_double(x))

if __name__ == '__main__':
    print(evaluate('sin(x) + x*x', 2.0))
