#!/usr/bin/env python3
"""Interactive plotter for expressions using the `cexpr` extension.

This script evaluates a mathematical expression (with variable ``x``) over a
numeric range and displays an interactive matplotlib window. It expects the
``cexpr`` extension to be installed (or available on ``sys.path``).

Example:

  python3 plot_eval.py --expr "sin(x)+x*x" --range -10 10 400

The script opens a GUI window (no file is written) unless the environment is
headless; use a virtual display or run locally on a desktop to see the plot.
"""

from __future__ import annotations

import argparse
import sys
from typing import Iterable, Tuple

try:
    import cexpr
except Exception:
    raise SystemExit('cexpr module not found — install the package (see README)')

try:
    import numpy as np
    import matplotlib
    # prefer TkAgg for portability; if unavailable this will raise
    matplotlib.use('TkAgg')
    import matplotlib.pyplot as plt
except Exception:
    raise SystemExit('numpy and matplotlib are required — pip install numpy matplotlib')


def parse_args(argv: Iterable[str] | None = None) -> argparse.Namespace:
    """Parse command-line arguments."""
    p = argparse.ArgumentParser(description='Plot expression using cexpr')
    p.add_argument('-e', '--expr', default='sin(x)+x*x', help='expression in x')
    p.add_argument(
        '--range', nargs=3, type=float, metavar=('START', 'END', 'N'),
        help='numeric range: start end count', default=[-10.0, 10.0, 400],
    )
    return p.parse_args(argv)


def compute_values(expr: str, start: float, end: float, count: int) -> Tuple[np.ndarray, np.ndarray]:
    """Evaluate `expr` at `count` evenly spaced points between `start` and `end`.

    Returns a tuple ``(xs, ys)`` with NumPy arrays. Invalid evaluations are set
    to ``nan`` and do not stop the loop.
    """
    xs = np.linspace(start, end, count)
    ys = np.empty_like(xs)
    for i, x in enumerate(xs):
        try:
            ys[i] = cexpr.evaluate_with_x(expr, float(x))
        except Exception:
            ys[i] = float('nan')
    return xs, ys


def plot_values(xs: np.ndarray, ys: np.ndarray, expr: str) -> None:
    """Create and show a matplotlib plot for the given data."""
    # Ensure no leftover interactive figures exist and disable interactive mode
    try:
        plt.ioff()
    except Exception:
        pass
    try:
        plt.close('all')
    except Exception:
        pass

    fig, ax = plt.subplots()
    ax.plot(xs, ys, label=expr)
    ax.set_title(expr)
    ax.set_xlabel('x')
    ax.set_ylabel('f(x)')
    ax.grid(True)
    ax.legend()

    # Show and then clean up to avoid stray windows
    try:
        plt.show()
    finally:
        try:
            plt.close('all')
        except Exception:
            pass


def main(argv: Iterable[str] | None = None) -> None:
    args = parse_args(argv)

    start, end, n = args.range
    try:
        n_int = int(n)
        if n_int < 2:
            raise ValueError('count must be >= 2')
    except Exception as exc:
        raise SystemExit(f'Invalid range count: {exc}')

    xs, ys = compute_values(args.expr, float(start), float(end), n_int)
    plot_values(xs, ys, args.expr)


if __name__ == '__main__':
    main()
