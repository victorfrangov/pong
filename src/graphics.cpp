#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "globals.h"
#include "pongIcon.h"

Graphics::Graphics(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "PONG");

    SDL_RWops* rw = SDL_RWFromMem(pong_png, pong_png_len);
    if(!rw){
        printf("SDL_RWFromMem Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if(!surface){
        printf("IMG_Load_RW Error: %s\n", IMG_GetError());
        return;
    }
    SDL_SetWindowIcon(this->_window, surface);
}

Graphics::~Graphics(){
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &p_filePath){
    if(this->_spriteSheets.count(p_filePath) == 0){
        this->_spriteSheets[p_filePath]= IMG_Load(p_filePath.c_str());
    }
    return this->_spriteSheets[p_filePath];
}

void Graphics::blitSurface(SDL_Texture* p_texture, SDL_Rect* p_src, SDL_Rect* p_dst){
    SDL_RenderCopy(this->_renderer, p_texture, p_src, p_dst);
}

void Graphics::flip(){
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear(){
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const{
    return this->_renderer; 
}