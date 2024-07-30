#include "ball.h"

/**
 * @brief Constructs a Ball with graphics context, and initial position.
 * 
 * @param p_graphics Graphics context to draw the ball.
 * @param p_spawnPoint Initial position of the ball.
 */
Ball::Ball(Graphics &p_graphics, Vector2f p_spawnPoint) :
        _x(p_spawnPoint.x),
        _y(p_spawnPoint.y),
        _dx(0),
        _dy(0),
        Sprite(p_graphics, 0, 0, 10, 10, p_spawnPoint)
        {
        }

/**
 * @brief Draws the ball on the screen.
 * 
 * @param p_graphics Graphics context to draw the ball.
 */
void Ball::draw(Graphics &p_graphics) {
    Sprite::draw(p_graphics, Vector2f(this->_x, this->_y));
}

/**
 * @brief Updates the ball's position and animations.
 * 
 * @param p_elapsedTime Time elapsed since the last update.
 */
void Ball::update(float p_elapsedTime) {
    // Update the ball's position based on its velocity and elapsed time
    this->_x += this->_dx * p_elapsedTime;
    this->_y += this->_dy * p_elapsedTime;
    // Implement other update logic here
}

/**
 * @brief Handles collisions with tiles.
 * 
 * @param p_others A vector of rectangles representing the tiles.
 */
void Ball::handleCollisions(std::vector<Rectangle> &p_others) {
    // Implement collision handling logic here
}