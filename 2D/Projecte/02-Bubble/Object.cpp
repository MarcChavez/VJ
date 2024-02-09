#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Object.h"
#include "Game.h"




enum Objects
{
	Puerta, Llave, Reloj, Gema, Cronometro
};

enum PortalAnimation
{
	Cerrado, Abierto, Abriendose
 };

void Object::creaPortal()
{
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(Cerrado, 8);
	sprite->addKeyframe(Cerrado, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.125f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.375f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.625f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.75f, 0.0f));
	sprite->addKeyframe(Cerrado, glm::vec2(0.875f, 0.0f));

	sprite->setAnimationSpeed(Abierto, 8);
	sprite->addKeyframe(Abierto, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.375f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.625f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.875f, 0.25f));
	sprite->addKeyframe(Abierto, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(Abierto, glm::vec2(0.125f, 0.5f));


	sprite->setAnimationSpeed(Abriendose, 8);
	sprite->addKeyframe(Abriendose, glm::vec2(0.875f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.75f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.625f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.5f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.375f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.125f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.875f, 0.5f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.75f, 0.5f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.625f, 0.5f));
	sprite->addKeyframe(Abriendose, glm::vec2(0.5f, 0.5f));

}

void Object::creaKey()
{
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 2);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.5f));
}

void Object::creaGem()
{
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 7);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.125f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.375f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
}

void Object::creaChrono()
{
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 4);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.75f, 0.f));

}

void Object::creaWatch()
{
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.125f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.375f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.625f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.75f, 0.0f));
	sprite->addKeyframe(0, glm::vec2(0.875f, 0.f));

	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.125f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.25f, 0.50f));
	sprite->addKeyframe(0, glm::vec2(0.375f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.625f, 0.5f));
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int ObjectType)
{

	this->ObjectType = ObjectType;
	if (ObjectType == Puerta)
	{
		spritesheet.loadFromFile("images/portal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(32, 40), glm::vec2(0.125, 0.25), &spritesheet, &shaderProgram);
		creaPortal();
		
	}

	else if (ObjectType == Llave)
	{
		spritesheet.loadFromFile("images/llave.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);

		creaKey();
	}

	else if (ObjectType == Reloj)
	{
		spritesheet.loadFromFile("images/Stopwatch-Sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.125, 0.5), &spritesheet, &shaderProgram);

		creaWatch();
	}

	else if (ObjectType == Gema)
	{
		spritesheet.loadFromFile("images/Gem-Sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(14, 20), glm::vec2(0.125, 1), &spritesheet, &shaderProgram);

		creaGem();
	}
	
	else if (ObjectType == Cronometro)
	{
		spritesheet.loadFromFile("images/stopwatchdevd.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);

		creaChrono();
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	if (ObjectType != Puerta) sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y -5)));
	else
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x + 8), float(tileMapDispl.y + posObj.y)));

}

void Object::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Object::render()
{
	sprite->render();
}

void Object::changeAni(int ani)
{
	sprite->changeAnimation(ani);
}

void Object::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Object::setPosition(const glm::vec2& pos)
{
	posObj = pos;
	if (ObjectType != Puerta)
	{
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y -5)));
	}
	else
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x + 8), float(tileMapDispl.y + posObj.y)));
}

glm::ivec2 Object::getPosition()
{
	return posObj;
}

int Object::keyFrame()
{
	return sprite->getcurrentKeyframe();
}
