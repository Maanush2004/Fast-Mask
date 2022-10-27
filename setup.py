from setuptools import setup

setup(
    setup_requires=["cffi>=1.0.0"],
    install_requires=["cffi>=1.0.0"],
    cffi_modules = ["binder.py:ffi"]
)