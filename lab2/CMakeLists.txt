cmake_minimum_required(VERSION 3.20)

add_executable(lab2
        main.cpp
        include/parent.h src/parent.cpp)

# target_include_directories(parent.out PRIVATE include)

add_executable(child
        src/child.cpp
        include/string_to_vector.h src/strint_to_vector.cpp)

# target_include_directories(child.out PRIVATE include)

add_dependencies(lab2 child)