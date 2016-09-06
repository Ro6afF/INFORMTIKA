#version 330

layout(location=0) in vec3 point_pos;
layout(location=1) in uvec3 point_tex;

layout(location=2) in mat4 inst_mat;
layout(location=6) in uint inst_texoff;
layout(location=7) in vec3 inst_cmask;

uniform mat4 view;

out vec3 vert_tex;
out vec3 vert_cmask;

void main(){
	while(true);
	gl_Position=view*inst_mat*vec4(point_pos,1);
	vert_tex=point_tex+uvec3(0,0,inst_texoff);
	vert_cmask=inst_cmask;
}
