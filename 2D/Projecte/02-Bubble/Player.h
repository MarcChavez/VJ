#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, int show);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	int ObjectTaken();
	void setInmortality();
	glm::ivec2 getPosition();
	bool estasMuelto();
	bool lastFrame();

	bool mueltoduda()  { return muelto; }

	glm::ivec2 getposReal();
	glm::ivec2 getTileReal() { return PlayerTileSize; }
	int getPuntos();
	void cargaSpriteNormal();
	void cargaSpriteShiny();
	void updateShiny(int deltaTime, int show);

	bool getInmortal() { return inmortal; }

	void cargaSprite(int deltaTime);

	bool isTp() { return (sprite->animation() == 7 || sprite->animation() == 14); }

	void dontJump() { dontMove = true;  }

	bool stillJumping() { return bJumping; }

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	glm::ivec2 PlayerTileSize, posPlayerReal_x_L, posPlayerReal_x_R;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int Object = -1;
	bool muelto = false;
	int puntos = 0;
	int time, time2;
	bool phase = false;
	int yaesta = 0;
	bool inmortal = false;

	bool dontMove = false;

};


#endif // _PLAYER_INCLUDE


