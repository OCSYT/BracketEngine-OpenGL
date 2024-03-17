#include "Input.h"

std::unordered_map<int, int> Input::previousKeyState;
std::unordered_map<int, int> Input::keyState;
std::unordered_map<int, int> Input::mouseButtonState;
std::unordered_map<int, int> Input::keyPressCount;
bool Input::GetKey(int key) {
    auto it = keyState.find(key);
    if (it != keyState.end()) {
        return it->second == GLFW_PRESS || it->second == GLFW_REPEAT;
    }
    return false;
}

bool Input::GetMouseButton(int button) {
    auto it = mouseButtonState.find(button);
    if (it != mouseButtonState.end()) {
        return it->second == GLFW_PRESS || it->second == GLFW_REPEAT;
    }
    return false;
}

double Input::GetMouseX(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return xpos;
}

double Input::GetMouseY(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return ypos;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    previousKeyState[key] = keyState[key];
    keyState[key] = action;

    // Increment the press count if the key is pressed
    if (action == GLFW_PRESS) {
        keyPressCount[key]++;
    }
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButtonState[button] = action;
}

