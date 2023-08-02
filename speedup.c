#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include <immintrin.h>

// #define ENV64 1
// #define NOSSE 1
// #define NOAVX 1

void apply_websocket_mask(int len, char *data, char mask[]) {
    #if (!defined(__SSE2__) || defined(NOSSE))
        uint32_t m4 = *(uint32_t *)mask;
        #define N 4

        #if defined(ENV64)
        #undef N
        #define N 8
        uint64_t m8 = ((uint64_t)m4 << 32) | (uint64_t)m4;
        #endif

        for (int i = 0; i < (len); i += N) {
            #if !defined(ENV64)
            *(uint32_t *)(data + i) = m4 ^ *(uint32_t *)(data + i);
            #else
            *(uint64_t *)(data + i) = m8 ^ *(uint64_t *)(data + i);
            #endif
        }
    #elif defined(NOAVX)
    // printf("%s", "1\0");
    uint32_t m4 = *(uint32_t *)mask;
    const __m128i lol = _mm_set1_epi32(m4);
    // printf("For real?\n");
    // printf("%lu\n", (size_t)mask % 32);

    for (int i = 0; i < len; i += 128 / 8) {
        __m128i in =  _mm_load_si128((__m128i *)(data + i));
        __m128i out = _mm_xor_si128(lol, in);
        _mm_store_si128((__m128i *)(data + i), out);
    }
    return;
    #else
    uint32_t m4 = *(uint32_t *)mask;
    const __m256i lol = _mm256_set1_epi32(m4);

    for (int i = 0; i < len; i += 32) {
        __m256i in =  _mm256_loadu_si256((__m256i *)(data + i));
        __m256i out = _mm256_xor_si256(lol, in);
        _mm256_storeu_si256((__m256i *)(data + i), out);
    }
    return;
    #endif
}

#define G 3

int main() {
	long long int s=1000000000;
	FILE *fp = fopen("/dev/urandom", "r");
	void *bytes = malloc(s);
	fread(bytes, 1, s, fp);
	char *by = (char *)bytes;
	char mask[4] = "1234";
	clock_t start,end;
	start = clock();
	for (int i=0; i < G; i++) {
		apply_websocket_mask(s, by, mask);
	}
	end = clock();	
	double time_taken = ((double)(end - start)) / ((double)CLOCKS_PER_SEC);
	printf("time: %lf\n", time_taken);
	printf("Speed : %lf\n", (s*G)/(time_taken*1073741824));
}
