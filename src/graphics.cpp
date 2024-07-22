#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics(){
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Cavestory");
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