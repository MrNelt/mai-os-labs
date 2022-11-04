#include "lab3.h"
#include "utils.h"

#include <pthread.h>


pthread_mutex_t mutex;

void CheckingAround(int row, int col, TMatrix&matrix, TMatrix&filter, TMatrix&resultMatrix){
    // координаты для проверки, row и col "приделываем к центру filter"
    int rowBegin = row - Isize(filter) / 2;
    int colBegin = col - Isize(filter[0]) / 2;
    int flag = 1;
    for (int i = 0; i < Isize(filter); i++) {
        if (flag == 0) {
            break;
        }
        for (int j = 0; j < Isize(filter[i]); j++) {
            int rowTemp = rowBegin + i;
            int colTemp = colBegin + j;
            if (!(rowTemp >= 0 && rowTemp < Isize(matrix) && colTemp >= 0 && colTemp < Isize(matrix[0]) && filter[i][j] == matrix[rowTemp][colTemp])) {
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
    int rowBegin = row - Isize(filter) / 2;
    int colBegin = col - Isize(filter[0]) / 2;
    for (int i = 0; i < Isize(filter); i++) {
        for (int j = 0; j < Isize(filter[i]); j++) {
            int rowTemp = rowBegin + i;
            int colTemp = colBegin + j;
            if (rowTemp >= 0 && rowTemp < Isize(matrix) && colTemp >= 0 && colTemp < Isize(matrix[0])) {
                pthread_mutex_lock(&mutex);
                resultMatrix[rowTemp][colTemp] += filter[i][j];
                pthread_mutex_unlock(&mutex);
            }
        }
    }
}

void WriteMatrix(TMatrix &matrix) {
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void ReadMatrix(TMatrix &matrix) {
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            std::cin >> matrix[i][j];
        }
    }
}

void* DilationRoutine(void* arg) {
    auto* token = (TThreadToken*) arg;
    for (int i = 0; i < Isize(token->coords); i++) {
        SummingAround(token->coords[i].first, token->coords[i].second, *token->matrix, *token->filter, *token->resultMatrix);
    }
    return nullptr;
}

void* ErosionRoutine(void* arg) {
    auto* token = (TThreadToken*) arg;
    for (int i = 0; i < Isize(token->coords); i++) {
        CheckingAround(token->coords[i].first, token->coords[i].second, *token->matrix, *token->filter, *token->resultMatrix);
    }
    return nullptr;
}


void DilationMatrix(TMatrix &matrix, TMatrix &filter, TMatrix &resultDilation, int threadCount, int counter) {
    TMatrix matrixCopy = matrix;
    pthread_mutex_init(&mutex, nullptr);
    std::vector <pthread_t> threads(threadCount);
    std::vector <TThreadToken> tokens(threadCount);
    // заполнение информации для токенов
    for (int i = 0; i < threadCount; i++) {
        tokens[i].matrix = &matrixCopy;
        tokens[i].filter = &filter;
        tokens[i].resultMatrix = &resultDilation;
    }
    int update = 0;
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            update++;
            tokens[update % threadCount].coords.emplace_back(i, j);
        }
    }

    for (int k = 0; k < counter; k++) {
        for (int i = 0; i < threadCount; i++) {
            pthread_create(&threads[i], nullptr, &DilationRoutine, &tokens[i]);
        }
        for (int i = 0; i < threadCount; i++) {
            pthread_join(threads[i], nullptr);
        }
        matrixCopy = resultDilation;
    }
    pthread_mutex_destroy(&mutex);
}


void ErosionMatrix(TMatrix &matrix, TMatrix &filter, TMatrix &resultErosion, int threadCount, int counter) {
    TMatrix matrixCopy = matrix;
    std::vector <pthread_t> threads(threadCount);
    std::vector <TThreadToken> tokens(threadCount);
    // заполнение информации для токенов
    for (int i = 0; i < threadCount; i++) {
        tokens[i].matrix = &matrixCopy;
        tokens[i].filter = &filter;
        tokens[i].resultMatrix = &resultErosion;
    }
    int update = 0;
    for (int i = 0; i < Isize(matrix); i++) {
        for (int j = 0; j < Isize(matrix[i]); j++) {
            update++;
            tokens[update % threadCount].coords.emplace_back(i, j);
        }
    }

    for (int k = 0; k < counter; k++) {
        for (int i = 0; i < threadCount; i++) {
            pthread_create(&threads[i], nullptr, &ErosionRoutine, &tokens[i]);
        }
        for (int i = 0; i < threadCount; i++) {
            pthread_join(threads[i], nullptr);
        }
        matrixCopy = resultErosion;
    }
}
