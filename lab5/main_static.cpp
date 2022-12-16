#include <iostream>

#include "signature.h"

int main() {
    int command;
    while (std::cin >> command) {
        if (command == 1) {
            int num;
            std::cin >> num;
            float value = E(num);
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
            float value = SinIntegral(a, b, e);
            if (value == -1) {
                std::cout << "incorrect values of variables" << std::endl;
                continue;
            }
            std::cout << value << std::endl;
        } else {
            std::cout << "you have to enter 1 or 2" << std::endl;
        }
    }
}