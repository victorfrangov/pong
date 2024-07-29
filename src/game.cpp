#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "hud.h"

#include "sprite.h"

namespace{
    const int FPS_TARGET = 60;
    const int MAX_FRAME_TIME = 1000 / FPS_TARGET;

    int frameCount = 0;
    float currentFPS = 0.0f;
}

Game::Game() : _graphics(), _hud(_graphics) {
    this->gameLoop();
}

Game::~Game(){
}

void Game::gameLoop() {
    Input input;
    SDL_Event e;

    Uint8 menuIndex = 0;

    Uint64 LAST_UPDATE_TIME = SDL_GetTicks64();
    Uint64 lastFpsUpdateTime = LAST_UPDATE_TIME;

    while (true) {
        input.beginNewFrame();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.repeat == 0) {
                    input.keyDownEvent(e);
                }
            } else if (e.type == SDL_KEYUP) {
                input.keyUpEvent(e);
            } else if (e.type == SDL_QUIT) {
                return;
            }
        }

        if (input.wasKeyPressed(SDL_SCANCODE_S) && menuIndex == 0) menuIndex = 1; // singleplayer
        if (input.wasKeyPressed(SDL_SCANCODE_M) && menuIndex == 0) menuIndex = 2; // multiplayer
        if (input.wasKeyPressed(SDL_SCANCODE_O) && menuIndex == 0) menuIndex = 3; // options
        if (input.wasKeyPressed(SDL_SCANCODE_Q) && menuIndex == 0) return; // quit
        if (input.wasKeyPressed(SDL_SCANCODE_S) && menuIndex == 3) this->_hud.toggleFps(); // frame info
        if (input.wasKeyPressed(SDL_SCANCODE_B) && menuIndex != 0) menuIndex = 0; // go back

        const Uint64 CURRENT_TIME_MS = SDL_GetTicks64();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        frameCount++;
        if (CURRENT_TIME_MS - lastFpsUpdateTime >= 1000) {
            currentFPS = frameCount / ((CURRENT_TIME_MS - lastFpsUpdateTime) / 1000.0f);
            frameCount = 0;
            lastFpsUpdateTime = CURRENT_TIME_MS;
        }

        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), this->_graphics);
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(menuIndex, currentFPS, ELAPSED_TIME_MS);

        // Frame rate limiting
        Uint64 frameEndTime = SDL_GetTicks64();
        int frameDuration = frameEndTime - CURRENT_TIME_MS;
        if (frameDuration < MAX_FRAME_TIME) {
            SDL_Delay(MAX_FRAME_TIME - frameDuration);
        }
    }
}

void Game::draw(Uint8 p_menuIndex, float p_currentFPS, int p_elapsedTime){
    SDL_Color bgColor = {0, 0, 0, 255};
    SDL_SetRenderDrawColor(this->_graphics.getRenderer(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);

    this->_graphics.clear();

    this->_hud.draw(p_menuIndex, p_currentFPS, p_elapsedTime);

    // Sprite sprite(this->_graphics, "res/gfx/bar.png", 0, 0, 10, 75, 100, 100);

    this->_graphics.flip();
}

void Game::update(float p_elapsedTime, Graphics &p_graphics){
    //where the "game" will update status
    // player pos too
    // anda the hud too
}