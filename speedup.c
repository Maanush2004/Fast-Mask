#include "stdint.h"

// #ifdef __SSE2__
// #include <xmmintrin.h>
// #endif

// typedef struct {
//     uint8_t bytes[4];
// } Mask;
#define ENV64 1

void apply_websocket_mask(int len, char *data, char mask[]) {
    #if defined(ENV32) || defined(ENV64)
    uint32_t m4 = *(uint32_t *)mask;
    // #define N 4
    #endif

    #if defined(ENV64)
    #define N 8
    uint64_t m8 = ((uint64_t)m4 << 32) | (uint64_t)m4;
    #endif

    for (int i = 0; i < (len); i += N) {
        #if defined(ENV32)
        *(uint32_t *)(data + i) = m4 ^ *(uint32_t *)(data + i);
        #elif defined(ENV64)
        *(uint64_t *)(data + i) = m8 ^ *(uint64_t *)(data + i);
        #endif
    }

    // for (int i = len % N; i > 0; i--) {
    //     data[len - i] = mask[i] ^ data[len - i];
    // }
}
