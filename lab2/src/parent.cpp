#include "../include/parent.h"


void ParentRoutine(std::istream& stream, char* PathToChild) {
    std::string name_output_file;
    std::getline(stream, name_output_file);
    char *name_output_file_array = (char*)malloc(name_output_file.size());
    name_output_file.copy(name_output_file_array, name_output_file.size());

    int fd[2]; //0 - read 1 - write 
    if (pipe(fd) == -1) {
        std::cout << "Error creating pipe\n";
        exit(EXIT_FAILURE);
    }

    int id = fork();
    if (id == -1) {
        std::cout << "Error creating process\n";
        exit(EXIT_FAILURE);
    }

    if (id) { // родительский процесс
        close(fd[0]);
        std::string string_numbers;
        std::getline(stream, string_numbers);

        int count_chars = string_numbers.size();
        char *string_numbers_array = (char*)malloc(count_chars);
        string_numbers.copy(string_numbers_array, count_chars);
        write(fd[1], &count_chars, sizeof(int));
        write(fd[1], string_numbers_array, sizeof(char) * (count_chars));


        free(string_numbers_array);
        free(name_output_file_array);
        close(fd[1]); 
        wait(NULL);
    }
    else { // дочерний процесс
        close(fd[1]);

        int count_chars = 0;
        read(fd[0], &count_chars, sizeof(int));

        char *string_numbers_array = (char*) malloc(count_chars);
        read(fd[0], string_numbers_array, sizeof(char) * (count_chars));
        if (execl(PathToChild, "child", name_output_file_array, string_numbers_array, NULL) == -1) {
            std::cout << "Error child process.\n";
            exit(EXIT_FAILURE);
        }

        free(string_numbers_array);
        free(name_output_file_array);
        close(fd[0]);
    }
}