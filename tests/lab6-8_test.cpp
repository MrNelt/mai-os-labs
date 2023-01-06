#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <zmq.hpp>
#include <vector>




#include "topology.h"
#include "zmqf.h"
#include "search.h"


TEST(lab6Test, TopologyTest) {
    TTopology container;
    size_t size = 0;

    EXPECT_EQ(container.Size(), size);
    container.Insert(5);
    ++size;
    container.Insert(12);
    ++size;
    container.Insert(888);
    ++size;
    container.Insert(999);
    ++size;

    EXPECT_EQ(container.Insert(5, 4), true);
    ++size;
    EXPECT_EQ(container.Insert(8, 3), false);
    EXPECT_EQ(container.Size(), size);

    EXPECT_EQ(container.Erase(5), true);
    --size;
    EXPECT_EQ(container.Size(), size);
    EXPECT_EQ(container.Erase(9999), false);
    EXPECT_EQ(container.Size(), size);

    EXPECT_EQ(container.Find(4), 0);
    EXPECT_EQ(container.Find(12), 1);
    EXPECT_EQ(container.Find(999), 3);
    EXPECT_EQ(container.Find(-8), -1);
}


TEST(lab6Test, SearchTest) {
    std::vector <std::string> text = {
        "aba444444aba",
        "123456789",
        "test",
        "1"
    };
    std::vector <std::string> pattern = {
        "aba",
        "1",
        "st",
        "0"
    };

    std::vector <std::vector<unsigned int>> answers = {
        {0, 9},
        {0},
        {2},
        {}
    };

    for (size_t i = 0; i < text.size(); ++i) {
        auto answer = KMP(pattern[i], text[i]);
        ASSERT_EQ(answers[i].size(), answer.size());
        for (size_t j = 0; j < answer.size(); ++j) {
            EXPECT_EQ(answers[i][j], answer[j]);
        } 
    }
}
