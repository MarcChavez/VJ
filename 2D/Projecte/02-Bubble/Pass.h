#ifndef _PASS_INCLUDE
#define _PASS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Texture.h"
#include "Sprite.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Pass
{

public:
	Pass();
	~Pass();

	void init(ShaderProgram& texProgram);
	void update(int deltaTime);
	void render();
	void setCode(int num);
	void resetPassWord();
	string givePassWord();
	void setPassWord(string a);
	void errorPasw(bool e);
	void changeWindow(int w, int h);


private:

	ShaderProgram texProgram;

	float currentTime;
	Texture spritesheet;
	Sprite* sprite;

	Texture spritesheet2;
	Sprite* sprite2;

	Texture spritesheet3;
	Sprite* sprite3;

	bool error = false;

	glm::mat4 projection;

	int pass = 0;
	int passWords[10] = {36, 36, 36, 36, 36, 36, 36, 36, 36, 36};


};


#endif // _INSTRUCCIONES_PASS
#pragma once
