#include "parent.h"

void ParentRoutine(std::istream& stream, const char* pathToChild) {
    std::string nameOutputFile;
    std::getline(stream, nameOutputFile);

    std::array <int, 2> parentPipe; //0 - read 1 - write 
    if (pipe(parentPipe.data()) == -1) {
        std::cout << "Error creating pipe\n";
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        std::cout << "Error creating process\n";
        exit(EXIT_FAILURE);
    }

    if (pid != 0) { // родительский процесс
        close(parentPipe[0]);
        std::string stringNumbers;
        while (std::getline(stream, stringNumbers)) {
            std::string stringNumberN = stringNumbers + "\n";
            write(parentPipe[1], stringNumberN.data(), sizeof(char) * (stringNumberN.size()));
        }
        close(parentPipe[1]);
        wait(nullptr);
    }
    else { // дочерний процесс
        close(parentPipe[1]);
        dup2(parentPipe[0], 0);
   
        if(execl(pathToChild, pathToChild, nameOutputFile.data(), nullptr) == -1) {
            std::cout << "Failed to exec\n";
            exit(EXIT_FAILURE);
        }
        close(parentPipe[0]);
    }
}