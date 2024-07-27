#include <iostream>
#include <vector>
#include <filesystem>

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

            std::string currentPath = std::filesystem::current_path().string();
            std::cout << "Current working directory: " << currentPath << std::endl;

            #ifdef _WIN32
            _font = TTF_OpenFont("/res/fonts/KenneyPixel.ttf", 56);
            #else
            _font = TTF_OpenFont("../res/fonts/KenneyPixel.ttf", 56);
            #endif
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
    std::vector<HudItem> hudItem = {
        {"PONG", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)},
        {"S: SINGLEPLAYER", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.5)},
        {"M: MULTIPLAYER", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.0)},
        {"O: OPTIONS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.6667)},
        {"Q: QUIT", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25)}
    };

    for(const auto& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text, &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderOptions(){
    std::vector<HudItem> hudItem = {
        {"S: SHOW FRAME INFO", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2)}
    };

    for(const auto& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text, &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}