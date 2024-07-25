#include <iostream>

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

            _font = TTF_OpenFont("res/fonts/KenneyPixel.ttf", 24);
            if(!this->_font)
                std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << '\n';
        }

Hud::~Hud(){
}

void Hud::renderText(const char* p_text, int p_x, int p_y){
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

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);


    SDL_Rect dst = { p_x, p_y, texW, texH };

    this->_graphics.blitSurface(texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

//add method to encapsulate the rendertext method, for each menu

void Hud::renderMenu(){
    int texW = 0;
    int texH = 0;
    const char* menu = "PONG";

    TTF_SizeText(this->_font, menu, &texW, &texH);

    this->renderText(menu, (globals::SCREEN_WIDTH / 2) - (texW / 2), (globals::SCREEN_HEIGHT / 4) - (texH / 2));

    // std::cout << (globals::SCREEN_WIDTH / 2) - (texW / 2) << '\n'; prints 302
}