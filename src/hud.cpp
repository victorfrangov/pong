#include <iostream>
#include <vector>

#include "hud.h"
#include "graphics.h"
#include "globals.h"

Hud::Hud(Graphics &p_graphics) :
        _graphics(p_graphics),
        _font(nullptr),
        _color({255, 255, 255, 255})
        {
            if(TTF_Init() != 0){
                std::cerr << "TTF_Init Error: " << TTF_GetError() << '\n';
                return;
            }

            _font = TTF_OpenFont("res/fonts/KenneyPixel.ttf", 56);
            if(!this->_font)
                std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << '\n';
        }

Hud::~Hud(){
}

void Hud::renderText(const char* p_text, int p_x, int p_y, int p_texW, int p_texH){
    if(!this->_font){
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(this->_font, p_text, this->_color);
    if(!surface){
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << '\n';
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_graphics.getRenderer(), surface);
    if(!texture){
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << '\n';
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = { p_x, p_y, p_texW, p_texH };

    this->_graphics.blitSurface(texture, NULL, &dst);

    freeMemory(texture, surface);
}

void Hud::freeMemory(SDL_Texture* p_texture, SDL_Surface* p_surface){
    SDL_DestroyTexture(p_texture);
    SDL_FreeSurface(p_surface);
}

void Hud::renderMenu(){
    std::vector<MenuItem> menuItems = {
        {"PONG", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 4)},
        {"M : Menu", Vector2f(globals::SCREEN_WIDTH / 3, globals::SCREEN_HEIGHT / 2)}
    };

    for(const auto& item : menuItems){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text, &titleTexW, &titleTexH);
 
        this->renderText(item.text, (globals::SCREEN_WIDTH / 2) - (titleTexW / 2),
            (globals::SCREEN_HEIGHT / 4) - (titleTexH), titleTexW, titleTexH);
    }
}