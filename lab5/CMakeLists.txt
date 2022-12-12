# Generate shared / static librarry for hello.c
# STATIC generates `libhello.a`
# SHARED geneartes `libhello.so`

add_library(1_static STATIC src/lib_1.cpp include/lib.h)
add_library(2_static STATIC src/lib_2.cpp include/lib.h)
add_library(1_dynamic SHARED src/lib_1.cpp include/lib.h)
add_library(2_dynamic SHARED src/lib_2.cpp include/lib.h)

target_include_directories(1_static PRIVATE include)
target_include_directories(2_static PRIVATE include)
target_include_directories(1_dynamic PRIVATE include)
target_include_directories(2_dynamic PRIVATE include)


# Genarete `main` executable from `main.cpp`
add_executable(main_static_1 main_static.cpp)
add_executable(main_static_2 main_static.cpp)
add_executable(main_dynamic main_dynamic.cpp)

target_include_directories(main_static_1 PRIVATE include)
target_include_directories(main_static_2 PRIVATE include)
target_include_directories(main_dynamic PRIVATE include)

# Link `main` program with library
target_link_libraries(main_static_1 1_static)
target_link_libraries(main_static_2 2_static)
target_link_libraries(main_dynamic) 


