#ifndef HANDLERNODE_H
#define HANDLERNODE_H


#include <cstdlib>
#include <ratio>
#include <string>
#include <iostream>
#include <unistd.h>

#include "zmqf.h"


class THandlerNode {
    private:
        zmq::context_t contextHandler;
        zmq::context_t contextSynh;
    public:
        zmq::socket_t handlerSocket;
        zmq::socket_t synhSocket;
        int handlerPort;
        int synhPort;
        THandlerNode():
            handlerSocket(contextHandler, ZMQ_PUB),
            synhSocket(contextSynh, ZMQ_REP)
            
        {};

        int Start() {
            handlerPort = BindSocket(handlerSocket);
            synhPort = BindSocket(synhSocket);
            synhSocket.set(zmq::sockopt::rcvtimeo, 5000);
            synhSocket.set(zmq::sockopt::sndtimeo, 5000);
            return 0;
        }

        int Kill() {
            handlerSocket.close();
            synhSocket.close();
            contextHandler.close();
            contextSynh.close();
            return 0;
        }

        int CreateCalcNode(int calcNodeId){
            int calcpid = fork();
            if (calcpid == -1) {
                std::cout << "Fork error\n";
                return EXIT_FAILURE;
            }
            if (calcpid == 0) {
                if(execl("server", "server",
                std::to_string(handlerPort).data(), std::to_string(synhPort).data(),
                std::to_string(calcNodeId).data(), nullptr) == -1) {
                    std::cout << "Failed to exec\n";
                    exit(EXIT_FAILURE);
                }
            }
            return 0;
        }
        int SendMessageChild(int id, const std::string& line) {
            handlerSocket.send(zmq::buffer(std::to_string(id)), zmq::send_flags::sndmore);

            SendMessage(handlerSocket, line);
            auto message = ReceiveMessage(synhSocket);     
            if (message != "Error: Node is unavailable") {
                SendMessage(synhSocket, "Ok!");
            } else {
                std::cout << message << "\n";
            }

            return 0;           
 
        }
};


#endif