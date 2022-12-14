#include <array>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include <string>
#include <vector>


const std::vector <std::string> LIB = {"./libd1_dynamic.so", "./libd2_dynamic.so"};
const std::vector <std::string> FUNC_NAME = {"E", "SinIntegral"};

int main() {
    int curlib = 0;
    float (*e)(int x);
    float (*sinIntegral)(float a, float b, float e);
    void* handle = dlopen(LIB[curlib].c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        std::cout << "Fail dlopen\n";
        return EXIT_FAILURE;
    }
    e = (float(*)(int))dlsym(handle, FUNC_NAME[0].c_str());
    sinIntegral = (float(*)(float, float, float))dlsym(handle, FUNC_NAME[1].c_str());
    int command;
    while (std::cin >> command) {
        if (command == 1) {
            int num;
            std::cin >> num;
            float value = e(num);
            if (value == -1) {
                std::cout << "incorrect value of variable" << std::endl;
                continue;
            }
            std::cout << value << std::endl;
        } else if (command == 2) {
            float a;
            float b;
            float e;
            std::cin >> a >> b >> e;
            float value = sinIntegral(a, b, e);
            if (value == -1) {
                std::cout << "incorrect values of variables" << std::endl;
                continue;
            }
            std::cout << value << std::endl;
        } else if (command == 0) {
            dlclose(handle);
            curlib ^= 1;
            void* handle = dlopen(LIB[curlib].c_str(), RTLD_LAZY);
            if (handle == nullptr) {
                std::cout << "Fail dlopen\n";
                return EXIT_FAILURE;
            }
            e = (float(*)(int))dlsym(handle, FUNC_NAME[0].c_str());
            sinIntegral = (float(*)(float, float, float))dlsym(handle, FUNC_NAME[1].c_str());
        } else {
            std::cout << "you have to enter 1 or 2" << std::endl;
        }
    }
    dlclose(handle);
}