cmake_minimum_required(VERSION 3.15)

project(MySet)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TEST) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror ")
    if(COVERAGE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0 ")
    endif()
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3")
endif()

set(SOURCES "src/MySet.cpp")
set(HEADERS "include/MySet.hpp")

set(MYSET_LIB_LIBRARIES ${PROJECT_NAME}) 
set(MYSET_LIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} ${SOURCES})

if(TEST)
    if(COVERAGE)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
    endif()
    enable_testing()
    add_subdirectory(tests)
endif()