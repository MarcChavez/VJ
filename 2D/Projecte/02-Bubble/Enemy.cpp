#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 70
#define FALL_STEP 4


enum Enemies
{
	Esqueleto, Vampiro, Arquero, Bala
};

enum VampireAnims
{
	V_STAND_LEFT, V_STAND_RIGHT, V_MOVE_LEFT, V_MOVE_RIGHT, B_STAND_LEFT, B_STAND_RIGHT, B_MOVE_LEFT, B_MOVE_RIGHT, B_T_LEFT, B_T_RIGHT, V_T_LEFT, V_T_RIGHT
};

enum EsqueletoAnims
{
	E_STAND_LEFT, E_STAND_RIGHT, E_MOVE_LEFT, E_MOVE_RIGHT
};

enum ArqueroAnims
{
	A_STAND_LEFT, A_STAND_RIGHT, A_MOVE_LEFT, A_MOVE_RIGHT, A_SHOOT_LEFT, A_SHOOT_RIGHT
};


void Enemy::creaSkeleton()
{
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(E_STAND_LEFT, 8);
	sprite->addKeyframe(E_STAND_LEFT, glm::vec2(float(0.0), 0.f));


	sprite->setAnimationSpeed(E_STAND_RIGHT, 8);
	sprite->addKeyframe(E_STAND_RIGHT, glm::vec2(float(0.0), 0.5f));

	sprite->setAnimationSpeed(E_MOVE_LEFT, 8);
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.0), 0.f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.125), 0.f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.25), 0.f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.375), 0.f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.5), 0.f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.625), 0.f));

	sprite->setAnimationSpeed(E_MOVE_RIGHT, 8);
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.0), 0.5f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.125), 0.5f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.25), 0.5f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.375), 0.5f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.5), 0.5f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.625), 0.5f));
}

void Enemy::creaVampire()
{
	sprite->setNumberAnimations(12);

	// T_LEFT, T_RIGHT
	
	float a = 1.f / 16.f;
	sprite->setAnimationSpeed(V_STAND_LEFT, 8);
	sprite->addKeyframe(V_STAND_LEFT, glm::vec2(float(a*10), 0.25f));


	sprite->setAnimationSpeed(V_STAND_RIGHT, 8);
	sprite->addKeyframe(V_STAND_RIGHT, glm::vec2(float(a*6), 0.75f));

	sprite->setAnimationSpeed(V_MOVE_LEFT, 8);
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a*7), 0.25f));
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a * 8), 0.25f));
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a * 9), 0.25f));
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a * 10), 0.25f));
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a * 11), 0.25f));
	sprite->addKeyframe(V_MOVE_LEFT, glm::vec2(float(a * 12), 0.25f));

	sprite->setAnimationSpeed(V_MOVE_RIGHT, 8);
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 4), 0.75f));
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 5), 0.75f));
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 6), 0.75f));
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 7), 0.75f));
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 8), 0.75f));
	sprite->addKeyframe(V_MOVE_RIGHT, glm::vec2(float(a * 9), 0.75f));

	sprite->setAnimationSpeed(B_STAND_LEFT, 8);
	sprite->addKeyframe(B_STAND_LEFT, glm::vec2(float(0.0), 0.0f));

	sprite->setAnimationSpeed(B_STAND_RIGHT, 8);
	sprite->addKeyframe(B_STAND_RIGHT, glm::vec2(float(0.0), 0.50f));

	sprite->setAnimationSpeed(B_MOVE_LEFT, 8);
	sprite->addKeyframe(B_MOVE_LEFT, glm::vec2(float(0.0), 0.0f));
	sprite->addKeyframe(B_MOVE_LEFT, glm::vec2(float(a * 1), 0.0f));
	sprite->addKeyframe(B_MOVE_LEFT, glm::vec2(float(a * 2), 0.0f));
	sprite->addKeyframe(B_MOVE_LEFT, glm::vec2(float(a * 3), 0.0f));

	sprite->setAnimationSpeed(B_MOVE_RIGHT, 8);
	sprite->addKeyframe(B_MOVE_RIGHT, glm::vec2(float(a * 14), 0.25f));
	sprite->addKeyframe(B_MOVE_RIGHT, glm::vec2(float(a * 15), 0.25f));
	sprite->addKeyframe(B_MOVE_RIGHT, glm::vec2(float(0.0), 0.50f));
	sprite->addKeyframe(B_MOVE_RIGHT, glm::vec2(float(a * 1), 0.50f));

	sprite->setAnimationSpeed(B_T_LEFT, 8);
	//sprite->addKeyframe(T_LEFT, glm::vec2(float(a*6), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*5), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*7), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*8), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*9), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*10), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*11), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*12), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*13), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*14), 0.0f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*15), 0.0f));

	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*0), 0.25f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*1), 0.25f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*2), 0.25f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*3), 0.25f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*4), 0.25f));
	sprite->addKeyframe(B_T_LEFT, glm::vec2(float(a*5), 0.25f));

	sprite->setAnimationSpeed(B_T_RIGHT, 8);
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*3), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*4), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*5), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*6), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*7), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*8), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*9), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*10), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*11), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*12), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*13), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*14), 0.5f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*15), 0.5f));
												 
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*0), 0.75f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*1), 0.75f));
	sprite->addKeyframe(B_T_RIGHT, glm::vec2(float(a*2), 0.75f));

	///////////////////////////////////////////////////////////////

	sprite->setAnimationSpeed(V_T_LEFT, 8);
	//sprite->addKeyframe(T_LEFT, glm::vec2(float(a*6), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 5), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 4), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 3), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 2), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 1), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 0), 0.25f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 15), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 14), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 13), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 12), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 11), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 10), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 9), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 8), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 7), 0.0f));
	sprite->addKeyframe(V_T_LEFT, glm::vec2(float(a * 5), 0.0f));					

	sprite->setAnimationSpeed(V_T_RIGHT, 8);
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 2), 0.75f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 1), 0.75f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 0), 0.75f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 15), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 14), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 13), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 12), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 11), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 10), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 9), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 8), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 7), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 6), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 5), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 4), 0.5f));
	sprite->addKeyframe(V_T_RIGHT, glm::vec2(float(a * 3), 0.5f));				

}

void Enemy::creaArcher()
{
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(A_STAND_LEFT, 5);
	sprite->addKeyframe(A_STAND_LEFT, glm::vec2(float(0.5), 0.75f));
	
	sprite->setAnimationSpeed(A_STAND_RIGHT, 5);
	sprite->addKeyframe(A_STAND_RIGHT, glm::vec2(float(0.0), 0.25f));
	
	sprite->setAnimationSpeed(A_SHOOT_LEFT, 5);
	sprite->addKeyframe(A_SHOOT_LEFT, glm::vec2(float(0.0), 0.5f));
	sprite->addKeyframe(A_SHOOT_LEFT, glm::vec2(float(0.25), 0.5f));
	sprite->addKeyframe(A_SHOOT_LEFT, glm::vec2(float(0.5), 0.5f));
	sprite->addKeyframe(A_SHOOT_LEFT, glm::vec2(float(0.75), 0.5f));


	sprite->setAnimationSpeed(A_SHOOT_RIGHT, 5);
	sprite->addKeyframe(A_SHOOT_RIGHT, glm::vec2(float(0.0), 0.0f));
	sprite->addKeyframe(A_SHOOT_RIGHT, glm::vec2(float(0.25), 0.0f));
	sprite->addKeyframe(A_SHOOT_RIGHT, glm::vec2(float(0.50), 0.0f));
	sprite->addKeyframe(A_SHOOT_RIGHT, glm::vec2(float(0.75), 0.0f));

	sprite->setAnimationSpeed(A_MOVE_LEFT, 8);
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.0), 0.75f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.25), 0.75f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.5), 0.75f));
	sprite->addKeyframe(E_MOVE_LEFT, glm::vec2(float(0.75), 0.75f));

	sprite->setAnimationSpeed(A_MOVE_RIGHT, 8);
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.0), 0.25f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.25), 0.25f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.5), 0.25f));
	sprite->addKeyframe(E_MOVE_RIGHT, glm::vec2(float(0.75), 0.25f));

}

void Enemy::creaBala()
{
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(float(0.0), 0.f));
}

void Enemy::updateVampire(int deltaTime)
{
	timeVampiro += deltaTime;
	if (animationOn)
	{
		if (sprite->getcurrentKeyframe() == 15)
		{
			if (bat_mode)
			{
				if (izq) sprite->changeAnimation(V_MOVE_LEFT);
				else sprite->changeAnimation(V_MOVE_RIGHT);
				int y = ((posEnemy.y) / tileSize);
				posEnemy = glm::ivec2(posEnemy.x, y*tileSize);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
				animationOn = false;
				bat_mode = false;
			}
			else
			{
				if (izq) sprite->changeAnimation(B_MOVE_LEFT);
				else sprite->changeAnimation(B_MOVE_RIGHT);
				animationOn = false;
				bat_mode = true;
			}
			timeVampiro = 0;
		}
		if (music)
		{
			Music::instance().playTVampSound();
			music = false;
		}

	}
	else if (int(timeVampiro) >= 12000 && !animationOn && !bat_mode)
	{
		if (bat_mode)
		{
			if (izq) sprite->changeAnimation(B_T_LEFT);
			else sprite->changeAnimation(B_T_RIGHT);
			animationOn = true;
		}
		else
		{
			if (izq) sprite->changeAnimation(V_T_LEFT);
			else sprite->changeAnimation(V_T_RIGHT);
			animationOn = true;
			yVamp1 = (posEnemy.y) / tileSize;
			yVamp2 = ((posEnemy.y) + EnemyTileSize.y - 1) / tileSize;
		}

		Music::instance().playTVampSound();
	}
	
	else
	{
		if (bat_mode) moveBat();
		else moveVamp();
	}
}

void Enemy::moveBat()
{
	if (map->vampireFloor(posEnemy, EnemyTileSize) == 2 && (yVamp1 != ((posEnemy.y + posVamp.y) / tileSize) && yVamp2 != (((posEnemy.y + posVamp.y) + EnemyTileSize.y - 1) / tileSize))) //map->vampireFloor(posEnemy, EnemyTileSize)
	{
		if (izq) sprite->changeAnimation(B_T_LEFT);
		else sprite->changeAnimation(B_T_RIGHT);
		animationOn = true;
	}
	else
	{
		if (izq)
		{
			if (sprite->animation() != B_MOVE_LEFT)
				sprite->changeAnimation(B_MOVE_LEFT);
			posEnemy.x -= 1;

			if (map->collisionMoveLeftBat(posEnemy + posBat, EnemyTileSizeBat))
			{
				posEnemy.x += 1;
				izq = false;
				sprite->changeAnimation(B_STAND_LEFT);
			}
		}

		else
		{
			if (sprite->animation() != B_MOVE_RIGHT)
				sprite->changeAnimation(B_MOVE_RIGHT);
			posEnemy.x += 1;

			if (map->collisionMoveRightBat(posEnemy + posBat, EnemyTileSizeBat))
			{
				posEnemy.x -= 1;
				izq = true;
				sprite->changeAnimation(B_STAND_RIGHT);
			}

		}

		if (up)
		{
			posEnemy.y -= 1;

			if (map->collisionUpBat(posEnemy + posBat, EnemyTileSizeBat))
			{
				posEnemy.y += 1;
				up = false;
			}
		}
		else
		{
			posEnemy.y += 1;

			if (map->vampireFloor(posEnemy + posBat, EnemyTileSizeBat) >= 1)
			{
					posEnemy.y -= 1;
				up = true;
			}
		}
	}

}

void Enemy::moveVamp()
{
	if (izq && mov) //
	{
		if (sprite->animation() != V_MOVE_LEFT)
			sprite->changeAnimation(V_MOVE_LEFT);
		posEnemy.x -= 1;

		if (map->collisionMoveLeftEnemy(posEnemy + posVamp, EnemyTileSize))
		{
			posEnemy.x += 1;
			izq = false;
			mov = false;
			sprite->changeAnimation(V_STAND_LEFT);
		}
	}
	else if (!izq && mov)//
	{
		if (sprite->animation() != V_MOVE_RIGHT)
			sprite->changeAnimation(V_MOVE_RIGHT);
		posEnemy.x += 1;

		if (map->collisionMoveRightEnemy(posEnemy + posVamp, EnemyTileSize))
		{
			posEnemy.x -= 1;
			izq = true;
			mov = false;
			sprite->changeAnimation(V_STAND_RIGHT);
		}
	}
	else
		mov = true;
}

void Enemy::updateSkeleton()
{
	if (izq && mov) //
	{
		if (sprite->animation() != E_MOVE_LEFT)
			sprite->changeAnimation(E_MOVE_LEFT);
		posEnemy.x -= 1;

		if (map->collisionMoveLeftEnemy(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x += 1;
			izq = false;
			mov = false;
			x_Real = 5;
			sprite->changeAnimation(E_STAND_LEFT);
		}
	}
	else if (!izq && mov)//
	{
		if (sprite->animation() != E_MOVE_RIGHT)
			sprite->changeAnimation(E_MOVE_RIGHT);
		posEnemy.x += 1;

		if (map->collisionMoveRightEnemy(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x -= 1;
			izq = true;
			mov = false;
			x_Real = 10;
			sprite->changeAnimation(E_STAND_RIGHT);
		}
	}
	else
		mov = true;
}

void Enemy::Test2()
{
	if (izq && mov) //
	{
		posEnemy.x -= 3;

		if (map->collisionMoveLeftPlayer(posEnemy, glm::ivec2(10, 4)))
		{
			auch = true;
		}
	}
	else if (!izq && mov)//
	{
		posEnemy.x += 3;

		if (map->collisionMoveRightPlayer(posEnemy, glm::ivec2(10, 4)))
		{
			auch = true;
		}
	}
	else
		mov = true;
}

void Enemy::Test()
{
	if (izqTest) //
	{
		posEnemy.x -= 3;
		izqTest = false;

	}
	else if (!izqTest)//
	{
		posEnemy.x += 3;
		izqTest = true;
	}

}

void Enemy::updateArcher(int deltaTime)
{
	if (izq)
	{
		if (dispara)
		{
			if (sprite->animation() != A_SHOOT_LEFT) timeArquero += deltaTime;

			if (timeArquero >= 750 && sprite->animation() != A_SHOOT_LEFT)
			{
				sprite->changeAnimation(A_SHOOT_LEFT);
				cooldown = true;
				tiro = true;
			}
		}

		else
		{
			timeArquero = 0;
			if (sprite->animation() == A_SHOOT_LEFT && sprite->getcurrentKeyframe() == 3) sprite->changeAnimation(A_STAND_LEFT);
			dispara = false;
		}
	}
	else
	{
		if (dispara)
		{
			if (sprite->animation() != A_SHOOT_RIGHT) timeArquero += deltaTime;

			if (timeArquero >= 750 && sprite->animation() != A_SHOOT_RIGHT)
			{
				sprite->changeAnimation(A_SHOOT_RIGHT);
				cooldown = true;
				tiro = true;
			}
		}

		else
		{
			timeArquero = 0;
			if (sprite->animation() == A_SHOOT_RIGHT && sprite->getcurrentKeyframe() == 3) sprite->changeAnimation(A_STAND_RIGHT);
			dispara = false;
		}
	}

	
	
	if (sprite->animation() != A_SHOOT_LEFT && sprite->animation() != A_SHOOT_RIGHT)
	{
		if (izq && mov) //
		{

			if (sprite->animation() != A_MOVE_LEFT)
				sprite->changeAnimation(A_MOVE_LEFT);
			posEnemy.x -= 1;

			if (map->collisionMoveLeftEnemy(posEnemy, glm::ivec2(32, 32)))
			{
				posEnemy.x += 1;
				izq = false;
				mov = false;
			}
		}
		else if (!izq && mov)//
		{
			if (sprite->animation() != A_MOVE_RIGHT)
				sprite->changeAnimation(A_MOVE_RIGHT);
			posEnemy.x += 1;

			if (map->collisionMoveRightEnemy(posEnemy, glm::ivec2(32, 32)))
			{
				posEnemy.x -= 1;
				izq = true;
				mov = false;
			}
		}
		else
			mov = true;
	}
}

void Enemy::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int EnemyType)
{

	this->EnemyType = EnemyType;
	if (EnemyType == Vampiro)
	{
		float a = 1.f / 16.f;
		spritesheet.loadFromFile("images/Vampire.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(54, 40), glm::vec2(a, 0.25), &spritesheet, &shaderProgram);
		// 54 x 36
		Shprogram = shaderProgram;
		creaVampire();

		EnemyTileSizeBat = glm::ivec2(28, 21);
		EnemyTileSize = glm::ivec2(33, 40);
		posVamp = glm::ivec2(13, 0);
		posBat = glm::ivec2(10, 6);
	}
	else if (EnemyType == Esqueleto)
	{
		spritesheet.loadFromFile("images/skeleton.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(32, 40), glm::vec2(0.125, 0.50), &spritesheet, &shaderProgram);
		creaSkeleton();
		EnemyTileSize = glm::ivec2(19, 40);
		x_Real = 7;
	}

	else if (EnemyType == Bala)
	{
		spritesheet.loadFromFile("images/Bala.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1.0, 1.00), &spritesheet, &shaderProgram);
		creaBala();
		EnemyTileSize = glm::ivec2(10, 4);
	}

	else if (EnemyType == Arquero)
	{
		spritesheet.loadFromFile("images/archerattack-export.png", TEXTURE_PIXEL_FORMAT_RGBA);
		spritesheet.setMagFilter(GL_NEAREST);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
		creaArcher();
		EnemyTileSize = glm::ivec2(32, 32);
	}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + (posEnemy.y))));

}

void Enemy::update(int deltaTime, bool stoped)
{
	if (!stoped)
	{
		sprite->update(deltaTime);
		izqTest = izq;
	}

	if (EnemyType == Vampiro)
	{
		if (!stoped)
		{
			updateVampire(deltaTime);
			if (!Music::instance().SongEnded("media/transformation.mp3")) Music::instance().setGeneralSound(1.0);
		}
		else
			Test();
	}
	else if (EnemyType == Esqueleto)
	{
		if (!stoped) updateSkeleton();
		else 
			Test();
	}
	else if (EnemyType == Bala)
	{
		if (!stoped) Test2();
		else
			Test();
	}

	else if (EnemyType == Arquero)
	{
		if (!stoped)
		{
			if (!cooldown)
				updateArcher(deltaTime);
			else
			{
				timeCooldown += deltaTime;
				tiro = false;
				if (((sprite->animation() == A_SHOOT_LEFT || sprite->animation() == A_SHOOT_RIGHT) && sprite->getcurrentKeyframe() == 3))
					if (izq) sprite->changeAnimation(A_STAND_LEFT);
					else sprite->changeAnimation(A_STAND_RIGHT);
				
				if (timeCooldown >= 1250)
				{
					cooldown = false;
					timeCooldown = 0.0;
				}
			}
		}
		else
			Test(); 
	}

	if (EnemyType != Bala) sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	else
	{
		if (izq) sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y + 6)));
		else sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x + 7), float(tileMapDispl.y + posEnemy.y + 6)));
	}
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	if (EnemyType != Bala) sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	else
	{
		if (izq) sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y + 6)));
		else sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x + 7), float(tileMapDispl.y + posEnemy.y + 6)));
	}
}

glm::ivec2 Enemy::getPosition()
{
	return posEnemy;
}

void Enemy::setTileSize(int tilesize)
{
	tileSize = tilesize;
}

bool Enemy::detectPlayer(const glm::ivec2& pos, const glm::ivec2& size)
{
	int xB;
	if (EnemyType == Bala && !izq)  xB = 0;
	else if (EnemyType == Bala && izq) xB = 15;
	else xB = 0;
	int xP1, xE1, yP1, yE1, xP2, yP2, xE2, yE2;

	xP1 = pos.x / tileSize;
	yP1 = pos.y / tileSize;
	xP2 = (pos.x + size.x - 1) / tileSize;
	yP2 = (pos.y + size.y - 1) / tileSize;

	xE1 = (posEnemy.x+xB + x_Real) / tileSize;
	yE1 = (posEnemy.y + y_Real) / tileSize;
	xE2 = ((posEnemy.x + xB + x_Real) + EnemyTileSize.x - 1) / tileSize;
	yE2 = ((posEnemy.y + y_Real) + EnemyTileSize.y - 1) / tileSize;


	if (EnemyType == Arquero)
	{
		if (yP1 == yE1) check_disparo(yP1, yP2, yE1, yE2, xP1, xP2, xE1, xE2);

		else if (yP2 == yE1) check_disparo(yP1, yP2, yE1, yE2, xP1, xP2, xE1, xE2);

		else if (yP1 == yE2) check_disparo(yP1, yP2, yE1, yE2, xP1, xP2, xE1, xE2);

		else if (yP2 == yE2) check_disparo(yP1, yP2, yE1, yE2, xP1, xP2, xE1, xE2);

		else
			dispara = false;
	}

	for (int x = xP1; x <= xP2; ++x)
	{
		for (int y = yP1; y <= yP2; y++)
		{
			
			if (x == xE1 && y == yE1) return true;

			if (x == xE1 && y == yE2) return true;

			if (x == xE2 && y == yE1) return true;

			if (x == xE2 && y == yE2) return true;

		}
	}
	
	return false;
}

bool Enemy::check_disparo(int yP1, int yP2, int yE1, int yE2, int xP1, int xP2, int xE1, int xE2)
{
	if (izq)
	{
		for (int x = xE1; x >= 2; --x)
		{
			int currentTile1 = map->getTile(x, yE1);
			int currentTile2 = map->getTile(x, yE2);

			if (currentTile1 <= int('l') - int('0') && currentTile1 != 0)
			{
				if (EnemyType == Arquero) dispara = false;
				return false;
			}
			else if (currentTile2 <= int('l') - int('0') && currentTile2 != 0)
			{
				if (EnemyType == Arquero)dispara = false;
				return false;
			}
			if (x == xP2)
			{
				if (EnemyType == Arquero)dispara = true;
			   return true;
			}
		}
	}
	else
	{
		for (int x = xE1; x <= 540; ++x)
		{
			int currentTile1 = map->getTile(x, yE1);
			int currentTile2 = map->getTile(x, yE2);

			if (currentTile1 <= int('l') - int('0') && currentTile1 != 0)
			{
				if (EnemyType == Arquero) dispara = false;
				return false;
			}
			else if (currentTile2 <= int('l') - int('0') && currentTile2 != 0)
			{
				if (EnemyType == Arquero)dispara = false;
				return false;
			}
			if (x == xP2)
			{
				if (EnemyType == Arquero)dispara = true;
				return true;
			}
		}
	}
	if (EnemyType == Arquero) dispara = false;
	return false;
}

int Enemy::isArcher()
{
	return EnemyType;
}

bool Enemy::createDisparo()
{
	if (dispara && tiro) return true;
	return false;
}

void Enemy::setDireccion(bool iz)
{
	izq = iz;
}

bool Enemy::getDireccion()
{
	return izq;
}

bool Enemy::check_Bala_colision()
{
	
	return auch;
}

