#include "player.h"

#include <iostream>

namespace player_constants{
    const float SPEED = 0.3f;
}

Player::Player(){}

Player::Player(Graphics &p_graphics, Vector2f p_spawnPoint):
    Sprite(p_graphics, 0, 0, 10, 65, p_spawnPoint),
        _points(0),
        _dy(0)
    {
    }

void Player::draw(Graphics &p_graphics){
    Sprite::draw(p_graphics, Vector2f(this->_x, this->_y));
}

void Player::stopMoving(){
    this->_dy = 0.0f;
}

void Player::update(float p_elapsedTime){
    this->_y += this->_dy * p_elapsedTime;
    Sprite::update();
    this->handleCollisions();
}

void Player::moveUp(){
    this->_dy = std::clamp(this->_dy - player_constants::SPEED, -player_constants::SPEED, player_constants::SPEED);
}

void Player::moveDown(){
    this->_dy = std::clamp(this->_dy + player_constants::SPEED, -player_constants::SPEED, player_constants::SPEED);
}

void Player::handleCollisions(){
    const Rectangle rect = Sprite::getBoundingBox();
    if (rect.getBottom() >= globals::SCREEN_HEIGHT) {
        this->_dy = 0;
        this->_y = globals::SCREEN_HEIGHT - rect.getHeight();
    } else if (rect.getTop() <= 0) {
        this->_dy = 0;
        this->_y = 0;
    }
}
