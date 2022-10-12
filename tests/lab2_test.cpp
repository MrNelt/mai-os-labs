#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "parent.h"
#include "string_to_float.h"



TEST(Lab2Test, StringToVectorTest) {
    std::vector <std::vector <float>> expectedVectors;
    expectedVectors.push_back({1.5, 2.5, 3.5});
    expectedVectors.push_back({1.5, 2, 3, 4, 5, 0});
    expectedVectors.push_back({1});

    std::vector <std::string> inputStrings;
    inputStrings.emplace_back("1.5 2.5 3.5");
    inputStrings.emplace_back("1.5 2 3 4 5 0");
    inputStrings.emplace_back("1");

    for (long unsigned int i = 0; i < 3; i++) {
        std::vector <float> outputVector = StringToVectorFloats(inputStrings[i]);
        ASSERT_EQ(expectedVectors[i].size(), outputVector.size());
        for (long unsigned int j = 0; i < expectedVectors[i].size(); i++) {
            EXPECT_FLOAT_EQ(expectedVectors[i][j], outputVector[j]);
        }
    }
}


TEST(Lab2Test, ParentTest) {
    
    std::vector <std::string> namesOutputFile = {"checker.txt", "output.txt", "jambo.tea"};
    std::vector <std::string> stringsNumbers = {"1 0.5 0.5 0.5\n100 8\n1\n90 2", "1 0.5 0.5\n100 0\n1\n90 2\n1 1", "1 0 0.5 0.5\n100 0\n1\n90 2"};
    std::vector <std::string> expectedStrings = {"8 12.5 1 45 ", "4 ", ""};

    for (long unsigned int i = 0; i < 3; i++) {
        {

        std::ofstream fOut("input.txt");
        fOut << namesOutputFile[i] << "\n";
        fOut << stringsNumbers[i] << "\n";

        }

        {

        std::ifstream fIn("input.txt");
        ParentRoutine(fIn, getenv("PATH_TO_CHILD"));

        }
    
        remove("input.txt");

        {
    
        std::ifstream fInCheckOutput = std::ifstream(namesOutputFile[i]);
        ASSERT_TRUE(fInCheckOutput.good());
        std::string outputString;
        std::getline(fInCheckOutput, outputString);
        EXPECT_EQ(outputString, expectedStrings[i]);
        }


        remove(namesOutputFile[i].data());
    }
}

