#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "graphics.h"
#include "globals.h"
#include "pongIcon.h"

Graphics::Graphics(){
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl") == SDL_TRUE) {
        SDL_Log("opengl was set");
    }

    SDL_CreateWindowAndRenderer("PONG", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
    SDL_SetRenderLogicalPresentation(this->_renderer, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX, SDL_SCALEMODE_NEAREST);

    SDL_IOStream* io = SDL_IOFromMem(pong_png, pong_png_len);
    if(!io){
        printf("SDL_IOFromMem Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Surface* surface = IMG_Load_IO(io, 1);
    if(!surface){
        printf("IMG_Load_IO Error: %s\n", IMG_GetError());
        return;
    }
    SDL_SetWindowIcon(this->_window, surface);
}

Graphics::~Graphics(){
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

// SDL_Surface* Graphics::loadImage(const std::string &p_filePath){
//     if(this->_spriteSheets.count(p_filePath) == 0){
//         this->_spriteSheets[p_filePath]= IMG_Load(p_filePath.c_str());
//     }
//     return this->_spriteSheets[p_filePath];
// }

void Graphics::blitSurface(SDL_Texture* p_texture, SDL_FRect* p_src, SDL_FRect* p_dst){
    SDL_RenderTexture(this->_renderer, p_texture, p_src, p_dst);
}

void Graphics::flip(){
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear(){
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const{
    return this->_renderer; 
}

void Graphics::toggleFullScreen(){
    SDL_SetWindowFullscreen(this->_window, this->getWindowStatus() ? SDL_FALSE : SDL_TRUE);
}

bool Graphics::getWindowStatus(){
    return SDL_GetWindowFlags(this->_window) & SDL_WINDOW_FULLSCREEN;
}