#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Pass.h"
#include "Game.h"


#define SCREEN_X 100
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 18

Pass::Pass()
{

	currentTime = 0;
}

Pass::~Pass()
{

}

void Pass::init(ShaderProgram& texProgram)
{
	this->texProgram = texProgram;
	spritesheet.loadFromFile("images/pass.png", TEXTURE_PIXEL_FORMAT_RGB);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(1080, 720), glm::vec2(0.5, 0.5), &spritesheet, &texProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 4);
	sprite->addKeyframe(0, glm::vec2(float(0.0), 0.f));
	sprite->addKeyframe(0, glm::vec2(float(0.50), 0.f));

	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(float(0.0), 0.5f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	spritesheet2.loadFromFile("images/passfont.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet2.setMagFilter(GL_NEAREST);
	sprite2 = Sprite::createSprite(glm::ivec2(29, 29), glm::vec2(0.0625, 0.25), &spritesheet2, &texProgram); //TIME_IZ

	sprite2->setNumberAnimations(37);
	int b = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (i >= 2 && j >= 5)
			{
				//d
			}
			else
			{
				sprite2->setAnimationSpeed(b, 8);
				sprite2->addKeyframe(b, glm::vec2(0.0625f * j, i * 0.25f));
				++b;
			}
			
		}
	}

	spritesheet3.loadFromFile("images/passfontError.png", TEXTURE_PIXEL_FORMAT_RGB);
	spritesheet3.setMagFilter(GL_NEAREST);
	sprite3 = Sprite::createSprite(glm::ivec2(29, 29), glm::vec2(0.125, 0.25), &spritesheet3, &texProgram);
	sprite3->setNumberAnimations(5);
		  
	sprite3->setAnimationSpeed(0, 4);
	sprite3->addKeyframe(0, glm::vec2(float(0.75), 0.25f));
		  
	sprite3->setAnimationSpeed(1, 8);
	sprite3->addKeyframe(1, glm::vec2(float(0.0), 0.75f));
		  
	sprite3->setAnimationSpeed(2, 8);
	sprite3->addKeyframe(2, glm::vec2(float(0.375), 0.75f));
		  
	sprite3->setAnimationSpeed(3, 8);
	sprite3->addKeyframe(3, glm::vec2(float(0.6255), 0.75f));
		  
	sprite3->setAnimationSpeed(4, 8);
	sprite3->addKeyframe(4, glm::vec2(float(0.75), 0.75f));
		  
	sprite3->changeAnimation(0);
	sprite3->setPosition(glm::vec2(float(0), float(0)));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Pass::update(int deltaTime)
{
	currentTime += deltaTime;

	if (pass == 0 && sprite->animation() != 0) sprite->changeAnimation(0);
	else if (sprite->animation() != 1 && pass > 0)
		sprite->changeAnimation(1);
	sprite->update(deltaTime);
}

void Pass::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	sprite->render();

	if (pass > 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			sprite2->changeAnimation(passWords[i]);
			sprite2->setPosition(glm::ivec2((29 * i) + (397), 400));
			sprite2->render();
		}
	}

	if (error)
	{
		sprite3->changeAnimation(0); //E
		sprite3->setPosition(glm::vec2(450, 393 + (3 * 29)));
		sprite3->render();

		sprite3->changeAnimation(2); //R
		sprite3->setPosition(glm::vec2(450 +(1*29), 393 + (3 * 29)));
		sprite3->render();

		sprite3->setPosition(glm::vec2(450 + (2 * 29), 393 + (3 * 29))); //R
		sprite3->render();

		sprite3->changeAnimation(1); //O
		sprite3->setPosition(glm::vec2(450 + (3 * 29), 393 + (3 * 29)));
		sprite3->render();

		sprite3->changeAnimation(2); //R
		sprite3->setPosition(glm::vec2(450 + (4 * 29), 393 + (3 * 29)));
		sprite3->render();

		sprite3->changeAnimation(3); //!!
		sprite3->setPosition(glm::vec2(450 + (5 * 29), 393 + (3 * 29)));
		sprite3->render();
	}
}

void Pass::setCode(int num)
{
	if (pass < 10)
	{
		if (num >= 48 && num <= 57)
		{
			passWords[pass] = num - 48;
			++pass;
		}
		else if (num >= 65 && num <= 90)
		{
			passWords[pass] = num - char('A') + 10;
			++pass;
		}
		else if (num >= 97 && num <= 122)
		{
			passWords[pass] = num - char('a') + 10;
			++pass;
		}
	}
	if (pass != 0)
	{
		if (num == 8)
		{
			this->passWords[pass-1] = 36;
			--pass;
		}
	}
}

void Pass::resetPassWord()
{
	pass = 0;
	for (int i = 0; i < 10; ++i)
		this->passWords[i] = 36;
}

string Pass::givePassWord()
{
	string password;
	for (int i = 0; i < pass; ++i)
	{
		if (passWords[i] <= 9) password += (int('0') + (passWords[i]));
		else if (passWords[i] <= 90) password += (int('A') + (passWords[i]-10));
		else
			password += (int('a') + (passWords[i] - 10));
	}
	return password;
}

void Pass::setPassWord(string a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[0] <= '9') passWords[i] = a[i]-int('0');
		else if (a[0] <= 'Z') passWords[i] = (a[i] - int('A'))+10;
		else if (a[0] <= 'z') passWords[i] = (a[i] - int('a')) + 10;
		pass++;
	}
}

void Pass::errorPasw(bool e)
{
	error = e;
}

void Pass::changeWindow(int w, int h)
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

