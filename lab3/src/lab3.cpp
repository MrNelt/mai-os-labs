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
            int rowTemp = rowBegin + j;
            int colTemp = colBegin + i;
            if (!(rowTemp >= 0 && rowTemp < (int)matrix[0].size() && colTemp >= 0 && colTemp < (int)matrix.size() && filter[i][j] == matrix[rowTemp][colTemp])) {
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
            int rowTemp = rowBegin + j;
            int colTemp = colBegin + i;
            if (rowTemp >= 0 && rowTemp < (int)matrix[0].size() && colTemp >= 0 && colTemp < (int)matrix.size() && rowTemp != row && colTemp != col) {
                //мютекс лок
                resultMatrix[rowTemp][colTemp] += filter[i][j];
                //мютекс анлок
            }
        }
    }
}