cmake_minimum_required(VERSION 3.15)

project(Breakout)

add_executable(${PROJECT_NAME} 
    src/glad.c 
    src/shader.cpp 
    src/texture.cpp 
    src/resourceLoader.cpp 
    src/spriteRenderer.cpp 
    src/game.cpp 
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} GL dl glfw)
