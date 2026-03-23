import numpy as np
import matplotlib.pyplot as plt
from ctypes_wrapper import evaluate

expr = input('Enter expression in x (e.g. sin(x) + x*x): ').strip()
if not expr:
    expr = 'sin(x) + x*x'

xs = np.linspace(-10, 10, 400)
ys = []
for xv in xs:
    try:
        y = evaluate(expr, float(xv))
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
