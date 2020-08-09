#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 20) out;
uniform mat4 projection;
out vec3 col;
const int a = 1;
void main() {   


    gl_Position =vec4(-0.5,0.5,+1.4,1.)*projection; 
	col = vec3(-1.,1.,0.);
    EmitVertex();

    gl_Position =vec4(0.5,0.5,-1.8,1.)*projection; 
	col = vec3(1.,1.,0.);
    EmitVertex();

	gl_Position = vec4(-0.5,-0.5,1.2,1.)*projection; 
	col = vec3(-1.,-1.,0.);
    EmitVertex();


	 gl_Position =vec4(0.5,-0.5,-2.2,1.)*projection; 
	 col = vec3(1.,-1.,0.);
    EmitVertex();

    
	EndPrimitive();

	
	
	
}  