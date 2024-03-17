#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

class Shaders{
    public:
    unsigned int shaderProgram;

    #include <vector>
    #include <string>

    #include <filesystem>

    void CreateShaders() {
        std::vector<std::string> shaderPaths;
        for (const auto& entry : std::filesystem::directory_iterator("./Shaders")) {
            if (entry.path().extension() == ".vert" || entry.path().extension() == ".frag") {
                shaderPaths.push_back(entry.path().string());
            }
        }

        // Compile and link shaders
        shaderProgram = glCreateProgram();
        for (const auto& shaderPath : shaderPaths) {
            std::string shaderSource = ReadShaderSource(shaderPath);
            const char* shaderCode = shaderSource.c_str();
            GLenum shaderType = (shaderPath.find(".vert") != std::string::npos) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
            unsigned int shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderCode, NULL);
            glCompileShader(shader);
            glAttachShader(shaderProgram, shader);
        }
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        std::cout << "Shaders Loaded!\n";
    }





    std::string ReadShaderSource(const std::string& filePath)
    {
        // Check if file exists
        if (!fs::exists(filePath))
        {
            std::cerr << "Shader file not found: " << filePath << std::endl;
            return "";
        }

        std::ifstream shaderFile(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }
};