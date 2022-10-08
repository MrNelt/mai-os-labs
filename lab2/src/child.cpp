#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

#include "../include/string_to_vector.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments.\n";
        return EXIT_FAILURE;
    }

    std::string name_output_file = argv[1];
    std::string string_numbers = argv[2];

    char *string_numbers_array = (char*)malloc(string_numbers.size());
    string_numbers.copy(string_numbers_array, string_numbers.size());
    std::vector <float> numbers = string_to_vector_floats(string_numbers_array);
    free(string_numbers_array);

    float first_number = numbers[0];
    for (unsigned long long i = 1; i < numbers.size(); i++) {
        if (numbers[i] == 0) {
            std::cout << "Division by zero.\n";
            return EXIT_FAILURE;
        }
        first_number /= numbers[i];
    }

    std::ofstream f;
    f.open(name_output_file);
    f << first_number << "\n";
    f.close();

    return EXIT_SUCCESS;
}