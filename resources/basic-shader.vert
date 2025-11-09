// OpenGL 2.1 vertex shader

uniform vec2 iResolution;

varying vec2 pos;
varying vec4 texCoord;

void main()
{
    // Compute texture coordinate
    texCoord = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // Transform vertex to clip space
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // Compute normalized position for screen-space effects
    pos = gl_Vertex.xy / iResolution.xy - 0.5;

    // Pass through color
    gl_FrontColor = gl_Color;

    // Pass texture coordinate (for fixed-function pipeline)
    gl_TexCoord[0] = texCoord;
}
