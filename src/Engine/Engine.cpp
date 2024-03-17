
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "../Quaternion.h"
#include "../GameObject.h"
#include "Input.h"
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

class Engine
{
public:
    GLFWwindow *CurrentWindow;
    int ScreenWidth, ScreenHeight;

    void SetWindow(GLFWwindow *win)
    {
        CurrentWindow = win;
    }

    

    Vector3 skybox = Vector3(0,0,0);
    Vector3 campos = Vector3(0, 0, 0);
    Vector3 camrot = Vector3(0, 0, 0);
    float camfov = 90;

    Vector3 GetCameraForwardDirection()
    {
        Quaternion quat = Quaternion::fromEuler(camrot.x,camrot.y, camrot.z);
        return quat.rotateVector(0.0f, 0.0f, 1.0f);
    }


    Vector3 GetCameraRightDirection()
    {
        Quaternion quat = Quaternion::fromEuler(camrot.x,camrot.y, camrot.z);
        return quat.rotateVector( -1.0f, 0, 0.0f);
    }
    Vector3 GetCameraUpDirection()
    {
        Quaternion quat = Quaternion::fromEuler(camrot.x,camrot.y, camrot.z);
                return quat.rotateVector(0, 1.0f, 0.0f);
    }


    void UpdateCamera(int width, int height)
    {
        glClearColor(skybox.x, skybox.y, skybox.z, 0.0f); //Set background to white
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, width, height);

        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float fovY = camfov;
        float nearClip = 0.1f;
        float farClip = 1000.0f;
        float top = nearClip * tan(fovY * 0.5f * (3.14 / 180.0f));
        float bottom = -top;
        float left = aspectRatio * bottom;
        float right = aspectRatio * top;
        glFrustum(left, right, bottom, top, nearClip, farClip);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(camrot.x, 1, 0, 0);
        glRotatef(camrot.y, 0, 1, 0);
        glRotatef(camrot.z, 0, 0, 1);
        glTranslatef(campos.x, campos.y, campos.z);
    }



    bool mouseLocked = false;
    void ToggleMouseLock(bool enabled)
    {
        mouseLocked = enabled;
        glfwSetInputMode(CurrentWindow, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }


    void EngineStart()
    {
        glfwSetKeyCallback(CurrentWindow, Input::KeyCallback);
        glfwSetMouseButtonCallback(CurrentWindow, Input::MouseButtonCallback);
    }

    void EngineUpdate()
    {
        glfwGetWindowSize(CurrentWindow, &ScreenWidth, &ScreenHeight);
        UpdateCamera(ScreenWidth, ScreenHeight);
    }
};
