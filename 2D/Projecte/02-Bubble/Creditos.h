#ifndef _CREDITOS_INCLUDE
#define _CREDITOS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Creditos
{

public:
	Creditos();
	~Creditos();

	void init(ShaderProgram& texProgram);
	void update(int deltaTime);
	void render();
	void changeWindow(int w, int h);


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


#endif // _CREDITOS_INCLUDE
#pragma once

