#include <iostream>
#include <vector>

#include "hud.h"
#include "graphics.h"
#include "globals.h"
#include "KenneyPixel.h"

Hud::Hud(Graphics &p_graphics) :
        _graphics(p_graphics),
        _font(nullptr),
        _color({255, 255, 255, 255})
        {
            if(TTF_Init() != 0){
                std::cerr << "TTF_Init Error: " << TTF_GetError() << '\n';
                return;
            }

            SDL_RWops* rw = SDL_RWFromMem(KenneyPixel_ttf, KenneyPixel_ttf_len);
            if (!rw) {
                std::cerr << "SDL_RWFromMem Error: " << SDL_GetError() << '\n';
                return;
            }

            _font = TTF_OpenFontRW(rw, 1, 56);
            if(!_font) {
                std::cerr << "TTF_OpenFontRW Error: " << TTF_GetError() << '\n';
    }
        }

Hud::~Hud(){
}

void Hud::draw(Uint8 p_menuIndex, float p_fps, int p_elapsedTime){
    SDL_Color lineColor = {0, 0, 255, 255};
    this->renderFrameInfo(p_fps,  p_elapsedTime);
    switch (p_menuIndex){
        case 0:
            this->renderMenu();
            break;
        case 1: // singelaplyer
            //here will get called the singleplayer class, maybe will have to add member vars, single/multi
            break;
        case 2: //multiplayer
            break;
        case 3: // options
            this->renderOptions();
            break;
        default:
            break;
    }
}

void Hud::update(){

}

void Hud::renderText(std::string p_text, int p_x, int p_y, int p_texW, int p_texH){
    if(!this->_font){
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(this->_font, p_text.c_str(), this->_color);
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

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
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
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
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
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderFrameInfo(float p_fps, int p_elapsedTime){
    if(this->_showFPS){
        std::vector<HudItem> hudItem = {
            {"FPS: " + std::to_string(static_cast<int>(p_fps)), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)}
            };

        for(const auto& item : hudItem){
            int titleTexW = 0;
            int titleTexH = 0;
            TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
            this->renderText(item.text, 0, 0, titleTexW / 3, titleTexH / 3);
        }
    }
}

void Hud::toggleFps(){
    this->_showFPS = !this->_showFPS;
}