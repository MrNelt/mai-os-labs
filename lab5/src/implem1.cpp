#include "signature.h"

float E(int x) {
    if (x < 0) {
        return -1;
    }
    float e = 1.0;
    for (int i = 0; i < x; ++i) {
        e *= 1 + 1 / static_cast<float>(x);
    }
    return e;
}

float SinIntegral(float a, float b, float e) {
    if (a > b || e > (b - a)) {
        return -1;
    }
    float h = e;
    float w = 0;
    for (float i = a; i <= b; i += e) {
        w += std::sin(i);
    }
    return h * w;
}