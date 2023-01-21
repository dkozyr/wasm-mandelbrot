#include "Color.h"

Rgba Rgb(uint8_t r, uint8_t g, uint8_t b) {
    constexpr Rgba alpha = 0xFF000000;
    return (((Rgba)r)) | (((Rgba)g) << 8) | (((Rgba)b) << 16) | alpha;
}

Rgba HsvToRgb(uint8_t h, uint8_t s, uint8_t v) {
    if(s == 0) {
        return Rgb(v, v, v);
    }
    
    uint8_t region = h / 43;
    uint8_t remainder = (h - (region * 43)) * 6; 
    
    uint8_t p = (v * (255 - s)) >> 8;
    uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
    
    switch(region) {
        case 0: return Rgb(v, t, p);
        case 1: return Rgb(q, v, p);
        case 2: return Rgb(p, v, t);
        case 3: return Rgb(p, q, v);
        case 4: return Rgb(t, p, v);
        default: return Rgb(v, p, q);
    }
    return 0;
}
