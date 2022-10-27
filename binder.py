from cffi import FFI
from pathlib import Path

ffi = FFI()

ffi.cdef("""
        void apply_websocket_mask(uint64_t len, char *data, char mask[]);
""")

ffi.set_source(
    "_speed",
    "#include \"speedup.h\";\n",
    sources = ["speedup.c",],
    include_dirs = [f"{Path(__file__).parent}"]
)

if __name__ == "__main__":
    ffi.compile(verbose=True)