#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "string_to_vector.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto *nameOutputFile = argv[1];
    std::ofstream out(nameOutputFile);

    std::string stringNumbers;
    while (std::getline(std::cin, stringNumbers)) {
        std::vector <float> numbers = StringToVectorFloats(stringNumbers);
        float firstNumber = numbers[0];
        for (unsigned long long i = 1; i < numbers.size(); i++) {
            if (numbers[i] == 0) {
                std::cout << "Division by zero.\n";
                out << "\n";
                out.close();
                exit(EXIT_FAILURE);
            }
            firstNumber /= numbers[i];
        }
        out << firstNumber << " ";
    }
    out << "\n";
    out.close();
    return 0;
}