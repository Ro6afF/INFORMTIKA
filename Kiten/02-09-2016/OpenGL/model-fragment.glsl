#version 330

in vec3 vert_tex;
in vec3 vert_cmask;
uniform sampler2DArray samp;

layout(location=0) out vec4 color;

void main(){
	color=texture(samp, vert_tex)*vec4(vert_cmask,1);
	//color=vec4(1,1,0,1);
}
