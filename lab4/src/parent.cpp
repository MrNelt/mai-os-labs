#include "parent.h"


#define SHARED_MEMORY_OBJECT_NAME "shared_memory"

void ParentRoutine(std::istream& stream, const char* pathToChild) {
    std::string nameOutputFile;
    std::getline(stream, nameOutputFile);

	/* shared memory file descriptor */
    int sfd;
	/* create the shared memory object */
	if ((sfd = shm_open(SHARED_MEMORY_OBJECT_NAME, O_CREAT | O_RDWR, S_IRWXU)) == -1) {
        std::cout << "Shm_open error" << std::endl;
        exit(EXIT_FAILURE);
    }
	/* configure the size of the shared memory object */
	ftruncate(sfd, getpagesize());

    int pid = fork();
    if (pid == -1) {
        std::cout << "Error creating process\n";
        exit(EXIT_FAILURE);
    }

    if (pid != 0) { // родительский процесс
	    /* memory map the shared memory object */
        char* ptr = (char*)mmap(nullptr, getpagesize(), PROT_WRITE, MAP_SHARED, sfd, 0);
        if (ptr == MAP_FAILED) {
            std::cout << "Mmap error" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string stringNumbers;
        std::string stringAllNumbers;
        while (std::getline(stream, stringNumbers)) {
            stringNumbers += "\n";
            stringAllNumbers += stringNumbers;
        }
        strncpy(ptr, stringAllNumbers.c_str(), stringAllNumbers.size());
        wait(nullptr);
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
        if(execl(pathToChild, pathToChild, nameOutputFile.data(), SHARED_MEMORY_OBJECT_NAME, nullptr) == -1) {
            std::cout << "Failed to exec\n";
            exit(EXIT_FAILURE);
        }
    }
}