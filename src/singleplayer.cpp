#include "singleplayer.h"
// #include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Player* p_player, Hud &p_hud) :
        _player(*p_player),
        _hud(&p_hud),
        _ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2))
        {
        }

void Singleplayer::draw(Graphics &p_graphics){
    this->_player.draw(p_graphics);
    this->_ball.draw(p_graphics);
    this->_hud->renderPoints(&this->_player);
}

void Singleplayer::update(float p_elapsedTime){
    this->_player.update(p_elapsedTime);
}