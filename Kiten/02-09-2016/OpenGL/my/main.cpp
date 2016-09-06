#include "gfw.hpp"
#include <iostream>
#include <chrono>

struct MyScreen: gfw::Screen{
	GLuint cube_program, floor_program;

	GLuint cube_model, cube_instances, floor_model;

	GLuint cube_va, floor_va;

	double rx=2, ry=3, rz=4, dz=0, dx=0, dvy=0, x=0, z=-5, vy=0;

	GLuint draw_cube[12][3];

	MyScreen(){
		for(size_t i=0;i<12;i++){
			size_t kind=i%2, side=(i/2)%2, j=i/4;
			size_t verts[4];
			verts[0]=0;
			verts[1]=1;
			verts[2]=2;
			verts[3]=3;
			for(size_t k=0;k<4;k++){
				size_t m=(1<<j)-1;
				verts[k]=((verts[k]&~m)<<1) | (verts[k]&m) | (side<<j);
			}
			draw_cube[i][0]=verts[kind?3:0];
			draw_cube[i][1]=verts[1];
			draw_cube[i][2]=verts[2];
		}
	}

	using CubeData=gfw::Mat<GLfloat,4,4>;

	void render(uint width, uint height) override{
		auto view=gfw::Mat<GLfloat,4,4>(
			gfw::perspective<double>(width, height, std::min(width, height), M_PI/6, 100.0)*
			gfw::translate<double>({0.0, 0.0, -1.0})*
			gfw::rotY(-vy)*
			gfw::translate<double>({-x, 0.0, -z})
		);

		std::vector<CubeData> cubes{
			/*gfw::Mat<GLfloat,4,4>(
				gfw::scale(5.0)*
				gfw::rotZ(rz)*
				gfw::rotY(ry)*
				gfw::rotX(rx)
			),*/
			gfw::Mat<GLfloat,4,4>(
				gfw::translate<double>({0,0,0})*
				gfw::scale(2.5)*
				gfw::rotZ(2*rz)*
				gfw::rotY(2*ry)*
				gfw::rotX(2*rx)
			)/*,
			gfw::Mat<GLfloat,4,4>(
				gfw::translate<double>({10,0,10})*
				gfw::scale(4.0)*
				gfw::rotZ(1.5*rz)*
				gfw::rotY(1.5*ry)*
				gfw::rotX(1.5*rx)
			),*/
		};

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_instances);
		gl->BufferData(GL_ARRAY_BUFFER, cubes.size()*sizeof(CubeData), cubes.data(), GL_STATIC_READ);
		gl->BindBuffer(GL_ARRAY_BUFFER, 0);

		gl->UseProgram(cube_program);
		gl->UniformMatrix4fv(gl->GetUniformLocation(cube_program, "view"), 1, GL_FALSE, &view.data[0][0]);

		gl->BindVertexArray(cube_va);
		gl->DrawElementsInstanced(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, draw_cube, cubes.size());

		gl->UseProgram(floor_program);
		gl->UniformMatrix4fv(gl->GetUniformLocation(floor_program, "view"), 1, GL_FALSE, &view.data[0][0]);
		gl->Uniform4f(gl->GetUniformLocation(floor_program, "floor_color"), 1.0,1.0,1.0,1.0);

		gl->BindVertexArray(floor_va);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		gl->BindVertexArray(0);

		x+=-dz*std::sin(vy)+dx*std::cos(vy);
		z+=dz*std::cos(vy)+dx*std::sin(vy);
		vy+=dvy;
		rx+=0.1;
		ry+=0.1;
		rz+=0.1;
	}

	void keydown(const SDL_KeyboardEvent &ev) override{
		if(ev.keysym.sym=='w') dz=0.1;
		if(ev.keysym.sym=='s') dz=-0.1;
		if(ev.keysym.sym=='a') dx=-0.1;
		if(ev.keysym.sym=='d') dx=0.1;
		if(ev.keysym.sym=='q') dvy=0.003;
		if(ev.keysym.sym=='e') dvy=-0.003;
	}

	void keyup(const SDL_KeyboardEvent &ev)	override{
		if(ev.keysym.sym=='w') dz=0;
		if(ev.keysym.sym=='s') dz=0;
		if(ev.keysym.sym=='a') dx=0;
		if(ev.keysym.sym=='d') dx=0;
		if(ev.keysym.sym=='q') dvy=0;
		if(ev.keysym.sym=='e') dvy=0;
	}

	void gl_init() override{
		std::cerr<<glGetString(GL_VENDOR)<<std::endl;
		glEnable(GL_DEPTH_TEST);

		cube_program=gfw::make_program(gl, {
			gfw::make_shader(gl, GL_VERTEX_SHADER, "cube-vertex.glsl"),
			gfw::make_shader(gl, GL_FRAGMENT_SHADER, "cube-fragment.glsl"),
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

		struct ModelPoint{
			gfw::Vec<GLfloat,3> pos;
			gfw::Vec<GLubyte,3> color;
		};

		constexpr size_t n=8;
		ModelPoint cube_model_data[n]={
/*			{{-1,-1,-1}, {63,63,63}},
			{{1,-1,-1}, {191,63,63}},
			{{-1,1,-1}, {63,191,63}},
			{{1,1,-1}, {191,191,63}},
			{{-1,-1,1}, {63,63,191}},
			{{1,-1,1}, {191,63,191}},
			{{-1,1,1}, {63,191,191}},
			{{1,1,1}, {191,191,191}},*/
			{{-1,-1,-1}, {255,0,255}},
			{{1,-1,-1}, {0,255,0}},
			{{-1,1,-1}, {0,0,255}},
			{{1,1,-1}, {255,255,0}},
			{{-1,-1,1}, {255,0,0}},
			{{1,-1,1}, {0,255,255}},
			{{-1,1,1}, {128,128,128}},
			{{1,1,1}, {128,128,128}}
		};

		gl->BindVertexArray(cube_va);

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_model);
		gl->BufferData(GL_ARRAY_BUFFER, n*sizeof(ModelPoint), cube_model_data, GL_STATIC_READ);

		gl->EnableVertexAttribArray(0);
		gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelPoint), reinterpret_cast<const void*>(offsetof(ModelPoint, pos)));

		gl->EnableVertexAttribArray(1);
		gl->VertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ModelPoint), reinterpret_cast<const void*>(offsetof(ModelPoint, color)));

		gl->BindBuffer(GL_ARRAY_BUFFER, cube_instances);
		for(size_t i=0;i<4;i++){
			gl->EnableVertexAttribArray(2+i);
			gl->VertexAttribPointer(2+i, 4, GL_FLOAT, GL_FALSE, sizeof(CubeData), reinterpret_cast<const void*>(i*4*sizeof(GLfloat)));
			gl->VertexAttribDivisor(2+i, 1);
		}

		gl->BindVertexArray(floor_va);

		gfw::Vec<GLfloat,3> floor_model_data[]={
			{-100,-8,0},
			{100,-8,0},
			{-100,-8,100},
			{100,-8,100},
		};
		gl->BindBuffer(GL_ARRAY_BUFFER, floor_model);
		gl->BufferData(GL_ARRAY_BUFFER, 4*sizeof(gfw::Vec<GLfloat,3>), floor_model_data, GL_STATIC_READ);
		gl->EnableVertexAttribArray(0);
		gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		gl->BindBuffer(GL_ARRAY_BUFFER, 0);
		gl->BindVertexArray(0);

		if(glGetError()){
			std::cerr<<"bind: GL error\n";
		}
	}

	void gl_deinit() override{
		gl->DeleteBuffers(1, &cube_model);
		gl->DeleteBuffers(1, &cube_instances);
		gl->DeleteBuffers(1, &floor_model);
		gl->DeleteVertexArrays(1, &cube_va);
		gl->DeleteVertexArrays(1, &floor_va);
		gl->DeleteProgram(cube_program);
		gl->DeleteProgram(floor_program);
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
