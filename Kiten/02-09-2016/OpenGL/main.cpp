#include "gfw.hpp"
#include <iostream>
#include <chrono>
#include <random>

static constexpr size_t imgsiz=69;

struct ModelPoint{
	gfw::Vec<GLfloat,3> pos;
	gfw::Vec<GLushort,3> texpos;
};
struct ModelInstance{
	gfw::Mat<GLfloat,4,4> mat;
	GLushort texoff;
	gfw::Vec<GLfloat,3> cmask;
};

void model_bind_points(gfw::GLContext *gl){
	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelPoint), reinterpret_cast<const void*>(offsetof(ModelPoint, pos)));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribIPointer(1, 3, GL_UNSIGNED_SHORT, sizeof(ModelPoint), reinterpret_cast<const void*>(offsetof(ModelPoint, texpos)));
}

void model_bind_instances(gfw::GLContext *gl){
	for(size_t i=0;i<4;i++){
		gl->EnableVertexAttribArray(2+i);
		gl->VertexAttribDivisor(2+i, 1);
		gl->VertexAttribPointer(2+i, 4, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), reinterpret_cast<const void*>(offsetof(ModelInstance, mat)+i*4*sizeof(GLfloat)));
	}
	gl->EnableVertexAttribArray(6);
	gl->VertexAttribDivisor(6, 1);
	gl->VertexAttribIPointer(6, 1, GL_UNSIGNED_SHORT, sizeof(ModelInstance), reinterpret_cast<const void*>(offsetof(ModelInstance, texoff)));

	gl->EnableVertexAttribArray(7);
	gl->VertexAttribDivisor(7, 1);
	gl->VertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(ModelInstance), reinterpret_cast<const void*>(offsetof(ModelInstance, cmask)));
};

struct MyScreen: gfw::Screen{
	GLuint floor_program, floor_model, floor_va;

	GLuint model_program;

	GLuint cube_model, cube_instances, cube_va, cube_tex;

	double rx=2, ry=3, rz=4, dz=0, dx=0, dvy=0, x=0, z=-5, vy=0;

	ModelPoint cube_model_data[24];
	GLuint cube_draw[12][3];
	gfw::Vec<GLubyte,3> cube_img[3*6*imgsiz*imgsiz];

	MyScreen(){
		for(size_t i=0;i<6;i++){
			size_t j=i/2, j1=(j+1)%3, j2=(j+2)%3;
			int kind=i%2?-1:1;
			cube_model_data[4*i+0].pos[j1]=-1;
			cube_model_data[4*i+0].pos[j2]=-1;
			cube_model_data[4*i+0].pos[j]=kind;
			cube_model_data[4*i+0].texpos[0]=0;
			cube_model_data[4*i+0].texpos[1]=0;
			cube_model_data[4*i+0].texpos[2]=i;
			cube_model_data[4*i+1].pos[j1]=1;
			cube_model_data[4*i+1].pos[j2]=-1;
			cube_model_data[4*i+1].pos[j]=kind;
			cube_model_data[4*i+1].texpos[0]=1;
			cube_model_data[4*i+1].texpos[1]=0;
			cube_model_data[4*i+1].texpos[2]=i;
			cube_model_data[4*i+2].pos[j1]=-1;
			cube_model_data[4*i+2].pos[j2]=1;
			cube_model_data[4*i+2].pos[j]=kind;
			cube_model_data[4*i+2].texpos[0]=0;
			cube_model_data[4*i+2].texpos[1]=1;
			cube_model_data[4*i+2].texpos[2]=i;
			cube_model_data[4*i+3].pos[j1]=1;
			cube_model_data[4*i+3].pos[j2]=1;
			cube_model_data[4*i+3].pos[j]=kind;
			cube_model_data[4*i+3].texpos[0]=1;
			cube_model_data[4*i+3].texpos[1]=1;
			cube_model_data[4*i+3].texpos[2]=i;
			cube_draw[2*i+0][0]=4*i+0;
			cube_draw[2*i+0][1]=4*i+1;
			cube_draw[2*i+0][2]=4*i+3;
			cube_draw[2*i+1][0]=4*i+0;
			cube_draw[2*i+1][1]=4*i+3;
			cube_draw[2*i+1][2]=4*i+2;
		}
		std::mt19937_64 rng{42};
		for(auto &i: cube_img){
			i.x=rng()%256;
			i.y=rng()%256;
			i.z=rng()%256;
		}
	}

	void render(uint width, uint height) override{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);

		auto view=gfw::Mat<GLfloat,4,4>(
			gfw::perspective<double>(width, height, std::min(width, height), M_PI/3, 100.0)*
			gfw::translate<double>({0.0, 0.0, -1.0})*
			gfw::rotY(-vy)*
			gfw::translate<double>({-x, 0.0, -z})
		);

		std::vector<ModelInstance> cubes{
			{gfw::Mat<GLfloat,4,4>(
				gfw::scale(5.0)*
				gfw::rotZ(rz)*
				gfw::rotY(ry)*
				gfw::rotX(rx)
			), 0, gfw::Vec<GLfloat,3>{1,1,1}},
			{gfw::Mat<GLfloat,4,4>(
				gfw::translate<double>({-5,0,10})*
				gfw::scale(2.5)*
				gfw::rotZ(2*rz)*
				gfw::rotY(2*ry)*
				gfw::rotX(2*rx)
			), 6, gfw::Vec<GLfloat,3>{1,1,1}},
			{gfw::Mat<GLfloat,4,4>(
				gfw::translate<double>({10,0,10})*
				gfw::scale(4.0)*
				gfw::rotZ(1.5*rz)*
				gfw::rotY(1.5*ry)*
				gfw::rotX(1.5*rx)
			), 12, gfw::Vec<GLfloat,3>{1,1,1}},
		};

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_instances);
		gl->BufferData(GL_ARRAY_BUFFER, cubes.size()*sizeof(ModelInstance), cubes.data(), GL_STATIC_READ);
		gl->BindBuffer(GL_ARRAY_BUFFER, 0);

		gl->UseProgram(floor_program);
		gl->UniformMatrix4fv(gl->GetUniformLocation(floor_program, "view"), 1, GL_FALSE, &view.data[0][0]);
		gl->Uniform4f(gl->GetUniformLocation(floor_program, "floor_color"), 0.5,0.5,0.5,0.5);
		gl->BindVertexArray(floor_va);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		gl->UseProgram(model_program);
		gl->UniformMatrix4fv(gl->GetUniformLocation(model_program, "view"), 1, GL_FALSE, &view.data[0][0]);

		gl->BindVertexArray(cube_va);
		gl->Uniform1i(gl->GetUniformLocation(model_program, "samp"), 0);
		glActiveTexture(GL_TEXTURE0+0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, cube_tex);
		gl->DrawElementsInstanced(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, cube_draw, cubes.size());

		gl->BindVertexArray(0);

		x+=-dz*std::sin(vy)+dx*std::cos(vy);
		z+=dz*std::cos(vy)+dx*std::sin(vy);
		vy+=dvy;
		rx+=0.001;
		ry+=0.003777;
		rz+=0.000343;
	}

	void keydown(const SDL_KeyboardEvent &ev)override {
		if(ev.keysym.sym=='w') dz=0.1;
		if(ev.keysym.sym=='s') dz=-0.1;
		if(ev.keysym.sym=='a') dx=-0.1;
		if(ev.keysym.sym=='d') dx=0.1;
		if(ev.keysym.sym=='q') dvy=0.03;
		if(ev.keysym.sym=='e') dvy=-0.03;
	}

	void keyup(const SDL_KeyboardEvent &ev)override{
		if(ev.keysym.sym=='w') dz=0;
		if(ev.keysym.sym=='s') dz=0;
		if(ev.keysym.sym=='a') dx=0;
		if(ev.keysym.sym=='d') dx=0;
		if(ev.keysym.sym=='q') dvy=0;
		if(ev.keysym.sym=='e') dvy=0;
	}

	void gl_init() override{
		GLint gl_i;
		std::cerr<<glGetString(GL_VENDOR)<<std::endl;
		glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &gl_i);
		if(gl_i<2048){
			throw std::runtime_error("large arrays not supported");
		}

		model_program=gfw::make_program(gl, {
			gfw::make_shader(gl, GL_VERTEX_SHADER, "model-vertex.glsl"),
			gfw::make_shader(gl, GL_FRAGMENT_SHADER, "model-fragment.glsl"),
		});

		floor_program=gfw::make_program(gl, {
			gfw::make_shader(gl, GL_VERTEX_SHADER, "floor-vertex.glsl"),
			gfw::make_shader(gl, GL_FRAGMENT_SHADER, "floor-fragment.glsl"),
		});

		gl->GenBuffers(1, &cube_model);
		gl->GenBuffers(1, &cube_instances);
		gl->GenBuffers(1, &floor_model);
		gl->GenVertexArrays(1, &cube_va);
		gl->GenVertexArrays(1, &floor_va);
		glGenTextures(1, &cube_tex);

		glBindTexture(GL_TEXTURE_2D_ARRAY, cube_tex);
		gl->TexStorage3D(GL_TEXTURE_2D_ARRAY, 4, GL_RGB8, imgsiz, imgsiz, 3*6);
		gl->TexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, imgsiz, imgsiz, 3*6, GL_RGB, GL_UNSIGNED_BYTE, cube_img);
		gl->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gl->TexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//		gl->TexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
		gl->GenerateMipmap(GL_TEXTURE_2D_ARRAY);
		if(glGetError()){
			std::cerr<<"tex: GL error\n";
		}

		gl->BindVertexArray(cube_va);

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_model);
		gl->BufferData(GL_ARRAY_BUFFER, sizeof(cube_model_data), cube_model_data, GL_STATIC_READ);
		model_bind_points(gl);

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_instances);
		model_bind_instances(gl);

		gl->BindVertexArray(floor_va);

		gfw::Vec<GLfloat,3> floor_model_data[]={
			{-100,-8,0},
			{100,-8,0},
			{-100,-8,100},
			{100,-8,100},
		};
		gl->BindBuffer(GL_ARRAY_BUFFER, floor_model);
		gl->BufferData(GL_ARRAY_BUFFER, sizeof(floor_model_data), floor_model_data, GL_STATIC_READ);
		gl->EnableVertexAttribArray(0);
		gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		gl->BindBuffer(GL_ARRAY_BUFFER, 0);
		gl->BindVertexArray(0);

		if(glGetError()){
			std::cerr<<"init: GL error\n";
		}
	}

	void gl_deinit() override{
		gl->DeleteBuffers(1, &floor_model);
		gl->DeleteVertexArrays(1, &floor_va);
		gl->DeleteProgram(floor_program);

		gl->DeleteProgram(model_program);

		gl->DeleteBuffers(1, &cube_model);
		gl->DeleteBuffers(1, &cube_instances);
		gl->DeleteVertexArrays(1, &cube_va);
	}
};

int main(){
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_Window *win=SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	if(!win) throw std::runtime_error(SDL_GetError());
	auto w=gfw::Window(win);

	MyScreen s;

	w.attach(&s);

	bool exit=false;

	while(!exit){
		int timeout=gfw::Event::_process();
		while(true){
			SDL_Event ev;
			if(timeout==-1) timeout=1000;
			int r=SDL_WaitEventTimeout(&ev, timeout);
			timeout=0;
			if(r<0) throw std::runtime_error("event");
			if(!r) break;
			if(ev.type==SDL_WINDOWEVENT){
				gfw::Window::_dispatch_window(ev.window);
			}else if(ev.type==SDL_KEYUP){
				gfw::Window::_dispatch_keyup(ev.key);
			}else if(ev.type==SDL_KEYDOWN){
				gfw::Window::_dispatch_keydown(ev.key);
			}else if(ev.type==SDL_QUIT){
				exit=true;
				break;
			}
		}
	}
	s.gl_detach();

	return 0;
}
