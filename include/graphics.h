#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * @file graphics.h
 * @brief Holds all information for graphics management in the game.
 */

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Rect;
struct SDL_Texture;

/**
 * @class Graphics
 * @brief Manages all graphics for the game.
 * 
 * This class is responsible for initializing and handling the main window and renderer.
 * It also manages loading and drawing textures.
 */
class Graphics {
public:
    /**
     * @brief Constructor that initializes the window and the renderer.
     * 
     * Sets the window title to "Cavestory".
     */
    Graphics();

    /**
     * @brief Destructor that cleans up resources.
     * 
     * Destroys the window and renderer, freeing up memory.
     */
    ~Graphics();

    /**
     * @brief Loads an image into the _spriteSheets map if it doesn't already exist.
     * 
     * Ensures each image is only loaded once. Returns the image from the map
     * regardless of whether it was just loaded or not.
     * 
     * @param p_filePath The file path of the image to load.
     * @return SDL_Surface* Pointer to the loaded surface.
     */
    SDL_Surface* loadImage(const std::string &p_filePath);

    /**
     * @brief Draws a given texture onto a part of the screen.
     * 
     * @param p_texture The texture to draw.
     * @param p_src The source rectangle within the texture to draw.
     * @param p_dst The destination rectangle on the screen to draw the texture to.
     */
    void blitSurface(SDL_Texture* p_texture, SDL_Rect* p_src, SDL_Rect* p_dst);

    /**
     * @brief Renders everything on the screen.
     */
    void flip();

    /**
     * @brief Clears the screen.
     */
    void clear();

    /**
     * @brief Returns the renderer instance.
     * 
     * @return SDL_Renderer* The current renderer instance.
     */
    SDL_Renderer* getRenderer() const;

private:
    SDL_Window* _window; ///< The main window.
    SDL_Renderer* _renderer; ///< The renderer for drawing.
    std::map<std::string, SDL_Surface*> _spriteSheets; ///< Map of sprite sheets loaded.
};
#endif /* GRAPHICS_H */