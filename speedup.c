#include "stdint.h"

// #ifdef __SSE2__
// #include <xmmintrin.h>
// #endif

// typedef struct {
//     uint8_t bytes[4];
// } Mask;


void apply_websocket_mask(int len, char *data, char mask[]) {
    for (int i = 0; i < (len / 4); i++) {
        data[i] = mask[0] ^ data[i];
        data[i + 1] = mask[1] ^ data[i + 1];
        data[i + 2] = mask[2] ^ data[i + 2];
        data[i + 3] = mask[3] ^ data[i + 3];
    }

    for (int i = len % 4; i > 0; i--) {
        data[len - i] = mask[i] ^ data[len - i];
    }
}
