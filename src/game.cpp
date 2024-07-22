#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"

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

        this->draw(this->_graphics);
    }
}

void Game::draw(Graphics &p_graphics){
    p_graphics.clear();


    p_graphics.flip();
}

void Game::update(float p_elapsedTime, Graphics &p_graphics){

}