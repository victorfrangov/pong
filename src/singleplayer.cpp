#include "singleplayer.h"
#include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Hud p_hud) :
        _points(0),
        _hud(p_graphics)
        {
            Sprite sprite(p_graphics, "res/gfx/bar.png", 0, 0, 10, 75, 50, 50);
        }

void Singleplayer::draw(){

}

void Singleplayer::update(){

}