#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneMenu.h"
#include "Game.h"


#define SCREEN_X 100
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 18

SceneMenu::SceneMenu()
{

	currentTime = 0;
}

SceneMenu::~SceneMenu()
{
	
}

void SceneMenu::init(ShaderProgram& texProgram)
{
	//initShaders();
	this->texProgram = texProgram;
	spritesheet.loadFromFile("images/Intro.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(1080, 720), glm::vec2(0.125, 0.250), &spritesheet, &texProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			sprite->addKeyframe(0, glm::vec2(float(0.125)*y, x*0.25f));
		}
	}
	
	

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	spritesheet2.loadFromFile("images/IntroSelect.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet2.setMagFilter(GL_NEAREST);
	sprite2 = Sprite::createSprite(glm::ivec2(1080, 720), glm::vec2(0.5, 0.250), &spritesheet2, &texProgram);
	sprite2->setNumberAnimations(3);

	sprite2->setAnimationSpeed(2, 2);
	sprite2->addKeyframe(2, glm::vec2(float(0.0), 0.0f));
	sprite2->addKeyframe(2, glm::vec2(float(0.50), 0.0f));

	sprite2->setAnimationSpeed(1, 2);
	sprite2->addKeyframe(1, glm::vec2(float(0.0), 0.25f));
	sprite2->addKeyframe(1, glm::vec2(float(0.5), 0.25f));

	sprite2->setAnimationSpeed(0, 2);
	sprite2->addKeyframe(0, glm::vec2(float(0.0),  0.5f));
	sprite2->addKeyframe(0, glm::vec2(float(0.5), 0.5f));
	


	sprite2->changeAnimation(0);
	sprite2->setPosition(glm::vec2(float(0), float(0)));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void SceneMenu::update(int deltaTime)
{
	currentTime += deltaTime;
	sprite->update(deltaTime);
	sprite2->update(deltaTime);

}

void SceneMenu::changeAni(int sele)
{
	sprite2->changeAnimation(sele);
}

void SceneMenu::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	sprite->render();
	sprite2->render();
}

void SceneMenu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void SceneMenu::changeWindow(int w, int h)
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




