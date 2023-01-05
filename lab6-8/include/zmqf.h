#ifndef ZMQF_H
#define ZMQF_H

#include <zmq.hpp>
const int MAIN_PORT = 4040;

bool SendMessage(zmq::socket_t& socket, const std::string& message);

std::string ReceiveMessage(zmq::socket_t& socket);

int BindSocket(zmq::socket_t& socket);

void Connect(zmq::socket_t &socket, int port);

void Disconnect(zmq::socket_t &socket, int port);

int Bind(zmq::socket_t &socket, int id);

void Unbind(zmq::socket_t &socket, int port);

#endif