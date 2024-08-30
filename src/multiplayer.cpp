#include "multiplayer.h"
#include "host.h"
#include "client.h"

#include <enet/enet.h>

Multiplayer::Multiplayer(Graphics& p_graphics, std::shared_ptr<Player> p_playerClient, std::shared_ptr<Player> p_playerHost, Hud& p_hud) :
	_playerClient(p_playerClient ? std::move(p_playerClient) : nullptr),
	_playerHost(p_playerHost ? std::move(p_playerHost) : nullptr),
	_hud(p_hud),
	_collisionTimer(0.0f),
	_ball(p_graphics, Vector2f(globals::SCREEN_WIDTH / 2.0f, globals::SCREEN_HEIGHT / static_cast<float>(rand() % 7 + 1))),
	_host(nullptr),
	_client(nullptr)
	{
		if (!this->_playerClient) { // start a server
			this->_host = std::make_unique<Host>();
			//MUST WAIT THAT CLIENT IS OCNNECTED HERE
			if (this->_host->enetParseEvent().type == ENET_EVENT_TYPE_CONNECT) { //HERE IS PLACED IN LOBBY, MUST CHANGE HOW HUDCPP AND GAMECPP 
				//SEND TO THE GAME, ADD ANOTHER MPLOBBY MENU
				exit(EXIT_FAILURE);
			}

			//init thed other player here
			this->_playerClient = std::make_unique<Player>(p_graphics, Vector2f(100, 100));
		} else if (!this->_playerHost) { // start a client
			this->_client = std::make_unique<Client>();
			this->_client->connectToHost(); //show a little connecting... message on screen (WILL BE PASSING IN AS PARAM AN IP)

			this->_playerHost = std::make_unique<Player>(p_graphics, Vector2f(540, 100));
			//client.sendPacket();
		}
	}

void Multiplayer::draw(Graphics& p_graphics) {
	if (this->_playerClient) {
		this->_playerClient->draw(p_graphics);
	}
	if (this->_playerHost) {
		this->_playerHost->draw(p_graphics);
	}
	this->_ball.draw(p_graphics);
	//this->_hud.renderPoints(this->_playerClient, this->_playerHost); // one of the two will be null, add a check
}

void Multiplayer::update(float p_elapsedTime) {
	this->_ball.update(p_elapsedTime);
	if (this->_playerClient) { this->_playerClient->update(p_elapsedTime); } //client sends packet here?
	if (this->_playerHost) { this->_playerHost->update(p_elapsedTime); this->_host->enetParseEvent(); }
	if (this->_collisionTimer > 0.0f) { this->_collisionTimer -= p_elapsedTime; }

	this->handlePlayerBallCollision();

	if (this->_ball.getLostStatus()) {
        if (this->_playerClient && this->_playerHost) {
            if (this->_playerClient->getPoints() > this->_playerHost->getPoints()) {
                this->_playerClient->setWon();
                this->_playerHost->setLost();
            } else if (this->_playerHost->getPoints() > this->_playerClient->getPoints()) {
                this->_playerHost->setWon();
                this->_playerClient->setLost();
            } else {
                this->_playerClient->setLost();
                this->_playerHost->setLost();
            }
        }
    }
}

bool Multiplayer::checkPlayerBallCollision() {
	if (this->_playerClient && this->_playerHost) {
		const SpriteRectangle ballRect = this->_ball.getBoundingBox();
		const SpriteRectangle clientRect = this->_playerClient->getBoundingBox();
		const SpriteRectangle hostRect = this->_playerHost->getBoundingBox();
		return ballRect.collidesWith(clientRect) || ballRect.collidesWith(hostRect);
	}
	return false;
}

void Multiplayer::handlePlayerBallCollision() {
	if (this->_collisionTimer <= 0 && this->checkPlayerBallCollision()) {
		const SpriteRectangle ballRect = this->_ball.getBoundingBox();
		if (this->_playerClient && ballRect.collidesWith(this->_playerClient->getBoundingBox())) {
			this->_playerClient->gainPoint();
			sides::Side collisionSide = this->_playerClient->getCollisionSide(ballRect);
			if (collisionSide == sides::LEFT || collisionSide == sides::RIGHT) {
				this->_ball.reverseDirectionX();
			}
		}
		if (this->_playerHost && ballRect.collidesWith(this->_playerHost->getBoundingBox())) {
			this->_playerHost->gainPoint();
			sides::Side collisionSide = this->_playerHost->getCollisionSide(ballRect);
			if (collisionSide == sides::LEFT || collisionSide == sides::RIGHT) {
				this->_ball.reverseDirectionX();
			}
		}
		this->_collisionTimer = COLLISION_COOLDOWN_TIME;
	}
}