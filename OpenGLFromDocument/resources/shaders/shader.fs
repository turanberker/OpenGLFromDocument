#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform float someUniform;
void main()
{
    FragColor = vec4(0.0f,someUniform,0.0f, 1.0f);
}