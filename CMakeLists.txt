cmake_minimum_required(VERSION 3.15)

project(Breakout)

add_executable(${PROJECT_NAME} glad.c shader.cpp texture.cpp resourceLoader.cpp game.cpp main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
