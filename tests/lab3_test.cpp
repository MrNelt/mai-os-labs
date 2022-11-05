#include <cstdlib>
#include <gtest/gtest.h>

#include <lab3.h>
#include <utils.h>

#include <chrono>


namespace {
    TMatrix GenerateMatrix(int n, int m) {
        TMatrix result(n, std::vector<float>(m));

        std::srand(std::time(nullptr));

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                result[i][j] = (float)(std::rand() % 100);
            }
        }

        return result;
    }
}


bool operator==(const TMatrix& lhs, const TMatrix& rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }

    for(int i = 0; i < Isize(lhs); ++i) {
        if(lhs[i].size() != rhs[i].size()) {
            return false;
        }

        for(int j = 0; j < Isize(lhs); ++j) {
            if(lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }

    return true;
}



TEST(Lab3Test, CheckingAroundTest) {
    TMatrix matrix = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };

    TMatrix filter = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };

    TMatrix resultMatrix = matrix; // изначально копия

    std::vector <std::pair<int, int>> checkedCoords = {
        {2, 0},
        {3, 0},
        {2, 2},
        {3, 4},
        {2, 4},
        {1, 1},
        {2, 1}
    };

    for (int i = 0; i < Isize(checkedCoords); i++) {
        int row = checkedCoords[i].first;
        int col = checkedCoords[i].second;
        CheckingAround(row, col, matrix, filter, resultMatrix);
    }

    TMatrix expectedMatrix = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {0, 2, 0, 4, 0},
        {0, 2, 3, 4, 0},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };

    EXPECT_EQ(resultMatrix, expectedMatrix);
}

TEST(Lab3Test, SummingAroundTest) {
    TMatrix matrix = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };

    TMatrix filter = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };

    TMatrix resultMatrix = matrix; // изначально копия

    std::vector <std::pair<int, int>> summingCoords = {
        {1, 1},
        {2, 1},
        {5, 4}
    };

    for (int i = 0; i < Isize(summingCoords); i++) {
        int row = summingCoords[i].first;
        int col = summingCoords[i].second;
        SummingAround(row, col, matrix, filter, resultMatrix);
    }

    TMatrix expectedMatrix = {
        {2, 4, 6, 4, 5},
        {3, 6, 9, 4, 5},
        {3, 6, 9, 4, 5},
        {2, 4, 6, 4, 5},
        {1, 2, 3, 5, 7},
        {1, 2, 3, 5, 7}
    };

    EXPECT_EQ(resultMatrix, expectedMatrix);
}


TEST(Lab3Test, SingleThreadYieldsCorrectResults) {
    int countTests = 3;
    std::vector <TMatrix> expectedMatrixsErosion {
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
        }
    };

    std::vector <TMatrix> expectedMatrixsDilation {
        {
            {2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2}
        },
        {
            {13, 19, 19, 19, 13}, 
            {19, 28, 28, 28, 19}, 
            {19, 28, 28, 28, 19},
            {19, 28, 28, 28, 19},
            {13, 19, 19, 19, 13}
        },
        {
            {9, 13, 13, 13, 9}, 
            {13, 19, 19, 19, 13}, 
            {13, 19, 19, 19, 13}, 
            {13, 19, 19, 19, 13}, 
            {9, 13, 13, 13, 9}
        }
    };


    std::vector <TMatrix> matrixs {
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},                                    
        },
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},  
        },
        {
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},  
        }
    };

    std::vector <TMatrix> filters {
        {
            {1}
        },
        {
            {3, 3, 3},
            {3, 3, 3},
            {3, 3, 3},
        },
        {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        }

    };
    std::vector <int> counters {
        1,
        1,
        2
    };

    for (int i = 0; i < countTests; i++) { // for erosion
        TMatrix expectedMatrix = expectedMatrixsErosion[i];
        TMatrix matrix = matrixs[i];
        TMatrix filter = filters[i];
        int counter = counters[i];
        TMatrix resultErosion = matrix;
        ErosionMatrix(matrix, filter, resultErosion, 1, counter);
        EXPECT_EQ(resultErosion, expectedMatrix);
    }

    for (int i = 0; i < countTests; i++) { // for dillation
        TMatrix expectedMatrix = expectedMatrixsDilation[i];
        TMatrix matrix = matrixs[i];
        TMatrix filter = filters[i];
        int counter = counters[i];
        TMatrix resultDilation = matrix;
        DilationMatrix(matrix, filter, resultDilation, 1, counter);
        EXPECT_EQ(resultDilation, expectedMatrix);
    }
}

TEST(Lab3Test, ThreadConfigurations) {
    std::srand(std::time(nullptr));
    auto performTestForGivenSize = [](int n1, int m1, int n2, int m2, int maxThreadCount) {
        int counter = 1 + std::rand() % 8;
     
        auto matrix = GenerateMatrix(n1, m1);
        auto filter = GenerateMatrix(n2, m2);
    
        auto resultDilationOne = matrix;
        auto resultErosionOne = matrix;

        DilationMatrix(matrix, filter, resultDilationOne, 1, counter);
        ErosionMatrix(matrix, filter, resultErosionOne, 1, counter);

        for(int i = 2; i < maxThreadCount; ++i) {
            auto resultDilation = matrix;
            auto resultErosion = matrix;
            DilationMatrix(matrix, filter, resultDilation, i, counter);
            ErosionMatrix(matrix, filter, resultErosion, i, counter);
            EXPECT_EQ(resultDilation, resultDilationOne);
            EXPECT_EQ(resultErosion, resultErosionOne);
        }
    };

    performTestForGivenSize(3, 3, 1, 1, 2);
    performTestForGivenSize(10, 10, 3, 3, 2);
    performTestForGivenSize(100, 100, 7, 7, 12);
}


TEST(Lab3Test, PerfomanceTest) {
    auto getAvgTime = [](int threadCount) {
        auto matrix = GenerateMatrix(300, 300);
        auto filter = GenerateMatrix(7, 7);

        constexpr int runsCount = 5;
        constexpr int counter = 5;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();
            auto resultErosion = matrix;
            ErosionMatrix(matrix, filter, resultErosion, threadCount, counter);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(8);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 8 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}