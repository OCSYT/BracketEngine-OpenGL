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

    std::tuple<Vector3, double, double, double, double> UpdateMouse(GLFWwindow* window, bool mouseLocked, double lastMouseX, double lastMouseY, double X, double Y, float sensitivity)
    {
        if (mouseLocked)
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
        
        // Return default values when mouse is not locked
        return std::make_tuple(Vector3(0.0f, 0.0f, 0.0f), lastMouseX, lastMouseY, 0, 0);
    }
};

#endif
