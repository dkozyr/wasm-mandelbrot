#pragma once

#include "Types.h"

extern "C" {
    
void RandSeed(int64_t seed0, int64_t seed1);

}

int64_t Rand();
int RandomInt(int a, int b);
double RandFloat();
