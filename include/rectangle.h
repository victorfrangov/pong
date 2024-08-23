#ifndef RECTANGLE
#define RECTANGLE

#include "globals.h"

/**
 * @class Rectangle
 * @brief Represents a rectangle with position and dimensions.
 * 
 * The Rectangle class provides methods to get the properties of the rectangle,
 * check for collisions with other rectangles, and validate the rectangle.
 */
class SpriteRectangle {
public:
    /**
     * @brief Default constructor for the Rectangle class.
     */
    SpriteRectangle() :
        _x(0),
        _y(0),
        _width(0),
        _height(0) 
    {}

    /**
     * @brief Constructs a Rectangle with specified position and dimensions.
     * 
     * @param p_x The x-coordinate of the rectangle.
     * @param p_y The y-coordinate of the rectangle.
     * @param p_width The width of the rectangle.
     * @param p_height The height of the rectangle.
     */
    SpriteRectangle(int p_x, int p_y, int p_width, int p_height) :
        _x(p_x),
        _y(p_y),
        _width(p_width),
        _height(p_height)
    {}

    /**
     * @brief Gets the x-coordinate of the center of the rectangle.
     * 
     * @return int: The x-coordinate of the center.
     */
    int getCenterX() const { return this->_x + _width / 2; }

    /**
     * @brief Gets the y-coordinate of the center of the rectangle.
     * 
     * @return int: The y-coordinate of the center.
     */
    int getCenterY() const { return this->_y + _width / 2; }

    /**
     * @brief Gets the left side of the rectangle.
     * 
     * @return int: The x-coordinate of the left side.
     */
    int getLeft() const { return this->_x; }

    /**
     * @brief Gets the right side of the rectangle.
     * 
     * @return int: The x-coordinate of the right side.
     */
    int getRight() const { return this->_x + this->_width; }

    /**
     * @brief Gets the top side of the rectangle.
     * 
     * @return int: The y-coordinate of the top side.
     */
    int getTop() const { return this->_y; }

    /**
     * @brief Gets the bottom side of the rectangle.
     * 
     * @return int: The y-coordinate of the bottom side.
     */
    int getBottom() const { return this->_y + this->_height; }

    /**
     * @brief Gets the width of the rectangle.
     * 
     * @return int: The width of the rectangle.
     */
    int getWidth() const { return this->_width; }

    /**
     * @brief Gets the height of the rectangle.
     * 
     * @return int: The height of the rectangle.
     */
    int getHeight() const { return this->_height; }

    /**
     * @brief Gets the coordinate of the specified side of the rectangle.
     * 
     * @param p_side The side of the rectangle (LEFT, RIGHT, TOP, BOTTOM).
     * @return int: The coordinate of the specified side.
     */
    int getSide(const sides::Side p_side) const {
        return
            p_side == sides::LEFT ? this->getLeft() :
            p_side == sides::RIGHT ? this->getRight() :
            p_side == sides::BOTTOM ? this->getBottom() :
            p_side == sides::TOP ? this->getTop() :
            sides::NONE;
    }

    /**
     * @brief Checks if the rectangle collides with another rectangle.
     * 
     * @param p_other The other rectangle to check collision against.
     * @return bool: True if there is a collision, false otherwise.
     */
    bool collidesWith(const SpriteRectangle &p_other) const {
        return
            this->getRight() >= p_other.getLeft() &&
            this->getLeft() <= p_other.getRight() &&
            this->getTop() <= p_other.getBottom() &&
            this->getBottom() >= p_other.getTop();
    }

    /**
     * @brief Gets the rectangle itself.
     * 
     * @return const Rectangle: The rectangle.
     */
    const inline SpriteRectangle getRect() const { return *this; }

private:
    int _x; ///< The x-coordinate of the rectangle.
    int _y; ///< The y-coordinate of the rectangle.
    int _width; ///< The width of the rectangle.
    int _height; ///< The height of the rectangle.
};

#endif /* RECTANGLE_H */