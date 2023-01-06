#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <shader/shader.h>
#include <gameHeaders/game.h>
#include <gameHeaders/resourceLoader.h>
#include "iostream"
#include "sstream"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

Game breakoutGame(WINDOW_WIDTH, WINDOW_HEIGHT);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

    if (key >= 0 && key < 1024) 
    {
        if (action == GLFW_PRESS) 
        {
            breakoutGame.SetKey(key, true);
        }
        else if (action == GLFW_RELEASE) 
        {
            breakoutGame.SetKey(key, false);
        }
    }
}

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Could not initialize GLAD" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    breakoutGame.Init();

    float currTime = 0.0f;
    float prevTime = 0.0f;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        currTime = glfwGetTime();
        deltaTime = currTime - prevTime;
        prevTime = currTime;

        glfwPollEvents();

        breakoutGame.ProcessInput(deltaTime);

        // Rendering code
        breakoutGame.Update(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        breakoutGame.Render();

        glfwSwapBuffers(window);
    }

    // ResourceLoader::Clear();
    
    glfwTerminate();

    return 0;
}
