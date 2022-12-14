#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <dlfcn.h>


#include "signature.h"

const std::vector <std::string> FUNC_NAME = {"E", "SinIntegral"};


TEST(Lab5Test, DynamicTest) {
    const float expectE = 2.71;
    const auto inputParameterE = {500, 300, 200};

    const std::vector <std::vector <float>> inputParameterSin = {
        {1, 5, 0.001},
        {5, 6, 0.001},
        {1, 100, 0.001}
    };
    const std::vector <float> answerSin = {0.2566, -0.676, -0.322};

    float (*eOne)(int x);
    float (*sinIntegralOne)(float a, float b, float e);
    void* handleOne = dlopen(getenv("PATH_TO_LIB1"), RTLD_LAZY);
    std::cout << getenv("PATH_TO_LIB1");
    ASSERT_NE(handleOne, nullptr);


    float (*eTwo)(int x);
    float (*sinIntegralTwo)(float a, float b, float e);
    void* handleTwo = dlopen(getenv("PATH_TO_LIB2"), RTLD_LAZY);
    ASSERT_NE(handleTwo, nullptr);

    eOne = (float(*)(int))dlsym(handleOne, FUNC_NAME[0].c_str());
    eTwo = (float(*)(int))dlsym(handleTwo, FUNC_NAME[0].c_str());
    sinIntegralOne = (float(*)(float, float, float))dlsym(handleOne, FUNC_NAME[1].c_str());
    sinIntegralTwo = (float(*)(float, float, float))dlsym(handleTwo, FUNC_NAME[1].c_str());
    for (const auto& elem : inputParameterE) {
        auto eOutOne = eOne(elem);
        auto eOutTwo = eTwo(elem);
        EXPECT_NEAR(eOutOne, expectE, 0.1);
        EXPECT_NEAR(eOutTwo, expectE, 0.1);
    }

    for (size_t i = 0; i < inputParameterSin.size(); ++i) {
        float a = inputParameterSin[i][0];
        float b = inputParameterSin[i][1];
        float e = inputParameterSin[i][2];
        auto sqOne = sinIntegralOne(a, b, e);
        auto sqTwo = sinIntegralTwo(a, b, e);
        EXPECT_NEAR(sqOne, answerSin[i], 0.1);
        EXPECT_NEAR(sqTwo, answerSin[i], 0.1);
    }
}

TEST(Lab5Test, StaticOneTest) {
    const float expectE = 2.71;
    const auto inputParameterE = {500, 300, 200};

    const std::vector <std::vector <float>> inputParameterSin = {
        {1, 5, 0.001},
        {5, 6, 0.001},
        {1, 100, 0.001}
    };
    const std::vector <float> answerSin = {0.2566, -0.676, -0.322};

    for (const auto& elem : inputParameterE) {
        auto eOut = E(elem);
        EXPECT_NEAR(eOut, expectE, 0.1);
    }

    for (size_t i = 0; i < inputParameterSin.size(); ++i) {
        float a = inputParameterSin[i][0];
        float b = inputParameterSin[i][1];
        float e = inputParameterSin[i][2];
        auto sq = SinIntegral(a, b, e);
        EXPECT_NEAR(sq, answerSin[i], 0.1);
    }
}