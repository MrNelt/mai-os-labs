#include "signature.h"
#include <iostream>

float E(int x) {
    if (x < 0) {
        return -1;
    }
    float e = 1.0;
    float term = 1.0;
    for (int i = 1; i <= x; ++i) {
        term /= i;
        e += term;
    }
    return e;
}

float SinIntegral(float a, float b, float e) {
    float value = 0;
    for (float i = a; i <= b - e; i += e) {
        value += (std::sin(i) + std::sin(i + e)) / 2;
    }
    return value * e;
}