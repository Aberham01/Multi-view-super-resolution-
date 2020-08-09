#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =1) in vec3 aColor;

out vec3 uv;
uniform mat4 projection;
uniform float res;

uniform mat4 view;
void main()
{
	vec3 ver= aPos*res;
    gl_Position = projection*view*vec4(ver, 1.0);
    //uv = aPos;
    uv = (aPos*0.5)+0.5;
}