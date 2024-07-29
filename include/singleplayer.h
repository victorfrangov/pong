#ifndef SINGLEPLAYER
#define SINGLEPLAYER

#include "graphics.h"
#include "hud.h"
#include "globals.h"

class Singleplayer{
public:
    Singleplayer(Graphics &p_graphics, Hud p_hud);

    void draw();

    void update();
private:
    int _points;
    Hud _hud;
};

#endif /* SINGLEPLAYER */
