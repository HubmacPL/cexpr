from setuptools import setup, Extension
from glob import glob

sources = glob('src/*.c') + ['python-binding/cexprmodule.c']

cexpr_ext = Extension(
    'cexpr',
    sources=sources,
    include_dirs=['include'],
    extra_compile_args=['-std=c11', '-O2'],
    libraries=['m'],
)

setup(
    name='cexpr',
    version='0.1.0',
    description='C expression evaluator (Python bindings)',
    long_description='CPython extension wrapping the cexpr C library.',
    long_description_content_type='text/markdown',
    ext_modules=[cexpr_ext],
    license='MIT',
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C',
    ],
)
