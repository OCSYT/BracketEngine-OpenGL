#include <iostream>
#include <map> // Include map header
#include "../GameObject.h"
#include "../OBJ_Loader.h"
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

class MeshRenderer
{
private:
    GameObject &obj;
    objl::Loader loader;
    bool modelLoaded = false;
    std::map<std::string, GLuint> textureCache; // Texture cache

public:
    MeshRenderer(GameObject &obj) : obj(obj) {}

    GLuint loadTexture(const std::string &path)
    {
        // Check if texture already loaded
        auto it = textureCache.find(path);
        if (it != textureCache.end())
        {
            return it->second; // Return cached texture ID
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Load texture using stb_image
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);

            // Store texture in cache
            textureCache[path] = textureID;
        }
        else
        {
            std::cerr << "Failed to load texture: " << path << std::endl;
            stbi_image_free(data);

            // Check if texture already loaded
            auto it = textureCache.find("./Textures/Required/None.png");
            if (it != textureCache.end())
            {
                return it->second; // Return cached texture ID
            }

            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Load texture using stb_image
            int width, height, nrChannels;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                GLenum format;
                if (nrChannels == 1)
                    format = GL_RED;
                else if (nrChannels == 3)
                    format = GL_RGB;
                else if (nrChannels == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                // Set texture parameters
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);

                // Store texture in cache
                textureCache[path] = textureID;
            }
        }

        return textureID;
    }

    void render(std::string modelPath, std::vector<std::string> texturePaths)
    {
        // Load the OBJ File
        if (!modelLoaded)
        {
            if (!loader.LoadFile(modelPath))
            {
                std::cerr << "Failed to load OBJ file: " << modelPath << std::endl;
                return;
            }
            else
            {
                modelLoaded = true;
            }
        }

        objl::Material defaultMaterial;
        defaultMaterial.Ka = objl::Vector3(1.0f, 1.0f, 1.0f); // Ambient color
        defaultMaterial.Kd = objl::Vector3(1.0f, 1.0f, 1.0f); // Diffuse color
        defaultMaterial.Ks = objl::Vector3(1.0f, 1.0f, 1.0f); // Specular color
        defaultMaterial.Ns = 0.0f;                            // Specular exponent
        defaultMaterial.Ni = 1.0f;                            // Optical density
        defaultMaterial.d = 1.0f;                             // Dissolve variable
        defaultMaterial.illum = 2;                            // Illumination variable

        int index = 0;
        // Loop through each loaded mesh and draw it
        for (const auto &mesh : loader.LoadedMeshes)
        {
            glEnable(GL_TEXTURE_2D);
            if (texturePaths.size() <= loader.LoadedMeshes.size())
            {
                if (index < texturePaths.size())
                {
                    GLuint textureID = loadTexture(texturePaths[index]);
                    glBindTexture(GL_TEXTURE_2D, textureID);
                }
                else
                {
                    GLuint textureID = loadTexture("./Textures/Required/None.png");
                    glBindTexture(GL_TEXTURE_2D, textureID);
                }
            }
            else
            {
                GLuint textureID = loadTexture("./Textures/Required/None.png");
                glBindTexture(GL_TEXTURE_2D, textureID);
            }

            const auto &material = defaultMaterial;

            // Enable material colors
            glColor3f(material.Kd.X, material.Kd.Y, material.Kd.Z);

            // Loop through each face of the mesh
            for (size_t i = 0; i < mesh.Indices.size(); i += 3)
            {
                glBegin(GL_TRIANGLES);

                // Draw each vertex of the face
                for (size_t j = 0; j < 3; ++j)
                {
                    const auto &vertex = mesh.Vertices[mesh.Indices[i + j]];

                    // Assign texture coordinates
                    glTexCoord2f(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y);

                    // Draw vertex
                    glVertex3f(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
                }

                glEnd();
            }
            ++index;
            glDisable(GL_TEXTURE_2D);
        }
    }
};
