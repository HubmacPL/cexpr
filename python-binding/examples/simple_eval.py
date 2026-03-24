#!/usr/bin/env python3
"""Simple examples to evaluate expressions with cexpr.

Usage:
  python3 simple_eval.py --expr "sin(x)+x*x" --range -5 5 11
  python3 simple_eval.py --expr "x*x+1" --x 3
"""
import sys
import argparse

try:
    import cexpr
except Exception:
    print('cexpr module not found. Install the package (e.g. pip install <wheel> or use PyCexpr-Installation).')
    raise


def main():
    p = argparse.ArgumentParser(description='Simple cexpr evaluation examples')
    p.add_argument('-e', '--expr', default='sin(x)+x*x', help='expression in x')
    p.add_argument('--x', type=float, help='evaluate for single x')
    p.add_argument('--range', nargs=3, type=float, metavar=('START', 'END', 'N'),
                   help='evaluate over range: start end count')
    args = p.parse_args()

    if args.x is not None:
        try:
            r = cexpr.evaluate_with_x(args.expr, float(args.x))
        except Exception as e:
            print(f"Error evaluating expression '{args.expr}' at x={args.x}: {e}")
            sys.exit(2)
        print(r)
        return

    # default to range if not provided
    if args.range:
        start, end, n = args.range
    else:
        start, end, n = -5.0, 5.0, 11

    # validate count
    try:
        n_int = int(n)
        if n_int < 2:
            raise ValueError('count must be >= 2')
    except Exception as e:
        print('Invalid range count:', e)
        sys.exit(2)

    try:
        import numpy as np
        xs = np.linspace(start, end, n_int)
    except Exception:
        # fallback to simple list if numpy not available
        xs = [start + i * (end - start) / (n_int - 1) for i in range(n_int)]

    for xv in xs:
        try:
            y = cexpr.evaluate_with_x(args.expr, float(xv))
        except Exception as e:
            print(f"{xv}\tERROR: {e}")
            continue
        print(f"{xv}\t{y}")


if __name__ == '__main__':
    main()
