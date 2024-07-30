#include "sprite.h"
#include "graphics.h"
#include "globals.h"
#include "bar.h"
#include <SDL2/SDL_image.h>

#include <iostream>

Sprite::Sprite(){}

Sprite::Sprite(Graphics &p_graphics, int p_sourceX, 
int p_sourceY, int p_width, int p_height, Vector2f p_pos):
    _x(p_pos.x),
    _y(p_pos.y)
{
    this->_src.x = p_sourceX;
    this->_src.y = p_sourceY;
    this->_src.w = p_width;
    this->_src.h = p_height;

    // Load image from memory
    SDL_RWops* rw = SDL_RWFromMem(bar_png, bar_png_len);
    if (!rw) {
        printf("SDL_RWFromMem Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Surface* surface = IMG_Load_RW(rw, 1); // 1 means SDL will free the RWops for us
    if (!surface) {
        printf("IMG_Load_RW Error: %s\n", IMG_GetError());
        return;
    }

    this->_spriteSheet = SDL_CreateTextureFromSurface(p_graphics.getRenderer(), surface);
    if (this->_spriteSheet == NULL) {
        printf("Error: Unable to load image onto _spriteSheet\n");
    }

    SDL_FreeSurface(surface);

    this->_boundingBox = Rectangle(this->_x, this->_y, p_width * globals::SPRITE_SCALE, p_height * globals::SPRITE_SCALE);
}

Sprite::~Sprite(){

}

void Sprite::update(){
    this->_boundingBox = Rectangle(this->_x, this->_y, this->_src.w * globals::SPRITE_SCALE, this->_src.h * globals::SPRITE_SCALE);
}

void Sprite::draw(Graphics &p_graphics, Vector2f p_pos){    
    SDL_Rect dst = {p_pos.x, p_pos.y, static_cast<int>(this->_src.w * globals::SPRITE_SCALE), 
    static_cast<int>(this->_src.h * globals::SPRITE_SCALE)};
    p_graphics.blitSurface(this->_spriteSheet, &this->_src, &dst);
}

const Rectangle Sprite::getBoundingBox() const{
    return this->_boundingBox;
}

//this gets called when there is a collision and you want to check which side collided
const sides::Side Sprite::getCollisionSide(const Rectangle &p_other) const{
    int amtRight, amtLeft, amtTop, amtBottom;

    amtRight = this->_boundingBox.getRight() - p_other.getLeft();
    amtLeft = p_other.getRight() - this->_boundingBox.getLeft();
    amtTop = p_other.getBottom() - this->_boundingBox.getTop();
    amtBottom = this->_boundingBox.getBottom() - p_other.getTop();

    int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
    int lowest = vals[0];
    for(int i = 0; i < sizeof(vals) / sizeof(vals[0]); i++){
        if(vals[i] < lowest){
            lowest = vals[i];
        }
    }

    return
            lowest == abs(amtRight) ? sides::RIGHT :
            lowest == abs(amtLeft) ? sides::LEFT :
            lowest == abs(amtTop) ? sides::TOP :
            lowest == abs(amtBottom) ? sides::BOTTOM :
            sides::NONE;
}

void Sprite::setSourceRectX(int p_value){
    this->_src.x = p_value;
}

void Sprite::setSourceRectY(int p_value){
    this->_src.y = p_value;
}

void Sprite::setSourceRectW(int p_value){
    this->_src.w = p_value;
}

void Sprite::setSourceRectH(int p_value){
    this->_src.h = p_value;
}