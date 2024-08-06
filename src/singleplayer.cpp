#include "singleplayer.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Player* p_player, Hud &p_hud) :
        _player(*p_player),
        _hud(p_hud),
        _collisionTimer(0.0f),
        _ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / (rand() % 7 + 1)))
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

    if(this->_collisionTimer > 0.0f){
        this->_collisionTimer -= p_elapsedTime;
    }
    
    this->handlePlayerBallCollision();

    if(this->_ball.getLostStatus()){
        this->_player.setLost();
    }
}

bool Singleplayer::checkPlayerBallCollision(){
    const Rectangle ballRect = this->_ball.getBoundingBox();
    const Rectangle playerRect = this->_player.getBoundingBox();
    return ballRect.collidesWith(playerRect);
}

void Singleplayer::handlePlayerBallCollision(){
    if(this->_collisionTimer <= 0 && this->checkPlayerBallCollision()){
        const Rectangle ballRect = this->_ball.getBoundingBox();
        const Rectangle playerRect = this->_player.getBoundingBox();

        this->_player.gainPoint();
        sides::Side collisionSide = this->_player.getCollisionSide(ballRect);

        if(collisionSide == sides::LEFT || collisionSide == sides::RIGHT)
            this->_ball.reverseDirectionX();
        else if(collisionSide == sides::TOP || collisionSide == sides::BOTTOM)
            this->_ball.reverseDirectionY();

        this->_collisionTimer = COLLISION_COOLDOWN_TIME;
    }
}