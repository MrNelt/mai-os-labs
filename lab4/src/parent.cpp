#include "parent.h"
#include <algorithm>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>


constexpr auto SHARED_MEMORY_OBJECT_NAME = "shared_memory";
constexpr auto SHARED_MEMORY_SEMAPHORE_INPUT_NAME = "shared_semaphore_input";
constexpr auto SHARED_MEMORY_SEMAPHORE_OUTPUT_NAME = "shared_semaphore_output";

void ParentRoutine(std::istream& stream, const char* pathToChild) {
    std::string nameOutputFile;
    std::getline(stream, nameOutputFile);
    /* shared memory file descriptor */
    int sfd;
    int semInFd;
    int semOutFd;
    /* create the shared memory object */
    if ((sfd = shm_open(SHARED_MEMORY_OBJECT_NAME, O_CREAT | O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((semInFd = shm_open(SHARED_MEMORY_SEMAPHORE_INPUT_NAME, O_CREAT | O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((semOutFd = shm_open(SHARED_MEMORY_SEMAPHORE_OUTPUT_NAME, O_CREAT | O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
    /* configure the size of the shared memory object */
    ftruncate(sfd, getpagesize());
    ftruncate(semInFd, getpagesize());
    ftruncate(semOutFd, getpagesize());

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

    sem_init(semInput, 1, 1);
    sem_init(semOutput, 1, 0);


    int pid = fork();
    if (pid == -1) {
        std::cout << "Error creating process\n";
        exit(EXIT_FAILURE);
    }

    if (pid != 0) { // родительский процесс
        /* memory map the shared memory object */
        char* ptr = (char*)mmap(nullptr, getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, sfd, 0);
        if (ptr == MAP_FAILED) {
            std::cout << "Mmap error" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string stringNumbers;
        while (std::getline(stream, stringNumbers)) {
            sem_wait(semInput);
            stringNumbers += "\n";
            sprintf((char *) ptr, "%s", stringNumbers.c_str());
            sem_post(semOutput);
        }
        sem_wait(semInput);
        sprintf((char *) ptr, "%s", "");
        sem_post(semOutput);
        wait(nullptr);
        if (sem_destroy(semInput) == -1) {
            std::cout << "Sem_destroy error" << std::endl; 
            exit(EXIT_FAILURE);     
        }
        if (sem_destroy(semOutput) == -1) {
            std::cout << "Sem_destroy error" << std::endl; 
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
        if (munmap(ptr, getpagesize()) == -1) {
            std::cout << "Munmap error" << std::endl; 
            exit(EXIT_FAILURE);
        }
        if (shm_unlink(SHARED_MEMORY_OBJECT_NAME) == -1) {
            std::cout << "Shm_unlink error" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else { // дочерний процесс
        if(execl(pathToChild, pathToChild, nameOutputFile.data(),
            SHARED_MEMORY_OBJECT_NAME, SHARED_MEMORY_SEMAPHORE_INPUT_NAME,
            SHARED_MEMORY_SEMAPHORE_OUTPUT_NAME, nullptr) == -1) {
            std::cout << "Failed to exec\n";
            exit(EXIT_FAILURE);
        }
    }
}