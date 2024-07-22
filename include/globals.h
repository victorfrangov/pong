/**
 * @file globals.h
 * @brief This file contains global constants and a structure used throughout the application.
 */

#ifndef GLOBALS
#define GLOBALS

/**
 * @namespace globals
 * @brief Namespace containing global constants.
 */
namespace globals{
    const int SCREEN_WIDTH = 640; ///< Width of the screen in pixels.
    const int SCREEN_HEIGHT = 480; ///< Height of the screen in pixels.

    const int SPRITE_SCALE = 2.0f; ///< Scale factor for sprites.
}

namespace sides{
    enum Side{
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE,
    };

    const inline Side getOppositeSide(Side p_side){
        return
                p_side == TOP ? BOTTOM :
                p_side == BOTTOM ? TOP :
                p_side == LEFT ? RIGHT :
                p_side == RIGHT ? LEFT :
                NONE;
    }
}

/**
 * @enum Direction
 * @brief Enumerates possible movement directions.
 * 
 * This enum is used to specify the direction of movement or facing of game entities.
 */
enum Direction{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/**
 * @struct Vector2f
 * @brief Represents a 2D vector with floating point coordinates.
 * 
 * This structure is used to represent positions and dimensions in 2D space.
 */
struct Vector2f{
    int x, y; ///< X and Y coordinates of the vector.

    /**
     * @brief Default constructor. Initializes x and y to 0.
     */
    Vector2f():
        x(0),
        y(0)
    {}

    /**
     * @brief Parameterized constructor.
     * @param p_x X coordinate.
     * @param p_y Y coordinate.
     */
    Vector2f(int p_x, int p_y):
        x(p_x),
        y(p_y)
    {}

    /**
     * @brief Returns a zero vector (0, 0).
     * @return Vector2f A vector with both x and y set to 0.
     */
    Vector2f zero(){
        return Vector2f(0, 0);
    }
};

#endif /* GLOBALS */