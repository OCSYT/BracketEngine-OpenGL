uniform sampler2D texture2;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture2, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = pixel;
}