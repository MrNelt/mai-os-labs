#include <gtest/gtest.h>

#include <lab3.h>
#include <utils.h>

#include <chrono>


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

    for (int i = 0; i < (int)checkedCoords.size(); i++) {
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

    for (int i = 0; i < (int)summingCoords.size(); i++) {
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