#include "lab3.h"
#include "utils.h"

#include <pthread.h>

void CheckingAround(int row, int col, TMatrix&matrix, TMatrix&filter, TMatrix&resultMatrix){
    // координаты для проверки, row и col "приделываем к центру filter"
    int rowBegin = row - filter[0].size() / 2;
    int colBegin = col - filter.size() / 2;
    int flag = 1;
    for (int i = 0; i < (int)filter.size(); i++) {
        if (!flag) {
            break;
        }
        for (int j = 0; j < (int)filter[i].size(); j++) {
            int rowTemp = rowBegin + i;
            int colTemp = colBegin + j;
            if (!(rowTemp >= 0 && rowTemp < (int)matrix.size() && colTemp >= 0 && colTemp < (int)matrix[0].size() && filter[i][j] == matrix[rowTemp][colTemp])) {
                flag = 0;
                break;
            }
        }
    }
    if (!flag) {
        resultMatrix[row][col] = 0;
    }
}

void SummingAround(int row, int col, TMatrix&matrix, TMatrix&filter, TMatrix&resultMatrix) {
    // координаты для суммирования, row и col "приделываем к центру filter"
    int rowBegin = row - filter[0].size() / 2;
    int colBegin = col - filter.size() / 2;
    for (int i = 0; i < (int)filter.size(); i++) {
        for (int j = 0; j < (int)filter[i].size(); j++) {
            int rowTemp = rowBegin + i;
            int colTemp = colBegin + j;
            if (rowTemp >= 0 && rowTemp < (int)matrix.size() && colTemp >= 0 && colTemp < (int)matrix[0].size()) {
                //мютекс лок
                resultMatrix[rowTemp][colTemp] += filter[i][j];
                //мютекс анлок
            }
        }
    }
}

void WriteMatrix(TMatrix &matrix) {
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix.size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void ReadMatrix(TMatrix &matrix) {
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix.size(); j++) {
            std::cin >> matrix[i][j];
        }
    }
}
