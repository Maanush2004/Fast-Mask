import _speed

dir(_speed)

_XOR_TABLE = [bytes(a^b for a in range(256)) for b in range(256)]

def apply_websocket_mask(mask, data):
    data_bytes = bytearray(data)
    for index in range(4):
        data_bytes[index::4] = data_bytes[index::4].translate(_XOR_TABLE[mask[index]])
    return data_bytes

s = 10**8
d = open("/dev/random", "rb").read(s)
m = bytes("abcd", "utf")
n = 10

x = _speed.lib.apply_websocket_mask # type: ignore

from time import perf_counter as t

t1 = t()
for _ in range(n):
    apply_websocket_mask(m, d)
tt1 = t() - t1

print(tt1, "Pythong", s * n / (tt1 * (10 ** 9)), "GB / s")

l = len(d)

t1 = t()
for _ in range(n):
    x(l, d, m)
tt2 = t() - t1

print(tt2, "CFFI", s * n / (tt2 * (10 ** 9)), "GB / s")

print(tt1 / tt2, "times faster")
