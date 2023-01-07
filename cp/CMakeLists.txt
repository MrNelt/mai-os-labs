add_executable(serverGame server.cpp include/game.hpp include/mutex.h include/mappedFile.h src/mutex.cpp)
add_executable(clientGame client.cpp include/game.hpp include/mutex.h include/mappedFile.h src/mutex.cpp)

target_include_directories(serverGame PRIVATE include)
target_include_directories(clientGame PRIVATE include)

target_link_libraries(serverGame PRIVATE Threads::Threads)
target_link_libraries(clientGame PRIVATE Threads::Threads)