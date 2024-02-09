#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Object
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int EnemyType);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void changeAni(int ani);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();
	void creaKey();
	void creaPortal();
	void creaGem();
	void creaChrono();
	int keyFrame();
	void creaWatch();

private:

	glm::ivec2 tileMapDispl, posObj;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int ObjectType;

};


#endif // _OBJECT_INCLUDE



