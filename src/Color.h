#pragma once

#include "Types.h"

using Rgba = uint32_t;

Rgba Rgb(uint8_t r, uint8_t g, uint8_t b);
Rgba HsvToRgb(uint8_t h, uint8_t s, uint8_t v);
