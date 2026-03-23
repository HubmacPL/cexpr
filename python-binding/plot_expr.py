import sys
import numpy as np
import matplotlib.pyplot as plt

# use CPython extension module 'cexpr' (built with `make pyext`)
sys.path.insert(0, 'python-binding')
import cexpr

expr = input('Enter expression in x (e.g. sin(x) + x*x): ').strip()
if not expr:
    expr = 'sin(x) + x*x'

xs = np.linspace(-10, 10, 400)
ys = []
for xv in xs:
    try:
        y = cexpr.evaluate_with_x(expr, float(xv))
    except Exception as e:
        print('Error evaluating at', xv, e)
        y = float('nan')
    ys.append(y)

plt.plot(xs, ys)
plt.title(expr)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True)
plt.show()
