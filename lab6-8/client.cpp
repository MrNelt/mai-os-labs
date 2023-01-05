#include <iostream>

#include "handlernode.hpp"
#include "calcnode.hpp"
#include "topology.h"
#include "zmqf.h"

int main() {
    THandlerNode handlerNode;
    handlerNode.Start();
    TTopology topology;
    std::cout << "Commands:\n";
    std::cout << "create child parent\n";
    std::cout << "kill child\n";
    std::cout << "exec id line pattern\n";
    std::cout << "exit\n";
    std::string command;
    while (std::cin >> command) {
        if (command == "create") {
            int child;
            int parent;
            std::cin >> child;
            std::cin >> parent;
            if (topology.Find(child) != -1) {
                std::cout << "Child already exists!\n";
                continue;
            }
            if (parent == -1) {
                topology.Insert(child);
                handlerNode.CreateCalcNode(child);
            } else {
                if (!topology.Insert(parent, child)) {
                    std::cout << "Parent doesn't exist!\n";
                } else {
                    handlerNode.CreateCalcNode(child);
                }
            }
        }
        if (command == "exec") {
            int child;
            std::cin >> child;
            if (topology.Find(child) == -1) {
                std::cout << "Child doesn't exist\n";
                continue;
            }
            std::string line;
            std::cin >> line;
            std::string pattern;
            std::cin >> pattern;
            std::string message = "exec " + line + " " + pattern;
            handlerNode.SendMessageChild(child, message);
        }
        if (command == "kill") {
            int child;
            std::cin >> child;
            if (topology.Find(child) == -1) {
                std::cout << "Child doesn't exist\n";
                continue;
            }
            handlerNode.SendMessageChild(child, "kill");
            topology.Erase(child);
        }

        if (command == "heartbit") {
            int time;
            std::cin >> time;
            std::cout << time << "\n";
            handlerNode.synhSocket.set(zmq::sockopt::rcvtimeo, time * 4);
            for (int i = 0; i < 5; ++i) {
                for (const auto& list : topology.container) {
                    for (const auto& elem : list) {
                        handlerNode.SendMessageChild(elem, "ping");
                    }
                }
		    sleep((unsigned)(time/1000));
            }
            handlerNode.synhSocket.set(zmq::sockopt::rcvtimeo, 5000);            
            continue;
        }

        if (command == "exit") {
            for (const auto& list : topology.container) {
                for (const auto& elem : list) {
                    handlerNode.SendMessageChild(elem, "kill");
                }
            }
            // handlerNode.Kill();
            break;
        }
    }
    handlerNode.Kill();
    return 0;
}