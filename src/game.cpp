#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "hud.h"

namespace{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() : _graphics() {
    this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
    Input input;
    SDL_Event e;
    Hud hud(this->_graphics);

    int LAST_UPDATE_TIME = SDL_GetTicks64();

    while(true){
        input.beginNewFrame();

        if(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN){
                if(e.key.repeat == 0){
                    input.keyDownEvent(e);
                }
            } else if(e.type == SDL_KEYUP){
                input.keyUpEvent(e);
            } else if(e.type == SDL_QUIT){
                return;
            }
        }
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            return;
        }

        const int CURRENT_TIME_MS = SDL_GetTicks64();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), this->_graphics);
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(this->_graphics, hud);
    }
}

void Game::draw(Graphics &p_graphics, Hud p_hud){

    SDL_Color bgColor = {0, 0, 0, 255};
    SDL_SetRenderDrawColor(this->_graphics.getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    p_graphics.clear();

    p_hud.renderMenu();

    SDL_Color lineColor = {0, 0, 255, 255};
    SDL_SetRenderDrawColor(this->_graphics.getRenderer(), lineColor.r, lineColor.g, lineColor.b, lineColor.a);
    SDL_RenderDrawLine(this->_graphics.getRenderer(), 320, 0, 320, 480);
    SDL_RenderDrawLine(this->_graphics.getRenderer(), 0, 111, 640, 111);

    p_graphics.flip();
}

void Game::update(float p_elapsedTime, Graphics &p_graphics){

}