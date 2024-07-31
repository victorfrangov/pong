#include "singleplayer.h"
// #include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Player* p_player, Hud &p_hud) :
        _player(*p_player),
        _hud(p_hud),
        _ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2), p_hud)
        {
        }

void Singleplayer::draw(Graphics &p_graphics){
    this->_player.draw(p_graphics);
    this->_ball.draw(p_graphics);
    this->_hud.renderPoints(&this->_player);
}

void Singleplayer::update(float p_elapsedTime){
    this->_ball.update(p_elapsedTime);
    this->_player.update(p_elapsedTime);
    
    this->handlePlayerBallCollision();
}

bool Singleplayer::checkPlayerBallCollision(){
    const Rectangle ballRect = this->_ball.getBoundingBox();
    const Rectangle playerRect = this->_player.getBoundingBox();
    return ballRect.collidesWith(playerRect);
}

// there is a weird bug where the ball will get stuck inside 
// the bar and circle around it and then get out
void Singleplayer::handlePlayerBallCollision(){
    if(this->checkPlayerBallCollision()){
        this->_player.gainPoint();
        const Rectangle ballRect = this->_ball.getBoundingBox();
        sides::Side test = this->_player.getCollisionSide(ballRect);
        if(test == sides::LEFT || test == sides::RIGHT)
            this->_ball.reverseDirectionX();
        else if(test == sides::TOP || test == sides::BOTTOM)
            this->_ball.reverseDirectionY();
    }
}