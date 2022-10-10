#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../include/string_to_vector.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto name_output_file = argv[1];

    std::ofstream out(name_output_file);

    std::string string_numbers;
    while (std::getline(std::cin, string_numbers)) {
        char *string_numbers_array = (char*)malloc(string_numbers.size());
        string_numbers.copy(string_numbers_array, string_numbers.size());
        std::vector <float> numbers = string_to_vector_floats(string_numbers_array);
        free(string_numbers_array);

        float first_number = numbers[0];
        for (unsigned long long i = 1; i < numbers.size(); i++) {
            if (numbers[i] == 0) {
                std::cout << "Division by zero.\n";
                out << "NULL\n";
                out.close();
                exit(EXIT_FAILURE);
            }
            first_number /= numbers[i];
        }
        out << first_number << " ";
    }
    out << "NULL\n";
    out.close();
    return 0;
}