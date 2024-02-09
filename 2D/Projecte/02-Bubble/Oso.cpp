#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Oso.h"
#include "Game.h"


#define SCREEN_X 100
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 18

Oso::Oso()
{

	currentTime = 0;
}

Oso::~Oso()
{

}

void Oso::init(ShaderProgram& texProgram)
{
	this->texProgram = texProgram;
	spritesheet.loadFromFile("images/oso.png", TEXTURE_PIXEL_FORMAT_RGB);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(1080, 720), glm::vec2(1.0, 1.0), &spritesheet, &texProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(float(0.0), 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Oso::update(int deltaTime)
{
	currentTime += deltaTime;

}

void Oso::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	sprite->render();
}

void Oso::changeWindow(int w, int h)
{
	float windowRatio = w / float(h);
	float scale = 1.f;
	if (windowRatio > 1.5)
	{
		scale = h / 720.f;
		float offset = (w - 1080 * scale) / 2;
		projection = glm::ortho(-offset, float(w) - offset, float(h), 0.f);
	}
	else
	{
		scale = w / 1080.f;
		float offset = (h - 720 * scale) / 2;
		projection = glm::ortho(0.f, float(w), float(h) - offset, -offset);
	}

	projection = glm::scale(projection, glm::vec3(scale));
}




