#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "hud.h"

namespace{
    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000 / FPS;

    int frameCount = 0;
    float fps = 0.0f;
    Uint64 lastFpsUpdateTime = 0;
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

    Uint8 menuIndex = 0;

    Uint64 LAST_UPDATE_TIME = SDL_GetTicks64();

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

        if(input.wasKeyPressed(SDL_SCANCODE_S) && menuIndex == 0) menuIndex = 1; // singleplayer
        if(input.wasKeyPressed(SDL_SCANCODE_M) && menuIndex == 0) menuIndex = 2; // multiplayer
        if(input.wasKeyPressed(SDL_SCANCODE_O) && menuIndex == 0) menuIndex = 3; // options
        if(input.wasKeyPressed(SDL_SCANCODE_Q)) return; // quit add the menuindex condition later
        if(input.wasKeyPressed(SDL_SCANCODE_S) && menuIndex == 3) menuIndex = 4; // frame info


        const Uint64 CURRENT_TIME_MS = SDL_GetTicks64();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        frameCount++;
        if (CURRENT_TIME_MS - lastFpsUpdateTime >= 1000) {
            fps = frameCount / ((CURRENT_TIME_MS - lastFpsUpdateTime) / 1000.0f);
            frameCount = 0;
            lastFpsUpdateTime = CURRENT_TIME_MS;
        }

        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), this->_graphics);
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(this->_graphics, hud, menuIndex, fps, ELAPSED_TIME_MS);
    }
}

void Game::draw(Graphics &p_graphics, Hud p_hud, Uint8 p_menuIndex, float p_fps, int p_elapsedTime){

    SDL_Color bgColor = {0, 0, 0, 255};
    SDL_SetRenderDrawColor(this->_graphics.getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    p_graphics.clear();

    p_hud.draw(p_menuIndex, p_fps, p_elapsedTime);

    p_graphics.flip();
}

void Game::update(float p_elapsedTime, Graphics &p_graphics){
    //where the "game" will update status
    // player pos too
    // anda the hud too
}