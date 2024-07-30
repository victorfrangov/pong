#ifndef SINGLEPLAYER
#define SINGLEPLAYER

#include "graphics.h"
#include "player.h"
#include "ball.h"
// #include "hud.h"
// #include "globals.h"
// #include "sprite.h"

class Singleplayer{
public:
    Singleplayer(Graphics &p_graphics, Player* p_player);

    void draw(Graphics &p_graphics);

    void update(float p_elapsedTime);
private:
    int _points;
    Player _player;
    Ball _ball;
};

#endif /* SINGLEPLAYER */
