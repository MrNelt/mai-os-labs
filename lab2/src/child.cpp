#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

#include "string_to_vector.h"


int main(int argc, char* argv[]) {
    std::string name_output_file(argv[1], sizeof(argv[1]));
    std::string string_numbers = argv[2];

    char string_numbers_array[string_numbers.size() + 1];
    string_numbers.copy(string_numbers_array, string_numbers.size() + 1);
    std::vector <float> numbers;
    string_to_vector_floats(string_numbers_array, numbers);

    float first_number = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] == 0) {
            std::cout << "Division by zero\n";
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