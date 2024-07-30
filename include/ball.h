#ifndef BALL_H
#define BALL_H

#include "graphics.h"
#include "globals.h"
#include "rectangle.h"
#include "sprite.h"
#include <vector>

/**
 * @brief Represents a Ball in the game.
 */
class Ball : public Sprite{
public:
    /**
     * @brief Constructs a Ball with graphics context, and initial position.
     * 
     * @param p_graphics Graphics context to draw the ball.
     * @param p_spawnPoint Initial position of the ball.
     */
    Ball(Graphics &p_graphics, Vector2f p_spawnPoint);

    /**
     * @brief Draws the ball on the screen.
     * 
     * @param p_graphics Graphics context to draw the ball.
     */
    void draw(Graphics &p_graphics);

    /**
     * @brief Updates the ball's position and animations.
     * 
     * @param p_elapsedTime Time elapsed since the last update.
     */
    void update(float p_elapsedTime);

    /**
     * @brief Handles collisions with tiles.
     * 
     * @param p_others A vector of rectangles representing the tiles.
     */
    void handleTileCollisions(std::vector<Rectangle> &p_others);

    /**
     * @brief Gets the x-coordinate of the ball.
     * 
     * @return float: The x-coordinate.
     */
    inline float getX() const { return this->_x; }

    /**
     * @brief Gets the y-coordinate of the ball.
     * 
     * @return float: The y-coordinate.
     */
    inline float getY() const { return this->_y; }

private:
    float _x, _y; // Position of the ball
    float _dx, _dy; // Velocity of the ball
    // Add other necessary private members here
};

#endif // BALL_H