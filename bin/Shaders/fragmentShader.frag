uniform sampler2D textureSampler; // Texture sampler uniform

varying vec2 texCoord; // Texture coordinates

void main() {
    // Sample color from the texture using texture coordinates
    vec4 textureColor = texture2D(textureSampler, texCoord);
    // Multiply the sampled texture color with the vertex color
    gl_FragColor = textureColor * vertexColor;
}
