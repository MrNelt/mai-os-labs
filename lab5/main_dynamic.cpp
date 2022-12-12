#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>


int main() {
    std::cout << "Hello, my fried!\n";
    const auto *libName = "./lib1_dynamic.so";
    int (*somethingWithInt)(int num);
    void* handle = dlopen(libName, RTLD_LAZY);
    if (handle == nullptr) {
        std::cout << "Fail dlopen\n";
        return EXIT_FAILURE;
    } 
    somethingWithInt = (int(*)(int))dlsym(handle, "SomethingWithInt");
    int num;
    std::cin >> num;
    std::cout << somethingWithInt(num) << "\n";
    dlclose(handle);
}