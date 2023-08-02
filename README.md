# Fast mask

CPU benchmark for SIMD

### Command to compile

For 256-bit vector :
> gcc -O3 -mavx2 speedup.c

For 128-bit vector :
> gcc -O3 -msse -msse2 speedup.c
