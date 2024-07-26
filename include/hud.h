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

    void renderText(const char* p_text, int p_x, int p_y, int p_texW, int p_texH);

    void freeMemory(SDL_Texture* p_texture, SDL_Surface* p_surface);

    void renderMenu();
private:
    Graphics& _graphics;
    TTF_Font* _font;
    SDL_Color _color;
};

struct MenuItem {
    const char* text;
    Vector2f pos;
};

#endif /* HUD */
