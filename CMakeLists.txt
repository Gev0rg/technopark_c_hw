cmake_minimum_required(VERSION 3.14)

project(stl)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/MySet.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/MySet.hpp)

set(STL_LIB ${SOURCES} ${HEADERS})
set(STL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${STL_LIB}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${STL_INCLUDE_DIRS})

enable_testing()
add_subdirectory(tests)    
