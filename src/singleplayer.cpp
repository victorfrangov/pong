#include "singleplayer.h"
// #include "sprite.h"

Singleplayer::Singleplayer(Graphics &p_graphics, Player* p_player, Hud &p_hud) :
        _player(*p_player),
        _hud(p_hud),
        _ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / 2), p_hud)
        {
        }

void Singleplayer::draw(Graphics &p_graphics){
    this->_player.draw(p_graphics);
    this->_ball.draw(p_graphics);
    this->_hud.renderPoints(&this->_player);
}

void Singleplayer::update(float p_elapsedTime){
    this->_ball.update(p_elapsedTime);
    this->_player.update(p_elapsedTime);
    
    this->handlePlayerBallCollision();

    if(this->_ball.getLostStatus()){
        this->_player.setLost();
    }
}

bool Singleplayer::checkPlayerBallCollision(){
    const Rectangle ballRect = this->_ball.getBoundingBox();
    const Rectangle playerRect = this->_player.getBoundingBox();
    return ballRect.collidesWith(playerRect);
}

void Singleplayer::handlePlayerBallCollision(){
    if(this->checkPlayerBallCollision()){
        this->_player.gainPoint();
        const Rectangle ballRect = this->_ball.getBoundingBox();
        sides::Side test = this->_player.getCollisionSide(ballRect);
        if(test == sides::LEFT || test == sides::RIGHT)
            this->_ball.reverseDirectionX();
        else if(test == sides::TOP || test == sides::BOTTOM)
            this->_ball.reverseDirectionY();
    }
}

//fixed
// void Singleplayer::handlePlayerBallCollision(){
//     if(this->checkPlayerBallCollision()){
//         this->_player.gainPoint();
//         const Rectangle ballRect = this->_ball.getBoundingBox();
//         sides::Side collisionSide = this->_player.getCollisionSide(ballRect);

//         // Update ball position based on collision side
//         switch(collisionSide) {
//             case sides::LEFT:
//                 this->_ball.setPosition(this->_player.getBoundingBox().getRight() + 1, ballRect.getY());
//                 this->_ball.reverseDirectionX();
//                 break;
//             case sides::RIGHT:
//                 this->_ball.setPosition(this->_player.getBoundingBox().getLeft() - ballRect.getWidth() - 1, ballRect.getY());
//                 this->_ball.reverseDirectionX();
//                 break;
//             case sides::TOP:
//                 this->_ball.setPosition(ballRect.getX(), this->_player.getBoundingBox().getBottom() + 1);
//                 this->_ball.reverseDirectionY();
//                 break;
//             case sides::BOTTOM:
//                 this->_ball.setPosition(ballRect.getX(), this->_player.getBoundingBox().getTop() - ballRect.getHeight() - 1);
//                 this->_ball.reverseDirectionY();
//                 break;
//             default:
//                 break;
//         }
//     }
// }