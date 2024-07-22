#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <map>

/**
 * @class Input
 * @brief Handles all keyboard inputs and checks different states of a key.
 * 
 * This class is responsible for managing keyboard input states across frames,
 * including pressed, released, and held states.
 */
class Input{
public:
    /**
     * @brief Called at the beginning of each new frame to reset the keys' states.
     * 
     * Clears the states of _pressedKeys and _releasedKeys to prepare for the next frame's input.
     */
    void beginNewFrame();
    
    /**
     * @brief Handles the event when a key is released.
     * 
     * Updates the _heldKeys and _releasedKeys maps based on the key release event.
     * 
     * @param e The SDL_Event containing the key release information.
     */
    void keyUpEvent(const SDL_Event& e);
    
    /**
     * @brief Handles the event when a key is pressed.
     * 
     * Updates the _heldKeys and _pressedKeys maps based on the key press event.
     * 
     * @param e The SDL_Event containing the key press information.
     */
    void keyDownEvent(const SDL_Event& e);
    
    /**
     * @brief Checks if a specific key was pressed during the current frame.
     * 
     * @param p_key The SDL_Scancode representing the key to check.
     * @return bool True if the key was pressed, false otherwise.
     */
    bool wasKeyPressed(SDL_Scancode p_key);
    
    /**
     * @brief Checks if a specific key was released during the current frame.
     * 
     * @param p_key The SDL_Scancode representing the key to check.
     * @return bool True if the key was released, false otherwise.
     */
    bool wasKeyReleased(SDL_Scancode p_key);
    
    /**
     * @brief Checks if a specific key is being held down.
     * 
     * @param p_key The SDL_Scancode representing the key to check.
     * @return bool True if the key is held, false otherwise.
     */
    bool isKeyHeld(SDL_Scancode p_key);

private:
    std::map<SDL_Scancode, bool> _heldKeys; ///< Tracks keys that are currently held down.
    std::map<SDL_Scancode, bool> _pressedKeys; ///< Tracks keys that were pressed during the current frame.
    std::map<SDL_Scancode, bool> _releasedKeys; ///< Tracks keys that were released during the current frame.
};

#endif // INPUT_H