#include <cstdio>
#include <cstdlib>
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
    std::string string_numbers = "1 0.5 0.5 0.5\n100 8\n1\n90 2";
    std::string expected_string = "8 12.5 1 45 NULL";
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
    f_in_check_output.close();
    remove("checker.txt");
    ASSERT_EQ(output_string, expected_string);
}


TEST(TestParent, Subtest_2) {
    std::string name_output_file = "output.txt";
    std::string string_numbers = "1 0.5 0.5 0.5\n100 0\n1\n90 2\n1 1 1 1\n1 1 1 1";
    std::string expected_string = "8 NULL";
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

    ASSERT_EQ(output_string, expected_string);

    f_in_check_output.close();
    remove("output.txt");
}


TEST(TestParent, Subtest_3) {
    std::string name_output_file = "output.txt";
    std::string string_numbers = "1 0 0.5 0.5\n100 0\n1\n90 2\n1 1 1 1\n1 1 1 1";
    std::string expected_string = "NULL";
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

    ASSERT_EQ(output_string, expected_string);

    f_in_check_output.close();
    remove("output.txt");
}