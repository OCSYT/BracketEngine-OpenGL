#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <unordered_map>

class Input {
public:
    static bool GetKey(int key);

    static bool GetMouseButton(int button);

    static double GetMouseX(GLFWwindow* window);
    static double GetMouseY(GLFWwindow* window);

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

private:
    static std::unordered_map<int, int> previousKeyState;
    static std::unordered_map<int, int> keyState;
    static std::unordered_map<int, int> mouseButtonState;
    static std::unordered_map<int, int> keyPressCount;
};

#endif // INPUT_H
