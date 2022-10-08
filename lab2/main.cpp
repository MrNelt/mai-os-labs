#include "include/parent.h"


int main() {
    std::string name_output_file;
    std::string string_numbers;
    std::getline(std::cin, name_output_file);
    std::getline(std::cin, string_numbers);

    std::ofstream f_temp_out("temp"); // переправить поток ввода в файл
    f_temp_out << name_output_file << "\n";
    f_temp_out << string_numbers << "\n";
    f_temp_out.close();

    std::ifstream s("temp");
    if (s.bad()) {
        std::cout << "Error open file.\n";
        return EXIT_FAILURE;
    }
    std::cout<<getenv("PATH_TO_CHILD");
    return ParentRoutine(s, getenv("PATH_TO_CHILD"));
}