#ifndef SPRITE
#define SPRITE

#include <SDL3/SDL.h>
#include <string>

#include "rectangle.h"
#include "globals.h"

class Graphics;

/**
 * @class Sprite
 * @brief Holds all information for individual sprites.
 * 
 * This class is responsible for managing the properties of a sprite,
 * including its texture, position, and rendering.
 */
class Sprite{
public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the Sprite class with default parameters.
     */
    Sprite();
    
    /**
     * @brief Overloaded constructor.
     * 
     * Initializes a new instance of the Sprite class with specific attributes.
     * 
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_filePath Path to the sprite sheet file.
     * @param p_sourceX X position in the sprite sheet.
     * @param p_sourceY Y position in the sprite sheet.
     * @param p_width Width of the sprite.
     * @param p_height Height of the sprite.
     * @param p_posX Initial X position of the sprite.
     * @param p_posY Initial Y position of the sprite.
     */
    Sprite(Graphics &p_graphics, float p_sourceX, float p_sourceY,
            float p_width, float p_height, Vector2f p_pos);
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~Sprite();
    
    /**
     * @brief Updates the sprite's state.
     * 
     * This method should be overridden by derived classes to update the sprite's state
     * for each frame.
     */
    virtual void update();
    
    /**
     * @brief Draws the sprite.
     * 
     * Renders the sprite at the specified position.
     * 
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_x X position where the sprite should be drawn.
     * @param p_y Y position where the sprite should be drawn.
     */
    void draw(Graphics &p_graphics, Vector2f p_pos);

    /**
     * @brief Gets the bounding box of the sprite.
     * 
     * This method returns the bounding box of the sprite, which can be used for collision detection
     * and other purposes where the physical boundaries of the sprite are needed.
     * 
     * @return const Rectangle: The bounding box of the sprite.
     */
    const Rectangle getBoundingBox() const;

    /**
     * @brief Determines the side of the collision with another rectangle.
     * 
     * This method compares the bounding box of the sprite with another rectangle (typically another sprite's bounding box)
     * to determine on which side the collision occurred. This can be useful for resolving collisions in a more
     * specific manner, such as adjusting sprite position or triggering different behaviors based on the collision side.
     * 
     * @param p_other The Rectangle to check collision against.
     * @return const sides::Side: The side of the sprite where the collision with the other rectangle occurred.
     */
    const sides::Side getCollisionSide(const Rectangle &p_other) const;

    /**
     * @brief Sets the x-coordinate of the source rectangle.
     * 
     * This method sets the x-coordinate of the source rectangle in the sprite sheet.
     * 
     * @param p_value The new x-coordinate value.
     */
    void setSourceRectX(int p_value);

    /**
     * @brief Sets the y-coordinate of the source rectangle.
     * 
     * This method sets the y-coordinate of the source rectangle in the sprite sheet.
     * 
     * @param p_value The new y-coordinate value.
     */
    void setSourceRectY(int p_value);

    /**
     * @brief Sets the width of the source rectangle.
     * 
     * This method sets the width of the source rectangle in the sprite sheet.
     * 
     * @param p_value The new width value.
     */
    void setSourceRectW(int p_value);

    /**
     * @brief Sets the height of the source rectangle.
     * 
     * This method sets the height of the source rectangle in the sprite sheet.
     * 
     * @param p_value The new height value.
     */
    void setSourceRectH(int p_value);

    /**
     * @brief Gets the x-coordinate of the sprite.
     * 
     * This method returns the current x-coordinate of the sprite.
     * 
     * @return float: The x-coordinate of the sprite.
     */
    inline float getX() const { return this->_x; }

    /**
     * @brief Gets the y-coordinate of the sprite.
     * 
     * This method returns the current y-coordinate of the sprite.
     * 
     * @return float: The y-coordinate of the sprite.
     */
    inline float getY() const { return this->_y; }

protected:
    SDL_FRect _src; ///< Source rectangle in the sprite sheet.
    SDL_Texture* _spriteSheet; ///< Texture of the sprite sheet.
    float _x, _y; ///< Current position of the sprite.
    Rectangle _boundingBox; ///< Bounding box of the sprite.
};

#endif /* SPRITE */