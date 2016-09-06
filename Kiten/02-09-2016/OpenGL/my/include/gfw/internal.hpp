#pragma once
#include <stdexcept>
#include <iostream>

#define SDLi(func, ...) ({auto r=SDL_##func(__VA_ARGS__);if(r<0){throw std::runtime_error("SDL_" #func " at" __FILE__ ":" + std::to_string(__LINE__) + " : "+std::string(SDL_GetError()));}r;})
#define SDLp(func, ...) ({auto r=SDL_##func(__VA_ARGS__);if(!r){throw std::runtime_error("SDL_" #func " at" __FILE__ ":" + std::to_string(__LINE__) + " : "+std::string(SDL_GetError()));}r;})
