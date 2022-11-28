from cffi import FFI
from pathlib import Path

ffi = FFI()

ffi.cdef("""
        char* apply_websocket_mask(int len, char *data, char mask[]);
""")

ffi.set_source(
    "_speed",
    "#include \"speedup.h\";\n",
    sources = ["speedup.c",],
    include_dirs = [f"{Path(__file__).parent}"],
    extra_compile_args=["-march=native", "-fopenmp"]
)

if __name__ == "__main__":
    ffi.compile(verbose=True)