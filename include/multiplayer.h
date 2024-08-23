#ifndef MULTIPLAYER
#define MULTIPLAYER

#include "graphics.h"
#include "player.h"
#include "ball.h"
#include "hud.h"
#include "client.h"
#include "host.h"

class Multiplayer {
public:
	Multiplayer(Graphics& p_graphics, Player* p_client, Player* p_host, Hud& p_hud);

	void draw(Graphics& p_graphics);

	void update(float p_elapsedTime);

	bool checkPlayerBallCollision();

	void handlePlayerBallCollision();
private:
	Player* _client;
	Player* _host;
	Hud& _hud;
	Ball _ball;

	const float COLLISION_COOLDOWN_TIME = 500.0f;
	float _collisionTimer;
};

#endif
