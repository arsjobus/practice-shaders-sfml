uniform sampler2D image;
uniform float time;
uniform vec2 iResolution;

varying vec4 texCoord;

void main()
{
    vec2 uv = texCoord.st;

    // Animated scanlines
    float scanline = sin((uv.y * iResolution.y * 1.5) + time * 10.0) * 0.1;

    // Slight RGB shift
    float r = texture2D(image, uv + vec2(0.01*sin(time*3.0), 0.0)).r;
    float g = texture2D(image, uv).g;
    float b = texture2D(image, uv - vec2(0.01*sin(time*2.0), 0.0)).b;

    vec4 color = vec4(r, g, b, 1.0) - vec4(scanline, scanline, scanline, 0.0);

    gl_FragColor = color;
}
