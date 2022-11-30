#include <istream>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>

#include "string_to_vector.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto *nameOutputFile = argv[1];
    std::ofstream out(nameOutputFile);
    int sfd;
	if ((sfd = shm_open(argv[2], O_RDWR, S_IRWXU)) == -1) {
        std::cout << "shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
    char* ptr = (char*)mmap(nullptr, getpagesize(), PROT_READ, MAP_SHARED, sfd, 0);
    if (ptr == MAP_FAILED) {
        std::cout << "error mmap func" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string stringNumbers = ptr;
    auto start = stringNumbers.begin();
    auto end = stringNumbers.end();
    auto next = std::find(start, end, '\n');
    while (next != end) {
        std::vector <float> numbers = StringToVectorFloats(std::string(start, next));
        float firstNumber = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            if (numbers[i] == 0) {
                std::cout << "Division by zero.\n";
                out << "\n";
                out.close();
                exit(EXIT_FAILURE);
            }
            firstNumber /= numbers[i];
        }
        out << firstNumber << " ";
        start = next + 1;
        next = std::find(start, end, '\n');
    }
    out << "\n";
    out.close();
    if (munmap(ptr, getpagesize()) == -1) {
        std::cout << "Munmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}