#include "gfw.hpp"
namespace gfw{

Screen::
Screen::~Screen(){}
void Screen::gl_init(){
	return;
}
void Screen::gl_deinit(){
}

void Screen::gl_attach(GLContext *ctx){
	if(ctx==gl) return;
	if(gl) gl_detach();
	gl=ctx;
	_gl_next=gl->screen;
	if(_gl_next) _gl_next->_gl_prev=this;
	gl->screen=this;
	gl_init();
}
void Screen::gl_detach(){
	if(!gl) return;
	gl_deinit();
	if(_gl_prev){
		assert(this!=gl->screen);
		_gl_prev->_gl_next=_gl_next;
	}else{
		assert(this==gl->screen);
		gl->screen=_gl_next;
	}
	if(_gl_next){
		_gl_next->_gl_prev=_gl_prev;
	}
	_gl_next=nullptr;
	_gl_prev=nullptr;
	gl=nullptr;
}

void Screen::keyup(const SDL_KeyboardEvent&){}
void Screen::keydown(const SDL_KeyboardEvent&){}

}
