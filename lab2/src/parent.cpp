#include "../include/parent.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>


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
        while (std::getline(stream, string_numbers)) {
            char *string_numbers_array = (char*)malloc(string_numbers.size() + 1);
            string_numbers.copy(string_numbers_array, string_numbers.size());
            string_numbers_array[string_numbers.size()] = '\n';
            write(fd[1], string_numbers_array, sizeof(char) * (string_numbers.size() + 1));
            free(string_numbers_array);
        }

        free(name_output_file_array);
        close(fd[1]);
        wait(NULL);
    }
    else { // дочерний процесс
        close(fd[1]);
        dup2(fd[0], 0);
    
        char* argv[3];
        char child[] = "child";
        argv[0] = child;
        argv[1] = name_output_file_array;
        argv[2] = NULL;
    
        if(execv(PathToChild, argv) == -1) {
            std::cout << "Faildet to exec\n";
            exit(EXIT_FAILURE);
        }
    
        free(name_output_file_array);
        close(fd[0]);
    }
}