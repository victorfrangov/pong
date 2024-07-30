#include "ball.h"
#include <iostream>

Ball::Ball(Graphics &p_graphics, Vector2f p_spawnPoint) :
        Sprite(p_graphics, 0, 0, 10, 10, p_spawnPoint),
        _x(p_spawnPoint.x),
        _y(p_spawnPoint.y),
        _dx(0.15f), // make this use params to be able to modify where the ball will start going to every round
        _dy(0.15f)
        {
        }

void Ball::draw(Graphics &p_graphics) {
    Sprite::draw(p_graphics, Vector2f(this->_x, this->_y));
}

void Ball::update(float p_elapsedTime) {
    this->_x += this->_dx * p_elapsedTime;
    this->_y += this->_dy * p_elapsedTime;
    
    Sprite::update();
    this->handleCollisions();
}

void Ball::handleCollisions() {
    const Rectangle rect = Sprite::getBoundingBox();
    // std::cout << rect.getBottom() << std::endl;
    if (rect.getBottom() >= globals::SCREEN_HEIGHT) {
        this->_dx = -this->_dx;
        this->_dy = -this->_dy;
        this->_y = globals::SCREEN_HEIGHT - rect.getHeight();
    } else if (rect.getTop() <= 0) {
        this->_dx = -this->_dx;
        this->_dy = -this->_dy;
        this->_y = 0;
    }
}