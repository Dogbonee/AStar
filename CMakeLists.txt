cmake_minimum_required(VERSION 3.30)
project(AStar)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cpp src/Application.cpp src/Application.h src/AStar.cpp src/AStar.h src/Graph.cpp src/Graph.h src/Vector2Hash.cpp src/Vector2Hash.h)
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 3 REQUIRED COMPONENTS System Graphics)

add_executable(AStar ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::System SFML::Graphics)

