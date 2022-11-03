#include "lab3.h"


int main() {
    int threadCount;
    int rowMatrix;
    int colMatrix;
    int rowFilter;
    int colFilter;
    int counter;

    std::cin >> threadCount;

    std::cin >> rowMatrix >> colMatrix;
    TMatrix matrix(rowMatrix, std::vector <float>(colMatrix));
    ReadMatrix(matrix);

    std::cin >> rowFilter >> colFilter;
    TMatrix filter(rowFilter, std::vector<float>(colFilter));
    ReadMatrix(filter);

    std::cin >> counter;

    TMatrix resultDilation = matrix;
    TMatrix resultErosion = matrix;

    DilationMatrix(matrix, filter, resultDilation, threadCount, counter);
    ErosionMatrix(matrix, filter, resultErosion, threadCount, counter);

    WriteMatrix(resultDilation);
    WriteMatrix(resultErosion);
}