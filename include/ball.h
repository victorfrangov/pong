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
    
    void handleBorderCollisions();

    void reverseDirectionX();

    void reverseDirectionY();

    // void setPosition(int p_x, int p_y);

    /**
     * @brief Gets the x-coordinate of the ball.
     * 
     * @return float: The x-coordinate.
     */
    // inline float getX() const { return this->_x; }

    /**
     * @brief Gets the y-coordinate of the ball.
     * 
     * @return float: The y-coordinate.
     */
    // inline float getY() const { return this->_y; }

    // inline void setLost() { this->_hasLost = true; }

    inline bool getLostStatus() const { return this->_hasLost; }
private:
    float _dx, _dy; // Velocity of the ball

    bool _hasLost;
};

#endif // BALL_H