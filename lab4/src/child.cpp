#include <istream>
#include <ostream>
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
#include <semaphore.h>

#include "string_to_vector.h"


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cout << "Invalid arguments.\n";
        exit(EXIT_FAILURE);
    }

    auto *nameOutputFile = argv[1];
    std::ofstream out(nameOutputFile);
    int sfd;
    int semInFd;
    int semOutFd; 
    if ((sfd = shm_open(argv[2], O_RDWR, S_IRWXU)) == -1) {
        std::cout << "shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }

    if ((semInFd = shm_open(argv[3], O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((semOutFd = shm_open(argv[4], O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }

    char* ptr = (char*)mmap(nullptr, getpagesize(), PROT_READ, MAP_SHARED, sfd, 0);
    if (ptr == MAP_FAILED) {
        std::cout << "error mmap func" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto *semInput = (sem_t*)mmap(nullptr, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, semInFd, 0);
    auto *semOutput = (sem_t*)mmap(nullptr, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, semOutFd, 0);
    if (semInput == MAP_FAILED) {
        std::cout << "Mmap error" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (semOutput == MAP_FAILED) {
        std::cout << "Mmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (true) {
        sem_wait(semOutput);
        std::string stringNumbers = ptr;
        if (stringNumbers.empty()) {
            sem_post(semInput);
            break;
        }
        std::vector <float> numbers = StringToVectorFloats(stringNumbers);
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
        sem_post(semInput);
    }
    out << "\n";
    out.close();
    if (munmap(ptr, getpagesize()) == -1) {
        std::cout << "Munmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (munmap(semInput, getpagesize()) == -1) {
        std::cout << "Munmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (munmap(semOutput, getpagesize()) == -1) {
        std::cout << "Munmap error" << std::endl;
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}