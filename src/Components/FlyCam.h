#ifndef FlyCam_H
#define FlyCam_H

#include <tuple> 
#include "../Vector.h"
#include <algorithm>

class FlyCam
{
private:
    GameObject& obj;
    
public:
    FlyCam(GameObject& obj) : obj(obj) {}

    void UpdatePos(Engine* app, float cameraSpeed){
        if (Input::GetKey(GLFW_KEY_W))
        {
            app->campos = app->campos + app->GetCameraForwardDirection() * cameraSpeed;
        }

        if (Input::GetKey(GLFW_KEY_A))
        {
            app->campos = app->campos + app->GetCameraRightDirection() * -cameraSpeed;
        }

        if (Input::GetKey(GLFW_KEY_S))
        {
            app->campos = app->campos + app->GetCameraForwardDirection() * -cameraSpeed;
        }

        if (Input::GetKey(GLFW_KEY_D))
        {
            app->campos = app->campos + app->GetCameraRightDirection() * cameraSpeed;
        }
        if (Input::GetKey(GLFW_KEY_SPACE))
        {
            app->campos = app->campos + Vector3(0, 1, 0) *-cameraSpeed;
        }

        if (Input::GetKey(GLFW_KEY_LEFT_CONTROL))
        {
            app->campos = app->campos + Vector3(0, 1, 0) * cameraSpeed;
        }

    }

    std::tuple<Vector3, double, double, double, double> UpdateMouse(GLFWwindow* window, double lastMouseX, double lastMouseY, double X, double Y, float sensitivity)
    {
            double mouseX = Input::GetMouseX(window);
            double mouseY = Input::GetMouseY(window);

            double deltaX = (mouseX - lastMouseX) * sensitivity; 
            double deltaY = (mouseY - lastMouseY) * sensitivity;

            // Update last mouse position for the next frame
            double newlastMouseX = mouseX;
            double newlastMouseY = mouseY;
    
            

            Vector3 deltaRotation = Vector3(Y , X, 0.0f);

            // Return the delta rotation vector along with the updated lastMouseX and lastMouseY values
            return std::make_tuple(deltaRotation, newlastMouseX, newlastMouseY, deltaX, deltaY);
    }
};

#endif
