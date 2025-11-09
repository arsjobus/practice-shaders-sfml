// OpenGL 2.1 fragment shader

uniform sampler2D image;
uniform float time; // pass time in seconds from your application

varying vec2 pos;
varying vec4 texCoord;

void main()
{
    vec2 st = texCoord.st;

    // Wavy effect
    float wave = sin(st.y * 10.0 + time * 2.0) * 0.02;

    // Offset each color channel slightly differently
    float r = texture2D(image, st + vec2(wave, 0.0)).r;
    float g = texture2D(image, st + vec2(-wave, 0.0)).g;
    float b = texture2D(image, st + vec2(0.0, wave)).b;

    vec4 color = vec4(r, g, b, 1.0);

    gl_FragColor = color;
}
