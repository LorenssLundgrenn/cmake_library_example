# cmake -S ./ -B ./build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake_minimum_required(VERSION 3.28)
project(my-project)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ./include
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

find_package(mytarget REQUIRED)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE 
    mytarget::mytarget
)