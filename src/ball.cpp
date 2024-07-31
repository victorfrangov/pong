#include "ball.h"
#include <iostream>

Ball::Ball(Graphics &p_graphics, Vector2f p_spawnPoint, Hud &p_hud) :
        Sprite(p_graphics, 0, 0, 10, 10, p_spawnPoint),
        _dx(0.15f), // make this use params to be able to modify where the ball will start going to every round
        _dy(0.15f),
        _hud(p_hud),
        _hasLost(false)
        {
        }

void Ball::draw(Graphics &p_graphics) {
    Sprite::draw(p_graphics, Vector2f(this->_x, this->_y));
}

void Ball::update(float p_elapsedTime) {
    this->_x += this->_dx * p_elapsedTime;
    this->_y += this->_dy * p_elapsedTime;
    
    Sprite::update();
    this->handleBorderCollisions();
}

void Ball::handleBorderCollisions() {
    const Rectangle rect = Sprite::getBoundingBox();
    if (rect.getBottom() >= globals::SCREEN_HEIGHT) {
        this->_dy = -this->_dy;
        this->_y = globals::SCREEN_HEIGHT - rect.getHeight();
    } else if (rect.getTop() <= 0) {
        this->_dy = -this->_dy;
        this->_y = 0;
    } else if (rect.getLeft() <= 0) {
        // this->setLost(); removed for testing
        this->_dx = -this->_dx;
        this->_x = 0;
    } else if (rect.getRight() >= globals::SCREEN_WIDTH) {
        this->_dx = -this->_dx;
        this->_x = globals::SCREEN_WIDTH - rect.getWidth();
    }
}

void Ball::reverseDirectionX(){
    this->_dx = -this->_dx;
}

void Ball::reverseDirectionY(){
    this->_dy = -this->_dy;
}

void Ball::setPosition(int p_x, int p_y){
    this->_x = p_x;
    this->_y = p_y;
}