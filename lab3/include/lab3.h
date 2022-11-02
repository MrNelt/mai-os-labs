#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>
#include <iostream>

using TMatrix = std::vector<std::vector<int>>;

void CheckingAround(int row, int col, TMatrix&matrix, TMatrix&filter, TMatrix&resultMatrix);

void SummingAround(int row, int col, TMatrix&matrix, TMatrix&filter, TMatrix&resultMatrix);

#endif //OS_LABS_LAB3_H