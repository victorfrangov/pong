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

	~Multiplayer();

	void draw(Graphics& p_graphics);

	void update(float p_elapsedTime);

	bool checkPlayerBallCollision();

	void handlePlayerBallCollision();
private:
	Player* _playerClient;
	Player* _playerHost;
	Hud& _hud;
	Ball _ball;

	Host* _host;
	Client* _client;

	const float COLLISION_COOLDOWN_TIME = 500.0f;
	float _collisionTimer;
};

#endif
