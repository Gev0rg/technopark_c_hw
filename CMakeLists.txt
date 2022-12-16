cmake_minimum_required(VERSION 3.14)

project(stl)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion -fprofile-arcs")
string(APPEND CMAKE_CXX_FLAGS " -Wlogical-op  -Wduplicated-cond -Wcast-qual -Wcast-align -g")

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Stl.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/Stl.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/Iterator.hpp
            )

set(STL_LIB ${SOURCES} ${HEADERS})
set(STL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${STL_LIB}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${STL_INCLUDE_DIRS})

enable_testing()
add_subdirectory(tests)    
