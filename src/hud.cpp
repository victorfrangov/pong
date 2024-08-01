#include <iostream>
#include <vector>
#include <sstream> // Add this line

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

            this->_font = TTF_OpenFontRW(rw, 1, 56);
            if(!_font)
                std::cerr << "TTF_OpenFontRW Error: " << TTF_GetError() << '\n';
        }

Hud::~Hud(){
}

void Hud::draw(Menu p_menu, float p_fps, int p_elapsedTime){
    std::vector<float> ballSpeedOptions = {0.05f, 0.15f, 0.25f, 0.35f};
    SDL_Color lineColor = {0, 0, 255, 255};
    this->renderFrameInfo(p_fps,  p_elapsedTime);
    switch (p_menu){
        case MAINMENU:
            this->renderMenu();
            break;
        case SPMENU:
            this->renderSPOptions(ballSpeedOptions);
            break;
        case MPMENU:
            break;
        case OPTIONS:
            this->renderOptions();
            break;
        case LOSE:
            this->renderLose();
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

    for(const HudItem& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderOptions(){
    std::vector<HudItem> hudItem = {
        {"S: SHOW FRAME INFO", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25)}
    };

    for(const HudItem& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderFrameInfo(float p_fps, int p_elapsedTime){
    if(this->_showFPS){
        std::vector<HudItem> hudItem = {
            {"FPS: " + std::to_string(static_cast<int>(p_fps)), Vector2f(0, 0)} // add a ping counter later
            };

        for(const HudItem& item : hudItem){
            int titleTexW = 0;
            int titleTexH = 0;
            TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
            this->renderText(item.text, item.pos.x, item.pos.y, titleTexW / 3, titleTexH / 3);
        }
    }
}

void Hud::toggleFps(){
    this->_showFPS = !this->_showFPS;
}

void Hud::renderPoints(Player* p_player){
    std::vector<HudItem> hudItem = {
        {std::to_string(p_player->getPoints()), Vector2f(globals::SCREEN_WIDTH / 4, globals::SCREEN_HEIGHT / 7)}
    };

    for(const HudItem& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderLose(){
    std::vector<HudItem> hudItem = {
        {"YOU LOSE!", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25)}
    };

    for(const HudItem& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
        this->renderText(item.text, item.pos.x - (titleTexW / 2), item.pos.y - (titleTexH / 2), titleTexW, titleTexH);
    }
}

void Hud::renderSPOptions(std::vector<float> p_ballSpeedOptions){
    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed << p_ballSpeedOptions[1];

    std::vector<HudItem> hudItem = {
        {"SINGLEPLAYER OPTIONS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5)},
        {"CONTROL WITH ARROWS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 3.5), 2},
        {"BALL SPEED: " + stream.str(), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.5)},
        {"PLAYER SPEED: " + std::to_string(1000), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2)},
        {"BALL SIZE: " + std::to_string(10), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.666667)},
        {"P: PLAY / B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25)}
    };

    for(const HudItem& item : hudItem){
        int titleTexW = 0;
        int titleTexH = 0;
        TTF_SizeText(this->_font, item.text.c_str(), &titleTexW, &titleTexH);

        int scaledTexW = titleTexW / item.sizeScale;
        int scaledTexH = titleTexH / item.sizeScale;
        this->renderText(item.text, item.pos.x - (scaledTexW / 2), item.pos.y - (scaledTexH / 2), scaledTexW, scaledTexH);
    }
}