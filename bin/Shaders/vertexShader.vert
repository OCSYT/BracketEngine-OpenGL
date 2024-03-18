varying vec4 vertexColor;
varying vec2 texCoord; // Add varying variable for texture coordinates

void main() {
    gl_Position = ftransform();
    vertexColor = gl_Color; // Pass color to fragment shader
    texCoord = gl_TexCoord[0].xy; // Pass texture coordinates to fragment shader
}
