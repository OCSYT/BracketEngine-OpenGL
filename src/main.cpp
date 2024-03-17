#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Quaternion.h"
#include "Vector.h"
#include "GameObject.h"
#include "Engine/Input.cpp"
#include "Engine/Program.cpp"
#include "Shaders.cpp"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 800;


int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Program", NULL, NULL);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    Shaders *Rendering = new Shaders();
    Engine* engine = new Engine();
    Program* program = new Program();
    Rendering->CreateShaders();
    engine->SetWindow(window);
    program->SetEngine(engine);
    engine->EngineStart();
    program->Start();
    float oldTimeSinceStart = 0;
    float deltaTime = 0;
    while (!glfwWindowShouldClose(window)) {
        float timeSinceStart = static_cast<float>(glfwGetTime());
        deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;
        glUseProgram(Rendering->shaderProgram);
        engine->EngineUpdate(deltaTime);
        program->Update(deltaTime);

        glUseProgram(0);
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
