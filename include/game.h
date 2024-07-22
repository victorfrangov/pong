/**
 * @file game.h
 * @brief Defines the Game class responsible for managing the game's main loop and state.
 *
 * This file contains the Game class declaration, including the constructor and destructor,
 * and methods for the game loop, drawing, and updating game state.
 */

#ifndef GAME_H
#define GAME_H

#include "graphics.h"

/**
 * @class Game
 * @brief Manages the main game loop, rendering, and updating.
 *
 * The Game class is central to the game application. It initializes the game state,
 * enters the main game loop, and handles updates and rendering.
 */
class Game{
public:
    /**
     * @brief Constructs the Game object and initializes game state.
     */
    Game();

    /**
     * @brief Destructs the Game object, performing necessary cleanup.
     */
    ~Game();

private:
    /**
     * @brief Contains the game's main loop logic.
     *
     * Calls update and draw methods in a loop until the game ends.
     */
    void gameLoop();

    /**
     * @brief Draws the game's current state to the screen.
     *
     * @param p_graphics Reference to the Graphics object for rendering.
     */
    void draw(Graphics &p_graphics);

    /**
     * @brief Updates the game's state.
     *
     * @param p_elapsedTime The time elapsed since the last update call.
     */
    void update(float p_elapsedTime, Graphics &p_graphics);

    Graphics _graphics; ///< Graphics object used for rendering.
};

#endif // GAME_H