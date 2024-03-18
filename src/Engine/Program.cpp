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
    GameObject Cube = GameObject(Vector3(), Vector3(0,0,0), Vector3(1,1,1));
    MeshRenderer Renderer = MeshRenderer(Cube);
    GameObject Camera = GameObject(Vector3(), Vector3(), Vector3(1,1,1));
    FlyCam Cam = FlyCam(Camera);

    // Variables
    double lastx, lasty;
    double mousex, mousey;

    void Start()
    {
        app->skybox = Vector3(0.1f, 0.1f, 0.1f);

        app->campos = (Vector3(0, 0, -5));
        app->camrot = Vector3();
        app->camfov = 90;
    }

    void Update(float deltaTime)
    {

        //Camera controls

        app->ToggleMouseLock(true);


        float cameraSpeed = 5 * deltaTime;
        if (app->mouseLocked)
        {
            Cam.UpdatePos(app, cameraSpeed);
            
            double deltaX, deltaY;
            std::tie(app->camrot, lastx, lasty, deltaX, deltaY) = Cam.UpdateMouse(app->CurrentWindow, lastx, lasty, mousex, mousey, 10 * deltaTime);
            mousex += deltaX;
            mousey += deltaY;
            mousey = std::clamp(mousey, -90.0, 90.0);
        }


        //render primitve cube
        objl::Material defaultMaterial;
        defaultMaterial.Ka = objl::Vector3(1.0f, 1.0f, 1.0f); // Ambient color
        defaultMaterial.Kd = objl::Vector3(1.0f, 1.0f, 1.0f); // Diffuse color (albedo)
        defaultMaterial.Ks = objl::Vector3(1.0f, 1.0f, 1.0f); // Specular color
        defaultMaterial.Ns = 0.0f;                            // Specular exponent
        defaultMaterial.Ni = 1.0f;                            // Optical density
        defaultMaterial.d = 1.0f;                             // Dissolve variable
        defaultMaterial.illum = 2;                            // Illumination variable
        Renderer.Render("./Models/Primitive/cube.obj", std::vector<std::string> {"./Textures/Required/None.png"}, defaultMaterial);
    }
};
