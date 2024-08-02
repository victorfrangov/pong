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
            this->_hudItem = {};

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
    this->renderFrameInfo(p_fps,  p_elapsedTime);
    switch (p_menu){
        case MAINMENU:
            this->renderMenu();
            break;
        case SPMENU:
            this->renderSPOptions();
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
    this->_hudItem = {
        {"PONG", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5), Dash::NODASH},
        {"S: SINGLEPLAYER", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.5), Dash::DASH},
        {"M: MULTIPLAYER", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.0), Dash::DASH},
        {"O: OPTIONS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.6667), Dash::DASH},
        {"Q: QUIT", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25), Dash::DASH}
    };
    this->renderHudItems();
}

void Hud::renderOptions(){
    this->_hudItem = {
        {"GAME OPTIONS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5), Dash::NODASH},
        {"S: SHOW FRAME INFO", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.5), Dash::DASH},
        {"F: FULLSCREEN TOGGLE", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.0), Dash::DASH},
        {"RESOLUTION : " + std::to_string(globals::SCREEN_WIDTH) + " / " + std::to_string(globals::SCREEN_HEIGHT), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.66667), Dash::DASH},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25), Dash::DASH}
    };
    this->renderHudItems();
}

void Hud::renderFrameInfo(float p_fps, int p_elapsedTime){
    if(this->_showFPS){
        this->_hudItem = {
            {"FPS: " + std::to_string(static_cast<int>(p_fps)), Vector2f(0, 0), Dash::NODASH, 3} // add a ping counter later
            };

        for(const HudItem& item : this->_hudItem){
            int titleTexW = 0;
            int titleTexH = 0;
            TTF_SizeUTF8(this->_font, item.text.c_str(), &titleTexW, &titleTexH);
            this->renderText(item.text, item.pos.x, item.pos.y, titleTexW / 3, titleTexH / 3);
        }
    }
}

void Hud::toggleFps(){
    this->_showFPS = !this->_showFPS;
}

void Hud::renderPoints(Player* p_player){
    this->_hudItem = {
        {std::to_string(p_player->getPoints()), Vector2f(globals::SCREEN_WIDTH / 4, globals::SCREEN_HEIGHT / 7), Dash::NODASH}
    };
    this->renderHudItems();
}

void Hud::renderLose(){
    this->_hudItem = {
        {"YOU LOSE!", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5), Dash::NODASH},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.25), Dash::DASH}
    };
    this->renderHudItems();
}

void Hud::renderSPOptions(){
    std::vector<float> ballSpeedOptions = {0.15f, 0.30f, 0.50f, 1.00f, 1.50f};
    std::vector<float> playerSpeedOptions = {0.20f, 0.60f, 1.50f, 2.30f,3.00f};
    std::vector<float> ballSizeOptions = {0.50f, 1.00f, 2.00f, 3.00f, 5.00f};

    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed << ballSpeedOptions[this->vectorIndex];

    this->_hudItem = {
        {"SINGLEPLAYER OPTIONS", Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 5), Dash::NODASH},
        {"BALL SPEED: " + stream.str(), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2.5), Dash::DASH},
        {"PLAYER SPEED: " + std::to_string(1000), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2), Dash::DASH},
        {"BALL SIZE: " + std::to_string(10), Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 1.666667), Dash::DASH},
        //add cooldown option?
        {"P: PLAY", Vector2f(globals::SCREEN_WIDTH / 3, globals::SCREEN_HEIGHT / 1.25), Dash::DASH},
        {"B: BACK", Vector2f(globals::SCREEN_WIDTH / 1.5, globals::SCREEN_HEIGHT / 1.25), Dash::DASH}        
    };
    this->renderHudItems();
}

void Hud::handleArrowInput(SDL_Scancode p_key) {
    do {
        switch (p_key){
        case SDL_SCANCODE_UP:
            _selectedOptionIndex = (_selectedOptionIndex - 1 + this->_hudItem.size()) % this->_hudItem.size();
            break;
        case SDL_SCANCODE_DOWN:
            _selectedOptionIndex = (_selectedOptionIndex + 1) % this->_hudItem.size();
            break;
        case SDL_SCANCODE_LEFT:
            //something
            break;
        case SDL_SCANCODE_RIGHT:
            //smth
            break;
        default:
            break;
        }
    } while (this->_hudItem[_selectedOptionIndex]._dash == Dash::NODASH);
}

void Hud::renderHudItems(){
    for (size_t i = 0; i < this->_hudItem.size(); ++i) {
        const HudItem& item = this->_hudItem[i];
        int titleTexW = 0;
        int titleTexH = 0;

        std::string displayText = item.text;
        if (i == _selectedOptionIndex && item._dash == Dash::DASH) {
            displayText = "- " + displayText;
        }

        TTF_SizeUTF8(this->_font, displayText.c_str(), &titleTexW, &titleTexH);

        int scaledTexW = titleTexW / item.sizeScale;
        int scaledTexH = titleTexH / item.sizeScale;
        this->renderText(displayText, item.pos.x - (scaledTexW / 2), item.pos.y - (scaledTexH / 2), scaledTexW, scaledTexH);
    }
}