#include "Engine.cpp"

// Reference custom scripts in here
#include "Components.cpp"

class Program
{
public:
    // REQUIRED FOR INITIALIZATION
    Engine *app;
    void SetEngine(Engine *instance)
    {
        app = instance;
    }

    // Scene
    GameObject Cube = GameObject(Vector3(), Vector3(0, 0, 0));
    MeshRenderer Renderer = MeshRenderer(Cube);
    GameObject Camera = GameObject(Vector3(), Vector3());
    FlyCam Cam = FlyCam(Camera);

    // Variables
    double lastx, lasty;
    double mousex, mousey;

    void Start()
    {
        app->skybox = Vector3(0.1f, 0.1f, 0.1f);

        app->campos = (Vector3(0, 0, -5));
        app->camfov = 90;
    }

    void Update(float deltaTime)
    {

        //Camera controls

        float cameraSpeed = 5 * deltaTime;

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

        app->ToggleMouseLock(true);

        if (app->mouseLocked)
        {
            double deltaX, deltaY;
            std::tie(app->camrot, lastx, lasty, deltaX, deltaY) = Cam.UpdateMouse(app->CurrentWindow, app->mouseLocked, lastx, lasty, mousex, mousey, 10 * deltaTime);
            mousex += deltaX;
            mousey += deltaY;
            mousey = std::clamp(mousey, -90.0, 90.0);
        }


        //Scene Rendering

        //render primitve cube
        objl::Material defaultMaterial;
        defaultMaterial.Ka = objl::Vector3(1.0f, 1.0f, 1.0f); // Ambient color
        defaultMaterial.Kd = objl::Vector3(1.0f, 1.0f, 1.0f); // Diffuse color (albedo)
        defaultMaterial.Ks = objl::Vector3(1.0f, 1.0f, 1.0f); // Specular color
        defaultMaterial.Ns = 0.0f;                            // Specular exponent
        defaultMaterial.Ni = 1.0f;                            // Optical density
        defaultMaterial.d = 1.0f;                             // Dissolve variable
        defaultMaterial.illum = 2;                            // Illumination variable
        Renderer.Render("./Models/cube.obj", std::vector<std::string> {"./Textures/Required/None.png"}, defaultMaterial);
    }
};
