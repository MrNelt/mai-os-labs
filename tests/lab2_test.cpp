#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>
#include <string>

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
    std::string name_output_file = "checker.txt";
    float expected_value = 8;
    std::string string_numbers = "1 0.5 0.5 0.5";
    std::ofstream f_out("input.txt");
    f_out << name_output_file << "\n";
    f_out << string_numbers << "\n";
    f_out.close();

    std::ifstream f_in = std::ifstream("input.txt");
    ParentRoutine(f_in, getenv("PATH_TO_CHILD"));
    f_in.close();
    remove("input.txt");

    std::ifstream f_in_check_output = std::ifstream("checker.txt");
    ASSERT_TRUE(f_in_check_output.good());
    std::string output_string;
    std::getline(f_in_check_output, output_string);
    float output_value = std::stof(output_string);
    ASSERT_FLOAT_EQ(output_value, expected_value);
    f_in_check_output.close();
    remove("checker.txt");
}


TEST(TestParent, Subtest_2) {
    std::string name_output_file = "out.txt";
    float expected_value = 500;
    std::string string_numbers = "1000 2 1";
    std::ofstream f_out("input.txt");
    f_out << name_output_file << "\n";
    f_out << string_numbers << "\n";
    f_out.close();

    std::ifstream f_in = std::ifstream("input.txt");
    ParentRoutine(f_in, getenv("PATH_TO_CHILD"));
    f_in.close();
    remove("input.txt");

    std::ifstream f_in_check_output = std::ifstream("out.txt");
    ASSERT_TRUE(f_in_check_output.good());
    std::string output_string;
    std::getline(f_in_check_output, output_string);
    float output_value = std::stof(output_string);
    ASSERT_FLOAT_EQ(output_value, expected_value);
    f_in_check_output.close();
    remove("out.txt");
}

TEST(TestParent, Subtest_3) {
    std::string name_output_file = "jambo.tea";
    float expected_value = 12.5;
    std::string string_numbers = "100 8 1 1 1";
    std::ofstream f_out("input.txt");
    f_out << name_output_file << "\n";
    f_out << string_numbers << "\n";
    f_out.close();

    std::ifstream f_in = std::ifstream("input.txt");
    ParentRoutine(f_in, getenv("PATH_TO_CHILD"));
    f_in.close();
    remove("input.txt");

    std::ifstream f_in_check_output = std::ifstream("jambo.tea");
    ASSERT_TRUE(f_in_check_output.good());
    std::string output_string;
    std::getline(f_in_check_output, output_string);
    float output_value = std::stof(output_string);
    ASSERT_FLOAT_EQ(output_value, expected_value);
    f_in_check_output.close();
    remove("jambo.tea");
}


TEST(TestParent, Subtest_4) {
    std::string name_output_file = "output.txt";
    std::string expected_value = "NULL";
    std::string string_numbers = "100 8 1 1 1 0";
    std::ofstream f_out("input.txt");
    f_out << name_output_file << "\n";
    f_out << string_numbers << "\n";
    f_out.close();

    std::ifstream f_in = std::ifstream("input.txt");
    ParentRoutine(f_in, getenv("PATH_TO_CHILD"));
    f_in.close();
    remove("input.txt");

    std::ifstream f_in_check_output = std::ifstream("output.txt");
    ASSERT_TRUE(f_in_check_output.good());
    std::string output_string;
    std::getline(f_in_check_output, output_string);
    ASSERT_EQ(output_string, expected_value);
    f_in_check_output.close();
    remove("output.txt");
}