#include "lab3.h"
#include "utils.h"

#include <thread>


namespace {
    void SumGivenRows(const TMatrix& lhs, const TMatrix& rhs, TMatrix& result, int firstRow, int lastRow) {
        int m = Isize(lhs);
        for(int i = firstRow; i < lastRow; ++i) {
            for(int j = 0; j < m; ++j) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
    }
}

TMatrix SumMatrices(const TMatrix& lhs, const TMatrix& rhs, int threadCount) {
    TMatrix result(lhs.size(), std::vector<int>(lhs[0].size()));

    if(threadCount > 1) {
        int actualThreads = std::min(threadCount, Isize(result));

        std::vector<std::thread> threads;
        threads.reserve(actualThreads);

        int rowsPerThread = Isize(result) / actualThreads;

        for(int i = 0; i < Isize(result); i += rowsPerThread) {
            if(i + rowsPerThread >= Isize(result)) {
                threads.emplace_back(SumGivenRows, std::ref(lhs), std::ref(rhs), std::ref(result), i, Isize(result));
            } else {
                threads.emplace_back(SumGivenRows, std::ref(lhs), std::ref(rhs), std::ref(result),
                                     i, i + rowsPerThread);
            }
        }

        for(auto& thread : threads) {
            thread.join();
        }
    } else {
        SumGivenRows(lhs, rhs, result, 0, lhs.size());
    }


    return result;
}
