#include "gfw.hpp"
#include "gfw/internal.hpp"
#include <unordered_map>
namespace gfw{

struct RenderTimer: Timer{
	Window *w;

	RenderTimer(Window *w):Timer(Timer::Clock::time_point::min(),-100),w(w){}

	void callback() override{
		//Timer::Clock::time_point time_begin=Timer::Clock::now();
		w->_render();
		Timer::Clock::time_point time_end=Timer::Clock::now();

		arm(std::max(time()+w->frame_time, time_end));
	}
};

static std::unordered_map<Uint32, Window*> windows;
Window::Window(SDL_Window *native):sdl_window(native),gl(new GLContext(SDLp(GL_CreateContext, sdl_window))),screen(nullptr){
	frame_time=std::chrono::nanoseconds(16666667);
	render_timer=new RenderTimer(this);
	windows[SDL_GetWindowID(sdl_window)]=this;
}
Window::~Window(){
	delete render_timer;

	delete gl;

	windows.erase(SDL_GetWindowID(sdl_window));
	SDL_DestroyWindow(sdl_window);
}

void Window::_render(){
	SDLi(GL_MakeCurrent, sdl_window, gl->sdl_glctx);
	glClearColor(0,0,0,0);
	if(glGetError()){
		std::cerr<<"glClearColor: GL error\n";
	}
	int w, h;
	SDL_GetWindowSize(sdl_window, &w, &h);
	if(screen){
		glViewport(0,0,w,h);
		if(glGetError()){
			std::cerr<<"glViewport: GL error\n";
		}
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		if(glGetError()){
			std::cerr<<"glClear: GL error\n";
		}
		screen->gl_attach(gl);
		screen->render(w, h);
		if(glGetError()){
			std::cerr<<"Screen::render: GL error\n";
		}
	}
	SDL_GL_SwapWindow(sdl_window);
	SDLi(GL_MakeCurrent, nullptr, nullptr);
}

Screen *Window::attach(Screen *s){
	Screen *so=screen;
	screen=s;
	return so;
}


GLContext::GLContext(SDL_GLContext native):sdl_glctx(native){
	#define X(f,t) f=(t)SDL_GL_GetProcAddress("gl" #f);
	#include "gfw/gl.x"
}
GLContext::~GLContext(){
	while(screen){
		screen->gl_detach();
	}
	SDL_GL_DeleteContext(sdl_glctx);
	return;
}

void Window::_dispatch_window(const SDL_WindowEvent &ev){
	auto it=windows.find(ev.windowID);
	if(it!=windows.end()) it->second->_event_window(ev);
}

void Window::_event_window(const SDL_WindowEvent &ev){
	(void)ev;
}

void Window::_dispatch_keyup(const SDL_KeyboardEvent &ev){
	auto it=windows.find(ev.windowID);
	if(it!=windows.end()) it->second->_event_keyup(ev);
}

void Window::_event_keyup(const SDL_KeyboardEvent &ev){
	if(screen) screen->keyup(ev);
}

void Window::_dispatch_keydown(const SDL_KeyboardEvent &ev){
	auto it=windows.find(ev.windowID);
	if(it!=windows.end()) it->second->_event_keydown(ev);
}

void Window::_event_keydown(const SDL_KeyboardEvent &ev){
	if(screen) screen->keydown(ev);
}

}
