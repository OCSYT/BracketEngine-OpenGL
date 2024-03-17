#ifndef CubeRenderer_H
#define CubeRenderer_H

class CubeRenderer
{
private:
    GameObject& obj;

public:
    CubeRenderer(GameObject& obj) : obj(obj) {}
    void render()
    {
        // Define the vertices of the cube
        GLfloat vertices[] = {
            // Front face
            -0.5f, 0.5f, 0.5f,  // Top left
            0.5f, 0.5f, 0.5f,   // Top right
            0.5f, -0.5f, 0.5f,  // Bottom right
            -0.5f, -0.5f, 0.5f, // Bottom left
            // Back face
            -0.5f, 0.5f, -0.5f,  // Top left
            0.5f, 0.5f, -0.5f,   // Top right
            0.5f, -0.5f, -0.5f,  // Bottom right
            -0.5f, -0.5f, -0.5f, // Bottom left
            // Left face
            -0.5f, 0.5f, 0.5f,   // Top front
            -0.5f, 0.5f, -0.5f,  // Top back
            -0.5f, -0.5f, -0.5f, // Bottom back
            -0.5f, -0.5f, 0.5f,  // Bottom front
            // Right face
            0.5f, 0.5f, 0.5f,    // Top front
            0.5f, 0.5f, -0.5f,   // Top back
            0.5f, -0.5f, -0.5f,  // Bottom back
            0.5f, -0.5f, 0.5f,   // Bottom front
            // Top face
            -0.5f, 0.5f, 0.5f,  // Front left
            0.5f, 0.5f, 0.5f,   // Front right
            0.5f, 0.5f, -0.5f,  // Back right
            -0.5f, 0.5f, -0.5f, // Back left
            // Bottom face
            -0.5f, -0.5f, 0.5f, // Front left
            0.5f, -0.5f, 0.5f,  // Front right
            0.5f, -0.5f, -0.5f, // Back right
            -0.5f, -0.5f, -0.5f // Back left
        };

        // Define colors for each face (in RGB format)
        GLfloat colors[] = {
            // Front face - Red
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            // Back face - Green
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            // Left face - Blue
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            // Right face - Yellow
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            // Top face - Cyan
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
            // Bottom face - Magenta
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f
        };

        // Apply scale transformation
        for (int i = 0; i < 72; i++)
        {
            vertices[i] *= 1;
        }

        // Apply rotation and translation transformations
        glPushMatrix();
        glTranslatef(obj.position.x, obj.position.y, obj.position.z);
        glRotatef(obj.rotation.x * 180 / 3.14, 1.0f, 0.0f, 0.0f);
        glRotatef(obj.rotation.y * 180 / 3.14, 0.0f, 1.0f, 0.0f);
        glRotatef(obj.rotation.z * 180 / 3.14, 0.0f, 0.0f, 1.0f);

        // Draw the cube
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY); // Enable color array
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors); // Specify color array

        glDrawArrays(GL_QUADS, 0, 24);

        glDisableClientState(GL_COLOR_ARRAY); // Disable color array
        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();
    }
};

#endif
