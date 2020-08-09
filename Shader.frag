#version 330 core
out vec4 FragColor;

in vec3 uv;
uniform sampler2D texture;
uniform float test;
void main()
{    vec4 color =  texture2D(texture,uv.xy);
float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    FragColor =vec4(vec3(gray),1.);
}