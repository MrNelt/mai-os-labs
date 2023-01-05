#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "zmqf.h"
#include "calcnode.hpp"
#include "handlernode.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "argc server error!\n";
        exit(EXIT_FAILURE);
    }
    TCalcNode calc(atoi(argv[1]), atoi(argv[2]), argv[3]);
    calc.Start();
    std::cout << "Calc node is starting! pid: " << getpid() << "\n";
    while (true) {
        std::string message = calc.Receive();
        if (message == "kill") {
            calc.Kill();
            std::cout << "Ok! Kill " << calc.filter << "!\n";
            break;
        }
        if (message == "ping") {
            std::cout << "Ok! The node " << calc.filter << " is available!\n";
            continue;
        }
        if (message.rfind("exec", 0) == 0) {
            auto answers = calc.Exec(message);
            if (answers.empty()) {
                std::cout << -1;
            }
            for (auto const &elem : answers) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
            continue;
        }
    }    
}