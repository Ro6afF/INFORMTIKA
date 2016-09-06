#version 330

layout(location=0) in vec3 p;
layout(location=1) in vec3 color;

layout(location=2) in mat4 cube;

uniform mat4 view;

out vec3 vert_color;

void main(){
	gl_Position=view*cube*vec4(p,1);
	vert_color=color;
}
