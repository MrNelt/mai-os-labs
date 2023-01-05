#ifndef CALCNODE_H
#define CALCNODE_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <unistd.h>
#include <utility>
#include <zmq.hpp>

#include "zmqf.h"
#include "search.h"


class TCalcNode {
    private:
        zmq::context_t contextHandler;
        zmq::context_t contextSynh;
    public:
        zmq::socket_t handlerSocket;
        zmq::socket_t synhSocket;
        int handlerPort;
        int synhPort;
        std::string filter;
        TCalcNode(int handlerPort, int synhPort, std::string filter):
            handlerSocket(contextHandler, ZMQ_SUB),
            synhSocket(contextSynh, ZMQ_REQ),
            handlerPort(handlerPort),
            synhPort(synhPort),
            filter(std::move(filter))
        {};

        int Start() {
            Connect(handlerSocket, handlerPort);
            Connect(synhSocket, synhPort);
            handlerSocket.set(zmq::sockopt::subscribe, filter);
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

        std::string Receive() {
            std::string adress = ReceiveMessage(handlerSocket);
            std::string content = ReceiveMessage(handlerSocket);
            SendMessage(synhSocket, "Ok!");
            std::string answer = ReceiveMessage(synhSocket);
            if (answer == "Error: Node is unavailable") {
                    std::cout << answer << "\n";
            }
            return content;   
        }


        std::vector<unsigned int> Exec(const std::string& message) {
            auto components = StringToVectorStrings(message, ' ');
            std::string pattern = components[2];
            std::string text = components[1];
            return KMP(pattern, text);
        }
};

#endif