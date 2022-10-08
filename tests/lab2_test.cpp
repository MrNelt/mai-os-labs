#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>

#include "parent.h"
#include "string_to_float.h"



TEST(TestStringToVector, Subtest_1) {
    std::vector <float> expected_vector = {1.5, 2.5, 3.5};
    char input_array[] = "1.5 2.5 3.5";
    std::vector <float> output_vector = string_to_vector_floats(input_array);
    ASSERT_EQ(expected_vector.size(), output_vector.size());
    for (long unsigned int i = 0; i < expected_vector.size(); i++) {
        ASSERT_FLOAT_EQ(expected_vector[i], output_vector[i]);
    }
}


TEST(TestStringToVector, Subtest_2) {
    std::vector <float> expected_vector = {1};
    char input_array[] = "1";
    std::vector <float> output_vector = string_to_vector_floats(input_array);
    ASSERT_EQ(expected_vector.size(), output_vector.size());
    for (long unsigned int i = 0; i < expected_vector.size(); i++) {
        ASSERT_FLOAT_EQ(expected_vector[i], output_vector[i]);
    }
}

TEST(TestStringToVector, Subtest_3) {
    std::vector <float> expected_vector = {1.5, 2, 3, 4, 5, 0};
    char input_array[] = "1.5 2 3 4 5 0";
    std::vector <float> output_vector = string_to_vector_floats(input_array);
    ASSERT_EQ(expected_vector.size(), output_vector.size());
    for (long unsigned int i = 0; i < expected_vector.size(); i++) {
        ASSERT_FLOAT_EQ(expected_vector[i], output_vector[i]);
    }
}

TEST(TestParent, Subtest_1) {
    std::string name_output_file = "jambo.txt";
    std::string string_numbers = "1 0.5 0.5 0.5";
    float expected_value = 8;

    std::ofstream f_out("temp");
    f_out << name_output_file << "\n";
    f_out << string_numbers << "\n";
    f_out.close();

    std::ifstream f_in("temp");
    parent(f_in, "child_test");

    std::ifstream f_in_check_temp("temp");
    ASSERT_TRUE(f_in_check_temp.is_open() == false);
    f_in_check_temp.close();

    std::ifstream f_in_check_output("jambo.tea");
    // ASSERT_TRUE(f_in_check_output.good() == true);
    std::string output_string;
    std::getline(f_in_check_output, output_string);
    float output_value = std::stof(output_string);
    ASSERT_FLOAT_EQ(output_value, expected_value);
    f_in_check_output.close();
    remove("/home/alex/mai-os-labs/build/tests/jambo.txt");
}
