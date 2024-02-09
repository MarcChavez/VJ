#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class GameOver
{

public:
	GameOver();
	~GameOver();

	void init(ShaderProgram &texProgram);
	void update(int deltaTime);
	void changeWindow(int w, int h);
	void render();


private:


private:

	ShaderProgram texProgram;

	float currentTime;
	Texture spritesheet;
	Sprite* sprite;

	Texture spritesheet2;
	Sprite* sprite2;

	glm::mat4 projection;


};


#endif // _GAMEOVER_INCLUDE
#pragma once
