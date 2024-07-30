#ifndef SINGLEPLAYER
#define SINGLEPLAYER

#include "hud.h"
#include "graphics.h"
#include "globals.h"
#include "sprite.h"
#include "player.h"

class Singleplayer : public Sprite{
public:
    Singleplayer(Graphics &p_graphics, Player* p_player);

    void draw(Graphics &p_graphics);

    void update(float p_elapsedTime);
private:
    int _points;
    Player _player;
};

#endif /* SINGLEPLAYER */
