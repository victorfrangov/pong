#ifndef SINGLEPLAYER
#define SINGLEPLAYER

#include "hud.h"
#include "graphics.h"
#include "globals.h"
#include "sprite.h"

class Singleplayer : public Sprite{
public:
    Singleplayer(Graphics &p_graphics, Hud *p_hud);

    void draw(Graphics &p_graphics);

    void update(float p_elapsedTime);
private:
    int _points;
    Hud _hud;
};

#endif /* SINGLEPLAYER */
