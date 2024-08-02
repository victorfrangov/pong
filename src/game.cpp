#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "hud.h"
#include "singleplayer.h"
#include "player.h"

namespace{
    const int FPS_TARGET = 60;
    const int MAX_FRAME_TIME = 1000 / FPS_TARGET;

    unsigned int frameCount = 0;
    float currentFPS = 0.0f;
}

Game::Game() : 
    _graphics(),
    _hud(_graphics),
    _singleplayer(nullptr),
    _player(nullptr),
    _isRunning(true),
    _menu()
    {
    this->gameLoop();
    }

Game::~Game(){
    if(this->_singleplayer != nullptr){
        delete this->_singleplayer;
        this->_singleplayer = nullptr;
    }

    if(this->_player != nullptr){
        delete this->_player;
        this->_player = nullptr;
    }
}

void Game::gameLoop() {
    Input input;
    Uint64 lastUpdateTime = SDL_GetTicks64();
    Uint64 lastFpsUpdateTime = lastUpdateTime;

    while (this->_isRunning) {
        input.beginNewFrame();
        this->handleInput(input);

        const Uint64 currentTimeMs = SDL_GetTicks64();
        int elapsedTimeMs = currentTimeMs - lastUpdateTime;

        frameCount++;
        if (currentTimeMs - lastFpsUpdateTime >= 1000) {
            currentFPS = frameCount / ((currentTimeMs - lastFpsUpdateTime) / 1000.0f);
            frameCount = 0;
            lastFpsUpdateTime = currentTimeMs;
        }

        this->update(std::min(elapsedTimeMs, MAX_FRAME_TIME));
        lastUpdateTime = currentTimeMs;

        this->draw(currentFPS, elapsedTimeMs);

        // Frame rate limiting
        Uint64 frameEndTime = SDL_GetTicks64();
        int frameDuration = frameEndTime - currentTimeMs;
        if (frameDuration < MAX_FRAME_TIME) {
            SDL_Delay(MAX_FRAME_TIME - frameDuration);
        }
    }
}

void Game::draw(float p_currentFPS, int p_elapsedTime){
    this->_graphics.clear();

    this->_hud.draw(this->_menu, p_currentFPS, p_elapsedTime);

    if(this->_singleplayer != nullptr)
        this->_singleplayer->draw(this->_graphics);

    this->_graphics.flip();
}

void Game::update(float p_elapsedTime){
    if(this->_singleplayer != nullptr)
        this->_singleplayer->update(p_elapsedTime);

    if(this->_player != nullptr){
        if(this->_player->getLostStatus())
            this->_menu = LOSE; // delete sp and player instances unless you have a play again button
    }
}

void Game::handleInput(Input &p_input) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            p_input.keyDownEvent(e);
        } else if (e.type == SDL_KEYUP) {
            p_input.keyUpEvent(e);
        } else if (e.type == SDL_QUIT) {
            this->_isRunning = false;
            return;
        }
    }

    if(p_input.wasKeyPressed(SDL_SCANCODE_S) && this->_menu == MAINMENU){ this->_hud.setOptionIndex(1); this->_menu = SPMENU; }

    if (p_input.wasKeyPressed(SDL_SCANCODE_UP) && this->_menu != SPGAME) { // must chcek that you are not in a game or else will crash
        this->_hud.handleArrowInput(SDL_SCANCODE_UP);
    } else if (p_input.wasKeyPressed(SDL_SCANCODE_DOWN) && this->_menu != SPGAME) {
        this->_hud.handleArrowInput(SDL_SCANCODE_DOWN);
    } else if (p_input.wasKeyPressed(SDL_SCANCODE_RIGHT) && this->_menu != SPGAME) {
        this->_hud.handleArrowInput(SDL_SCANCODE_RIGHT);
    } else if (p_input.wasKeyPressed(SDL_SCANCODE_LEFT) && this->_menu != SPGAME) {
        this->_hud.handleArrowInput(SDL_SCANCODE_LEFT);
    }

    if(p_input.wasKeyPressed(SDL_SCANCODE_P) && this->_menu == SPMENU){
        if(this->_singleplayer == nullptr && this->_player == nullptr){
            this->_menu = SPGAME;
            this->_player = new Player(this->_graphics, Vector2f(100, 100));
            this->_singleplayer = new Singleplayer(this->_graphics, this->_player, this->_hud); // will have to pass in the variables for speed/size before it gets init
        }
    }

    if (p_input.wasKeyPressed(SDL_SCANCODE_M) && this->_menu == MAINMENU) { this->_menu = MPMENU; this->_hud.setOptionIndex(1); } // multiplayer
    if (p_input.wasKeyPressed(SDL_SCANCODE_O) && this->_menu == MAINMENU) { this->_menu = OPTIONS; this->_hud.setOptionIndex(1); }  // options
    if (p_input.wasKeyPressed(SDL_SCANCODE_Q) && this->_menu == MAINMENU) { this->_isRunning = false; return; } // quit
    if (p_input.wasKeyPressed(SDL_SCANCODE_S) && this->_menu == OPTIONS) this->_hud.toggleFps(); // frame info

    if (p_input.wasKeyPressed(SDL_SCANCODE_B) && this->_menu != MAINMENU){
        this->_hud.setOptionIndex(1);
        this->_menu = MAINMENU;
        if (this->_singleplayer != nullptr) { // add checks for when will have multiplayer
            delete this->_singleplayer;
            this->_singleplayer = nullptr;
        }
        if (this->_player != nullptr) {
            delete this->_player;
            this->_player = nullptr;
        }
    }

    if(p_input.isKeyHeld(SDL_SCANCODE_W) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->moveUp();
    if(p_input.wasKeyReleased(SDL_SCANCODE_W) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->stopMoving();
    if(p_input.isKeyHeld(SDL_SCANCODE_S) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->moveDown();
    if(p_input.wasKeyReleased(SDL_SCANCODE_S) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->stopMoving();
}