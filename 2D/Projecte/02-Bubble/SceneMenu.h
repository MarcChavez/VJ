#ifndef _SCENEMENU_INCLUDE
#define _SCENEMENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class SceneMenu
{

public:
	SceneMenu();
	~SceneMenu();

	void init(ShaderProgram &texProgram);
	void update(int deltaTime);
	void render();
	void changeAni(int sele);
	void changeWindow(int w, int h);


private:
	void initShaders();

private:

	ShaderProgram texProgram;

	float currentTime;
	Texture spritesheet;
	Sprite* sprite;

	Texture spritesheet2;
	Sprite* sprite2;

	TileMap* map;

	glm::mat4 projection;
	

};


#endif // _SCENEMENU_INCLUDE
