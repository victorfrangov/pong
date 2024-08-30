#ifndef MULTIPLAYER
#define MULTIPLAYER

#include "graphics.h"
#include "player.h"
#include "ball.h"
#include "hud.h"
#include "client.h"
#include "host.h"

#include <memory>

class Multiplayer {
public:
	Multiplayer(Graphics& p_graphics, std::shared_ptr<Player> p_client, std::shared_ptr<Player> p_host, Hud& p_hud);

	~Multiplayer() = default;

	void draw(Graphics& p_graphics);

	void update(float p_elapsedTime);

private:
	std::shared_ptr<Player> _playerClient;
	std::shared_ptr<Player> _playerHost;
	Hud& _hud;
	Ball _ball;

	std::unique_ptr<Host> _host;
	std::unique_ptr<Client> _client;

	const float COLLISION_COOLDOWN_TIME = 500.0f;
	float _collisionTimer;

	bool checkPlayerBallCollision();

	void handlePlayerBallCollision();
};

#endif
