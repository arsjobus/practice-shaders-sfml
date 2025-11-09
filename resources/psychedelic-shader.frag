// OpenGL 2.1 fragment shader
uniform sampler2D image;     // your texture
uniform float time;           // pass elapsed time from your app
uniform vec2 iResolution;     // window size

varying vec2 pos;
varying vec4 texCoord;

void main()
{
    // Normalized UV coordinates
    vec2 uv = texCoord.st;

    // Center the UVs around (0,0) for radial effects
    vec2 center = uv - 0.5;

    // Compute distance and angle from center
    float dist = length(center);
    float angle = atan(center.y, center.x);

    // Create animated color bands
    float band = sin(10.0 * dist - time * 5.0 + angle * 5.0);

    // Mix multiple sine waves for psychedelic motion
    float r = sin(band + time * 3.0);
    float g = sin(band + time * 2.0 + 1.0);
    float b = sin(band + time * 4.0 + 2.0);

    // Sample the texture for detail and modulate with color bands
    vec4 tex = texture2D(image, uv);
    vec4 color = vec4(r, g, b, 1.0) * tex;

    // Increase saturation and contrast
    color = pow(color, vec4(1.5));

    gl_FragColor = color;
}
