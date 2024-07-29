#include "singleplayer.h"
#include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Hud *p_hud) :
        _points(0),
        _hud(p_graphics)
        {
        }

void Singleplayer::draw(Graphics &p_graphics){
    Sprite::draw(p_graphics, 0, 0);
}

void Singleplayer::update(float p_elapsedTime){

}