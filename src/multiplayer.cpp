#include "multiplayer.h"
#include "host.h"
#include "client.h"

#include <enet/enet.h>

Multiplayer::Multiplayer(Graphics& p_graphics, Player* p_client, Player* p_host, Hud& p_hud) :
	_client(p_client),
	_host(p_host),
	_hud(p_hud),
	_collisionTimer(0.0f),
	_ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2, globals::SCREEN_HEIGHT / (rand() % 7 + 1)))
	{
		if (!this->_client) { // start a server
			Host host();
		} else if (!this->_host) { // start a client
			Client client();
		}
	}

void Multiplayer::draw(Graphics& p_graphics) {
	if (this->_client) {
		this->_client->draw(p_graphics);
	}
	if (this->_host) {
		this->_host->draw(p_graphics);
	}
	this->_ball.draw(p_graphics);
	//this->_hud.renderPoints(this->_client, this->_host);
}

void Multiplayer::update(float p_elapsedTime) {
	this->_ball.update(p_elapsedTime);
	if (this->_client) { this->_client->update(p_elapsedTime); }
	if (this->_host) { this->_host->update(p_elapsedTime); }
	if (this->_collisionTimer > 0.0f) { this->_collisionTimer -= p_elapsedTime; }

	this->handlePlayerBallCollision();

	if (this->_ball.getLostStatus()) {
        if (this->_client && this->_host) {
            if (this->_client->getPoints() > this->_host->getPoints()) {
                this->_client->setWon();
                this->_host->setLost();
            } else if (this->_host->getPoints() > this->_client->getPoints()) {
                this->_host->setWon();
                this->_client->setLost();
            } else {
                this->_client->setLost();
                this->_host->setLost();
            }
        }
    }
}

bool Multiplayer::checkPlayerBallCollision() {
	if (this->_client && this->_host) {
		const SpriteRectangle ballRect = this->_ball.getBoundingBox();
		const SpriteRectangle clientRect = this->_client->getBoundingBox();
		const SpriteRectangle hostRect = this->_host->getBoundingBox();
		return ballRect.collidesWith(clientRect) || ballRect.collidesWith(hostRect);
	}
	return false;
}

void Multiplayer::handlePlayerBallCollision() {
	if (this->_collisionTimer <= 0 && this->checkPlayerBallCollision()) {
		const SpriteRectangle ballRect = this->_ball.getBoundingBox();
		if (this->_client && ballRect.collidesWith(this->_client->getBoundingBox())) {
			this->_client->gainPoint();
			sides::Side collisionSide = this->_client->getCollisionSide(ballRect);
			if (collisionSide == sides::LEFT || collisionSide == sides::RIGHT) {
				this->_ball.reverseDirectionX();
			}
		}
		if (this->_host && ballRect.collidesWith(this->_host->getBoundingBox())) {
			this->_host->gainPoint();
			sides::Side collisionSide = this->_host->getCollisionSide(ballRect);
			if (collisionSide == sides::LEFT || collisionSide == sides::RIGHT) {
				this->_ball.reverseDirectionX();
			}
		}
		this->_collisionTimer = COLLISION_COOLDOWN_TIME;
	}
}