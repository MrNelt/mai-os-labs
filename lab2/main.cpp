#include <cstddef>
#include <iostream>
#include <string>
#include <unistd.h>


int main(int argc, char *argv[]) {
    std::string name_output_file;
    std::getline(std::cin, name_output_file);
    char name_output_file_array[name_output_file.size()];
    for (int i = 0; i < name_output_file.size(); i++) {
        name_output_file_array[i] = name_output_file[i];
    }
    int fd[2]; //0 - in 1 - out 
    if (pipe(fd) == -1) {
        std::cout << "Error creating pipe\n";
        return 1;
    }
    int id = fork();
    if (id == -1) {
        std::cout << "Error creating process\n";
        return 2;
    }
    if (id) { // родительский процесс
        close(fd[0]);
        std::string string_numbers;
        std::getline(std::cin, string_numbers);
        int count_chars = string_numbers.size();
        char string_numbers_array[count_chars];
        for (int i = 0; i < count_chars; i++) {
            string_numbers_array[i] = string_numbers[i];
        }
        write(fd[1], &count_chars, sizeof(int));
        write(fd[1], &string_numbers_array, sizeof(char) * count_chars);
    }
    else { // дочерний процесс
        close(fd[1]);
        int count_chars = 0;
        read(fd[0], &count_chars, sizeof(int));
        char string_numbers_array[count_chars];
        read(fd[0], &string_numbers_array, sizeof(char) * count_chars);
        // std::cout << "Hello, World!\n";
        if (execl("child.out", "child.out", name_output_file_array, string_numbers_array, NULL) == -1) {
            std::cout << "Error child process.\n";
            return 3;
        }
    }
}