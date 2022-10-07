#include <iostream>
#include <vector>
#include <string>
#include <string.h>

inline void string_to_vector_floats(char string_numbers_array[], std::vector <float>& numbers) {
    int counter = 0;
    char *tmp_char;
    tmp_char = strtok(string_numbers_array," ");
    while (tmp_char != NULL) {
        numbers.push_back(std::stof(tmp_char));
        tmp_char = strtok(NULL, " ");
    }
}