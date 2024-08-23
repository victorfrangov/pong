#ifndef SINGLEPLAYER
#define SINGLEPLAYER

#include "graphics.h"
#include "player.h"
#include "ball.h"
#include "hud.h"
// #include "globals.h"
// #include "sprite.h"

class Singleplayer{
public:
	Singleplayer(Graphics &p_graphics, Player* p_player, Hud &p_hud);

	void draw(Graphics &p_graphics);

	void update(float p_elapsedTime);

	bool checkPlayerBallCollision();

	void handlePlayerBallCollision();
private:
	Player &_player;
	Hud &_hud;
	Ball _ball;

	const float COLLISION_COOLDOWN_TIME = 200.0f;
	float _collisionTimer;
};

#endif /* SINGLEPLAYER */
