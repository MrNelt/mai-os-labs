add_executable(lab4
        main.cpp
        include/parent.h src/parent.cpp)

target_include_directories(lab4 PRIVATE include)

add_executable(child4
        src/child.cpp
        include/string_to_vector.h src/string_to_vector.cpp)

target_include_directories(child4 PRIVATE include)

add_dependencies(lab4 child4)