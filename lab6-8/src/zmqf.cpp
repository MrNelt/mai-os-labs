#include <iostream>

#include "zmqf.h"


bool SendMessage(zmq::socket_t& socket, const std::string& message) {
    try {
        socket.send(zmq::buffer(message), zmq::send_flags::none);
        return true;
    } catch(...) {
        return false;
    }
}

std::string ReceiveMessage(zmq::socket_t& socket) {
    zmq::message_t message;
    bool messageReceived;
    try {
        messageReceived = (bool)socket.recv(message, zmq::recv_flags::none);
    } catch(...) {
        messageReceived = false;
    }
    std::string received(static_cast<char*>(message.data()), message.size());
    if(!messageReceived || received.empty()) {
        return "Error: Node is unavailable";
    }
    return received;
}

int BindSocket(zmq::socket_t& socket) {
    int port = 3000;
    std::string portTemplate = "tcp://*:";
    while(true) {
        try {
            socket.bind(portTemplate + std::to_string(port));
            break;
        } catch(...) {
            port++;
        }
    }
    return port;
}

void Connect(zmq::socket_t &socket, int port) {
    std::string address = "tcp://localhost:" + std::to_string(port);
    socket.connect(address);
}

void Disconnect(zmq::socket_t &socket, int port) {
    std::string address = "tcp://localhost:" + std::to_string(port);
    socket.disconnect(address);
}

int Bind(zmq::socket_t &socket, int id) {
    int port = MAIN_PORT + id;
    std::string address = "tcp://*:" + std::to_string(port);
    while(true){
        try{
            socket.bind(address);
            break;
        }
        catch(...){
            port++;
        }
    }
    return port;
}

void Unbind(zmq::socket_t &socket, int port) {
    std::string address = "tcp://*:" + std::to_string(port);
    socket.unbind(address);
}