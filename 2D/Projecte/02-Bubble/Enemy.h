#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int EnemyType);
	void update(int deltaTime, bool stoped);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	void setTileSize(int tilesize);

	void creaVampire();
	void creaSkeleton();
	void creaArcher();
	void creaBala();

	void updateVampire(int deltaTime);
	void updateSkeleton();
	void updateArcher(int deltaTime);
	void updateBala();
	bool check_disparo(int yP1, int yP2, int yE1, int yE2, int xP1, int xP2, int xE1, int xE2);
	void Test();
	void Test2();
	void moveVamp();
	void moveBat();
	int isArcher();
	bool check_Bala_colision();
	void setDireccion(bool iz);
	bool createDisparo();
	bool getDireccion();


	bool detectPlayer(const glm::ivec2& pos, const glm::ivec2& size);

private:
	glm::ivec2 tileMapDispl, posEnemy, posBat, posVamp;
	glm::ivec2 EnemyTileSize;
	glm::ivec2 EnemyTileSizeBat, EnemyTileSizeVamp;
	Texture spritesheet;
	Sprite* sprite;
	Texture spritesheetBat;
	Sprite* spriteBat;
	TileMap* map;

	ShaderProgram Shprogram;

	bool izq = false, mov = true, up = true;
	bool izqTest = true;
	int EnemyType;
	int tileSize;
	bool tiro = false;
	bool auch = false;

	int yVamp1, yVamp2;

	float timeArquero = 0;
	float timeVampiro = 0;
	float timeCooldown = 0.0;
	bool cooldown = false;

	bool bat_mode = false;
	bool animationOn = false;
	bool dispara = false;

	bool music = false;

	int x_Real = 0;
	int y_Real = 0;

};


#endif // _ENEMY_INCLUDE



