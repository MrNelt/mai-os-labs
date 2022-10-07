set(CMAKE_C_STANDARD 11)

add_executable(lab2
        main.cpp)

target_include_directories(lab2 PRIVATE include)

add_executable(child
        src/child.cpp
        include/string_to_vector.h)

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)