#include "Random.h"

static int64_t shuffle_table[2] = {31415926535, 100000007};

API void RandSeed(int64_t s0, int64_t s1) {
    shuffle_table[0] = s0;
    shuffle_table[1] = s1;
}

int64_t Rand() {
    int64_t s1 = shuffle_table[0];
    int64_t s0 = shuffle_table[1];
    int64_t result = s0 + s1;
    shuffle_table[0] = s0;
    s1 ^= s1 << 23;
    shuffle_table[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
    return (result & 0x7FFFFFFFFFFFFFFF);
}

int RandomInt(int a, int b) { //range: [a, b)
    return a + (Rand() % (b - a));
}

double RandFloat() {
    return (double)Rand() / (double)0x7FFFFFFFFFFFFFFF;
}
