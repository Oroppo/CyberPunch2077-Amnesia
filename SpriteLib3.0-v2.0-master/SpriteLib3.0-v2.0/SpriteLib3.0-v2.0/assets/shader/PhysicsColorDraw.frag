#version 420

out vec4 FragColor;

in vec2 TexCoords;

layout (binding = 0) uniform sampler2D uTex;
uniform float uTransparency=1.0f;
uniform vec4 uColor;

void main() 
{
	vec4 mask = texture(uTex, TexCoords);

	FragColor.rgb = uColor.rgb;
	FragColor.a = uColor.a * mask.a;
}