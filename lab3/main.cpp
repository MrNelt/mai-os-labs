#include "lab3.h"

#include <iostream>

int main() {
    int threadCount;
    int rowMatrix, colMatrix;
    int rowFilter, colFilter;
    int counter;

    std::cin >> threadCount;

    std::cin >> rowMatrix >> colMatrix;
    TMatrix matrix(rowMatrix, std::vector <int>(colMatrix));
    ReadMatrix(matrix);

    std::cin >> rowFilter >> colFilter;
    TMatrix filter(rowFilter, std::vector<int>(colFilter));
    ReadMatrix(filter);

    std::cin >> counter;

    TMatrix resultDilation = matrix;
    TMatrix resultErosion = matrix;

    DilationMatrix(matrix, filter, resultDilation, threadCount, counter);
    ErosionMatrix(matrix, filter, resultErosion, threadCount, counter);

    WriteMatrix(resultDilation);
    WriteMatrix(resultErosion);
}