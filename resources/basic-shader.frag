// OpenGL 2.1 fragment shader

uniform sampler2D image;

varying vec2 pos;
varying vec4 texCoord;

void main()
{
    // Use interpolated values from vertex shader
    vec2 uv = pos;
    vec2 st = texCoord.st;

    // Return black
    vec4 color = vec4(0.0);

    // Write output color
    gl_FragColor = color;

    // sample the texture
    gl_FragColor = texture2D(image, st);
}
