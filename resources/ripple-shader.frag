uniform sampler2D image;
uniform float time;
uniform vec2 iResolution;

varying vec4 texCoord;

void main()
{
    vec2 uv = texCoord.st;

    // Normalize coordinates to [0,1]
    vec2 st = uv;

    // Compute distance from center
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(st, center);

    // Ripple effect
    float ripple = sin(10.0 * dist - time * 5.0) * 0.02;

    // Offset UV radially
    vec2 offset = normalize(st - center) * ripple;
    vec4 color = texture2D(image, st + offset);

    gl_FragColor = color;
}
