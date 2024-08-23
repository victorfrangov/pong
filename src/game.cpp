#include <SDL3/SDL.h>
#include <iostream>

#include "game.h"
#include "input.h"
#include "hud.h"
#include "singleplayer.h"

namespace{
    const int FPS_TARGET = 60;
    const int MAX_FRAME_TIME = 1000 / FPS_TARGET;

    unsigned int frameCount = 0;
    float currentFPS = 0.0f;
}

bool Game::_isRunning = true;

Game::Game() : 
    _graphics(),
    _hud(_graphics),
    _singleplayer(nullptr),
    _player(nullptr),
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
    Uint64 lastUpdateTime = SDL_GetTicks();
    Uint64 lastFpsUpdateTime = lastUpdateTime;

    while (this->_isRunning) {
        input.beginNewFrame();
        this->handleInput(input);

        const Uint64 currentTimeMs = SDL_GetTicks();
        Uint64 elapsedTimeMs = currentTimeMs - lastUpdateTime;

        frameCount++;
        if (currentTimeMs - lastFpsUpdateTime >= 1000) {
            currentFPS = frameCount / ((currentTimeMs - lastFpsUpdateTime) / 1000.0f);
            frameCount = 0;
            lastFpsUpdateTime = currentTimeMs;
        }

        this->update(std::min(static_cast<int>(elapsedTimeMs), MAX_FRAME_TIME));
        lastUpdateTime = currentTimeMs;

        this->draw(currentFPS, elapsedTimeMs);

        // Frame rate limiting
        Uint64 frameEndTime = SDL_GetTicks();
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
        if (e.type == SDL_EVENT_KEY_DOWN) {
            p_input.keyDownEvent(e);
        } else if (e.type == SDL_EVENT_KEY_UP) {
            p_input.keyUpEvent(e);
        } else if (e.type == SDL_EVENT_QUIT) {
            this->_isRunning = false;
            return;
        }
    }

    auto handleArrowKeys = [this, &p_input]() {
        if (p_input.wasKeyPressed(SDL_SCANCODE_UP) && this->_menu != SPGAME && this->_menu != MPGAME) this->_hud.handleKeyInput(SDL_SCANCODE_UP);
        if (p_input.wasKeyPressed(SDL_SCANCODE_DOWN) && this->_menu != SPGAME && this->_menu != MPGAME) this->_hud.handleKeyInput(SDL_SCANCODE_DOWN);
        if (p_input.wasKeyPressed(SDL_SCANCODE_RIGHT) && this->_menu != SPGAME && this->_menu != MPGAME) this->_hud.handleKeyInput(SDL_SCANCODE_RIGHT);
        if (p_input.wasKeyPressed(SDL_SCANCODE_LEFT) && this->_menu != SPGAME && this->_menu != MPGAME) this->_hud.handleKeyInput(SDL_SCANCODE_LEFT);

        if(p_input.isKeyHeld(SDL_SCANCODE_UP) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->moveUp();
        if(p_input.wasKeyReleased(SDL_SCANCODE_UP) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->stopMoving();
        if(p_input.isKeyHeld(SDL_SCANCODE_DOWN) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->moveDown();
        if(p_input.wasKeyReleased(SDL_SCANCODE_DOWN) && this->_menu == SPGAME && this->_singleplayer != nullptr && this->_player != nullptr) this->_player->stopMoving();
    };

    auto handleMenuSelection = [this, &p_input]() {
        auto lambdaStartSPGame = [this]() {
            this->_menu = SPGAME;
            this->_player = new Player(this->_graphics, Vector2f(100, 100));
            this->_singleplayer = new Singleplayer(this->_graphics, this->_player, this->_hud); // will have to pass in the variables for speed/size before it gets init
            this->_hud.setOptionIndex(1);
        };
        
        if(p_input.wasKeyPressed(SDL_SCANCODE_ESCAPE) && this->_menu == SPGAME) { this->_menu = MAINMENU; this->_hud.setOptionIndex(1); }

        if(p_input.wasKeyPressed(SDL_SCANCODE_RETURN)) {
            this->_hud.handleKeyInput(SDL_SCANCODE_RETURN, &this->_menu);

            if(this->_menu == SPMENU && this->_hud.getOptionIndex() == 4 && this->_singleplayer == nullptr && this->_player == nullptr) lambdaStartSPGame();
            if(this->_menu == LOSE && this->_hud.getOptionIndex() == 1 && this->_singleplayer == nullptr && this->_player == nullptr) lambdaStartSPGame();
            
        }

        if(this->_menu != SPGAME && this->_menu != MPGAME){
            if (this->_singleplayer != nullptr) { // add checks for when will have multiplayer
                delete this->_singleplayer;
                this->_singleplayer = nullptr;
            }
            if (this->_player != nullptr) {
                delete this->_player;
                this->_player = nullptr;
            }
        }
    };

    handleArrowKeys();
    handleMenuSelection();
}