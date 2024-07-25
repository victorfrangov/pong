#ifndef HUD
#define HUD

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Graphics;

class Hud{
public:
    Hud(Graphics &p_graphics);
    ~Hud();

    void renderText(const char* p_text, int p_x, int p_y);

    void renderMenu();
private:
    Graphics& _graphics;
    TTF_Font* _font;
    SDL_Color _color;
};

#endif /* HUD */
