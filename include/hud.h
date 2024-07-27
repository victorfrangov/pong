#ifndef HUD
#define HUD

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "globals.h"

class Graphics;

class Hud{
public:
    Hud(Graphics &p_graphics);
    ~Hud();

    void draw(Uint8 p_menuIndex, float p_fps, int p_elapsedTime);

    void update();

    void renderText(std::string p_text, int p_x, int p_y, int p_texW, int p_texH);

    void renderMenu();

    void renderOptions();

    void renderFrameInfo(float p_fps, int p_elapsedTime);

    void toggleFps();
private:
    Graphics& _graphics;
    TTF_Font* _font;
    SDL_Color _color;

    bool _showFPS = false;
};

struct HudItem {
    std::string text;
    Vector2f pos;
};

#endif /* HUD */
