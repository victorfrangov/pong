#include "singleplayer.h"
// #include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Player* p_player) :
        _points(0),
        _player(*p_player),
        _ball(p_graphics, Vector2f(320, 280))
        {
        }

void Singleplayer::draw(Graphics &p_graphics){
    this->_player.draw(p_graphics);
    this->_ball.draw(p_graphics);
}

void Singleplayer::update(float p_elapsedTime){

}