#include "gfw.hpp"
#include <iostream>
#include <iterator>
#include <string>
namespace gfw{

GLuint make_shader(GLContext *gl, GLenum tp, const char *name){
	std::ifstream fin(name);
	if(!fin) throw std::runtime_error("failed to open "+std::string(name));
	auto code=std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

	GLuint shader=gl->CreateShader(tp);
	const char *s=code.c_str();
	GLint l=code.size();
	gl->ShaderSource(shader, 1, &s, &l);

	gl->CompileShader(shader);

	GLint status;
	gl->GetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status==GL_FALSE){
		GLint len=0;
		gl->GetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		char err[len+1];
		GLsizei len2;
		gl->GetShaderInfoLog(shader, len+1, &len2, err);
		err[len2]=0;

		throw std::runtime_error("shader compilation failed:\n"+std::string(err));
	}

	return shader;
}

GLuint make_program(GLContext *gl, std::vector<GLuint> shaders, bool destroy){
	GLuint prog=gl->CreateProgram();
	for(auto sh: shaders){
		gl->AttachShader(prog, sh);
	}

	gl->LinkProgram(prog);

	GLint status;
	gl->GetProgramiv(prog, GL_LINK_STATUS, &status);

	if(status==GL_FALSE){
		GLint len=0;
		gl->GetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		char err[len+1];
		GLsizei len2;
		gl->GetProgramInfoLog(prog, len+1, &len2, err);
		err[len2]=0;

		throw std::runtime_error("program link failed:\n"+std::string(err));
	}

	for(GLuint sh: shaders){
		gl->DetachShader(prog, sh);
		if(destroy){
			gl->DeleteShader(sh);
		}
	}

	return prog;
}

}
