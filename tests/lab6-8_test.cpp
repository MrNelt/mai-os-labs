#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <zmq.hpp>




#include "topology.h"
#include "zmqf.h"

TEST(lab6Test, TopologyTest){
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

