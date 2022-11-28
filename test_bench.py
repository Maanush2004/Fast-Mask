import _speed

_XOR_TABLE = [bytes(a^b for a in range(256)) for b in range(256)]

def apply_websocket_mask(mask, data):
    data_bytes = bytearray(data)
    for index in range(4):
        data_bytes[index::4] = data_bytes[index::4].translate(_XOR_TABLE[mask[index]])
    return data_bytes

s = 10**6
d = open("/dev/random", "rb").read(s)
# s = 10
# d = b"1" * s
m = bytes("wjdi", "utf")
n = 201
# print(d[0:10])

x = _speed.lib.apply_websocket_mask # type: ignore

from time import perf_counter as t

t1 = t()
for _ in range(n):
    apply_websocket_mask(m, d)
tt1 = t() - t1
k = apply_websocket_mask(m, d)
l = len(d)

# print(hex(int.from_bytes(d, "little")))
print(tt1, "Pythong", (l * n) / (tt1 * (10 ** 9)), "GB / s")

t1 = t()
for _ in range(n):
    x(l, d, m)
    # print(d[0:10])
tt2 = t() - t1

l = len(d)

print(tt2, "CFFI", (l * n) / (tt2 * (10 ** 9)), "GB / s")

print(tt1 / tt2, "times faster")
print(d == k, d[0:10], k[0: 10])
# print(d == k, hex(int.from_bytes(d, "little")), hex(int.from_bytes(k, "little")))