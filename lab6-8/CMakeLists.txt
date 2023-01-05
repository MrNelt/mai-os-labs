add_library(topology STATIC src/topology.cpp include/topology.h)
add_library(zmfq STATIC src/zmqf.cpp include/zmqf.h)
add_library(search STATIC include/search.h src/search.cpp)

target_include_directories(topology PRIVATE include)
target_include_directories(zmfq PRIVATE include)
target_include_directories(search PRIVATE include)


target_link_libraries(topology PRIVATE zmq)
target_link_libraries(zmfq PRIVATE zmq)

add_executable(client client.cpp include/handlernode.hpp include/calcnode.hpp)
target_link_libraries(client PRIVATE topology)
target_link_libraries(client PRIVATE zmfq)
target_link_libraries(client PRIVATE search)


add_executable(server server.cpp include/handlernode.hpp include/calcnode.hpp)
target_link_libraries(server PRIVATE topology)
target_link_libraries(server PRIVATE zmfq)
target_link_libraries(server PRIVATE search)


target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)