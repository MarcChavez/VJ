#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 70
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, STAND_FRONT, DEAD, APARECE, DESAPARECE, 
	STAND_LEFT_SHINY, STAND_RIGHT_SHINY, MOVE_LEFT_SHINY, MOVE_RIGHT_SHINY, STAND_FRONT_SHINY, APARECE_SHINY, DESAPARECE_SHINY, DEAD_SHINY
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;

	spritesheet.loadFromFile("images/Zou.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	float width = 1.f / 3.f;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	PlayerTileSize = glm::ivec2(18, 32);
	posPlayerReal_x_L = glm::ivec2(6, 0);
	posPlayerReal_x_R = glm::ivec2(5, 0);
	sprite->setNumberAnimations(15);

	cargaSpriteShiny();
	cargaSpriteNormal();


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::cargaSpriteShiny()
{
	sprite->setAnimationSpeed(STAND_LEFT_SHINY, 8);
	sprite->addKeyframe(STAND_LEFT_SHINY, glm::vec2(0.625, 0.375));

	sprite->setAnimationSpeed(STAND_RIGHT_SHINY, 8);
	sprite->addKeyframe(STAND_RIGHT_SHINY, glm::vec2(0.125, 0.5));

	sprite->setAnimationSpeed(MOVE_LEFT_SHINY, 8);
	sprite->addKeyframe(MOVE_LEFT_SHINY, glm::vec2(0.5f, 0.375));
	sprite->addKeyframe(MOVE_LEFT_SHINY, glm::vec2(0.625, 0.375));
	sprite->addKeyframe(MOVE_LEFT_SHINY, glm::vec2(0.75, 0.375));


	sprite->setAnimationSpeed(MOVE_RIGHT_SHINY, 8);
	sprite->addKeyframe(MOVE_RIGHT_SHINY, glm::vec2(0.f, 0.5));
	sprite->addKeyframe(MOVE_RIGHT_SHINY, glm::vec2(0.125, 0.5));
	sprite->addKeyframe(MOVE_RIGHT_SHINY, glm::vec2(0.25, 0.5));

	sprite->setAnimationSpeed(STAND_FRONT_SHINY, 8);
	sprite->addKeyframe(STAND_FRONT_SHINY, glm::vec2(0.125, 0.375));

	sprite->setAnimationSpeed(DEAD_SHINY, 8);
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.125, 0.375));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.5, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.6725, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.75, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD_SHINY, glm::vec2(0.875, 0.125));

	sprite->setAnimationSpeed(APARECE_SHINY, 4);
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.0, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.125, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.25, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.375, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.5, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.625, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.75, 0.625));
	sprite->addKeyframe(APARECE_SHINY, glm::vec2(0.875, 0.625));

	sprite->setAnimationSpeed(DESAPARECE_SHINY, 4);
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.875, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.75, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.625, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.5, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.375, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.25, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.125, 0.625));
	sprite->addKeyframe(DESAPARECE_SHINY, glm::vec2(0.0, 0.625));
}

void Player::cargaSpriteNormal()
{
	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.625, 0.0));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125, 0.125));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625, 0.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75, 0.0));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.125));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125, 0.125));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.125));

	sprite->setAnimationSpeed(STAND_FRONT, 8);
	sprite->addKeyframe(STAND_FRONT, glm::vec2(0.125, 0.0));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.125, 0.0));
	sprite->addKeyframe(DEAD, glm::vec2(0.5, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.6725, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.75, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.875, 0.125));
	sprite->addKeyframe(DEAD, glm::vec2(0.875, 0.125));

	sprite->setAnimationSpeed(APARECE, 4);
	sprite->addKeyframe(APARECE, glm::vec2(0.0, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.125, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.25, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.375, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.5, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.625, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.75, 0.25));
	sprite->addKeyframe(APARECE, glm::vec2(0.875, 0.25));

	sprite->setAnimationSpeed(DESAPARECE, 4);
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.875, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.75, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.625, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.5, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.375, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.25, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.125, 0.25));
	sprite->addKeyframe(DESAPARECE, glm::vec2(0.0, 0.25));
}

void Player::update(int deltaTime, int show)
{
	if (show == 0)
	{
		if (muelto && sprite->animation() == DEAD && sprite->getcurrentKeyframe() < 7) sprite->update(deltaTime);
		else if ((!muelto || yaesta != 1) && sprite->animation() != DEAD) sprite->update(deltaTime);

		if (sprite->animation() == APARECE) sprite->changeAnimation(STAND_FRONT);

		time2 += deltaTime;

		if (!bJumping && sprite->animation() == STAND_FRONT)
		{
			puntos += map->newFloorLeft(posPlayer, PlayerTileSize);
			Object = map->ObjectLeftPlayer(posPlayer, PlayerTileSize);
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && yaesta != 1 && !dontMove) //izq && mov
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;

			if (!bJumping) puntos += map->newFloorLeft(posPlayer + posPlayerReal_x_L, PlayerTileSize);

			if (map->collisionMoveLeftPlayer(posPlayer + posPlayerReal_x_L, PlayerTileSize) || map->collisionUp(posPlayer + posPlayerReal_x_L, PlayerTileSize))
			{
				posPlayer.x += 2;
				//sprite->changeAnimation(STAND_LEFT);
			}

		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && yaesta != 1 && !dontMove)//!izq && mov
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (!bJumping) puntos += map->newFloorRight(posPlayer + posPlayerReal_x_R, PlayerTileSize);

			if (map->collisionMoveRightPlayer(posPlayer + posPlayerReal_x_R, PlayerTileSize) || map->collisionUp(posPlayer + posPlayerReal_x_R, PlayerTileSize))
			{
				posPlayer.x -= 2;
				//sprite->changeAnimation(STAND_RIGHT);
			}

		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && yaesta != 1 && !dontMove)//!izq && mov
		{
			if (sprite->animation() != STAND_FRONT)
				sprite->changeAnimation(STAND_FRONT);
		}

		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);

			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);

			if (sprite->animation() == STAND_LEFT)
			{
				if (!bJumping)
				{
					puntos += map->newFloorLeft(posPlayer + posPlayerReal_x_L, PlayerTileSize);
				}
			}
			else if (sprite->animation() == STAND_RIGHT)
				if (!bJumping)
				{
					puntos += map->newFloorRight(posPlayer + posPlayerReal_x_R, PlayerTileSize);
				}
		}

		if ((sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT))
			Object = map->ObjectLeftPlayer(posPlayer + posPlayerReal_x_L, PlayerTileSize);

		else if ((sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT))
			Object = map->ObjectRightPlayer(posPlayer + posPlayerReal_x_R, PlayerTileSize);

		if (bJumping && yaesta != 1)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				int test = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
				glm::ivec2 testpos;
				if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
					testpos = glm::ivec2(posPlayer.x + posPlayerReal_x_L.x, test + 8);
				else
					testpos = glm::ivec2(posPlayer.x + posPlayerReal_x_R.x, test + 8);

				if (map->collisionUp(testpos, PlayerTileSize))
				{
					jumpAngle = 90 + (90 - jumpAngle);
				}
				else
					posPlayer.y = test;
				if (jumpAngle > 90)
					if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
						bJumping = !(map->baldosaDown(posPlayer, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y));
					else
						bJumping = !(map->baldosaDown(posPlayer, PlayerTileSize, &posPlayer.y) ||  map->collisionMoveDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y));
			}
		}

		else if (!bJumping && yaesta != 1)
		{
			posPlayer.y += FALL_STEP;
			if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT)
			{
				if (map->baldosaDown(posPlayer, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y))
				{
					if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
			}
			else
			{
				if (map->baldosaDown(posPlayer, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y))
				{
					if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
			}
		}

		if (time2 - time >= 3 * 1000 && muelto)
		{
			muelto = false;
			time = time2 = 0;
			yaesta = 0;
		}

		else if (time2 - time >= 2 * 1000 && time2 - time < 3 * 1000 && yaesta <= 1 && muelto)
		{
			yaesta = 2;
			posPlayer.y = (18 * 20) + 6;
			posPlayer.x = 4 * 20;
			sprite->changeAnimation(STAND_FRONT);
		}
	}
	else
	{
		if (show == 1)
		{
			if (sprite->animation() != APARECE)
				sprite->changeAnimation(APARECE);
		}
		else
			if (sprite->animation() != DESAPARECE)
				sprite->changeAnimation(DESAPARECE);


		sprite->update(deltaTime);
	}

	posPlayer.x += map->getMovPlayer();
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::updateShiny(int deltaTime, int show)
{
	if (show == 0)
	{
		if (muelto && sprite->animation() == DEAD_SHINY && sprite->getcurrentKeyframe() < 7) sprite->update(deltaTime);

		else if ((!muelto || yaesta != 1) && sprite->animation() != DEAD_SHINY) sprite->update(deltaTime);

		if (sprite->animation() == APARECE_SHINY) sprite->changeAnimation(STAND_FRONT_SHINY);
		
		if (!bJumping && sprite->animation() == STAND_FRONT_SHINY)
		{
			puntos += map->newFloorLeft(posPlayer, PlayerTileSize);
			Object = map->ObjectLeftPlayer(posPlayer, PlayerTileSize);
		}

		time2 += deltaTime;
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && yaesta != 1 && !dontMove) //izq && mov
		{
			if (sprite->animation() != MOVE_LEFT_SHINY)
				sprite->changeAnimation(MOVE_LEFT_SHINY);
			posPlayer.x -= 2;

			if (!bJumping) puntos += map->newFloorLeft(posPlayer + posPlayerReal_x_L, PlayerTileSize);


			if (map->collisionMoveLeftPlayer(posPlayer + posPlayerReal_x_L, PlayerTileSize) || map->collisionUp(posPlayer + posPlayerReal_x_L, PlayerTileSize))
			{
				posPlayer.x += 2;
				//sprite->changeAnimation(STAND_LEFT);
			}

		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && yaesta != 1 && !dontMove)//!izq && mov
		{
			if (sprite->animation() != MOVE_RIGHT_SHINY)
				sprite->changeAnimation(MOVE_RIGHT_SHINY);
			posPlayer.x += 2;
			if (!bJumping) puntos += map->newFloorRight(posPlayer + posPlayerReal_x_R, PlayerTileSize);

			if (map->collisionMoveRightPlayer(posPlayer + posPlayerReal_x_R, PlayerTileSize) || map->collisionUp(posPlayer + posPlayerReal_x_R, PlayerTileSize))
			{
				posPlayer.x -= 2;
				//sprite->changeAnimation(STAND_RIGHT);
			}

		}

		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && yaesta != 1 && !dontMove)//!izq && mov
		{
			if (sprite->animation() != STAND_FRONT_SHINY)
				sprite->changeAnimation(STAND_FRONT_SHINY);
		}

		else
		{
			if (sprite->animation() == MOVE_LEFT_SHINY)
				sprite->changeAnimation(STAND_LEFT_SHINY);

			else if (sprite->animation() == MOVE_RIGHT_SHINY)
				sprite->changeAnimation(STAND_RIGHT_SHINY);

			if (sprite->animation() == STAND_LEFT_SHINY)
			{
				if (!bJumping)
				{
					puntos += map->newFloorLeft(posPlayer+ posPlayerReal_x_L, PlayerTileSize);
				}
			}
			else if (sprite->animation() == STAND_RIGHT_SHINY)
				if (!bJumping)
				{
					puntos += map->newFloorRight(posPlayer + posPlayerReal_x_R, PlayerTileSize);
				}
		}

		if ((sprite->animation() == STAND_LEFT_SHINY || sprite->animation() == MOVE_LEFT_SHINY))
			Object = map->ObjectLeftPlayer(posPlayer+ posPlayerReal_x_L, PlayerTileSize);

		else if ((sprite->animation() == STAND_RIGHT_SHINY || sprite->animation() == MOVE_RIGHT_SHINY))
			Object = map->ObjectRightPlayer(posPlayer + posPlayerReal_x_R, PlayerTileSize);

		if (bJumping && yaesta != 1)
		{
			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				int test = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
				glm::ivec2 testpos;
				if (sprite->animation() == STAND_LEFT_SHINY || sprite->animation() == MOVE_LEFT_SHINY)
					testpos = glm::ivec2(posPlayer.x + posPlayerReal_x_L.x, test + 8);
				else
					testpos = glm::ivec2(posPlayer.x + posPlayerReal_x_R.x, test + 8);
				
				if (map->collisionUp(testpos, glm::vec2(PlayerTileSize.x, PlayerTileSize.y + 8)))
				{
					jumpAngle = 90 + (90 - jumpAngle);
				}
				else
					posPlayer.y = test;
				if (jumpAngle > 90)
					if (sprite->animation() == STAND_LEFT_SHINY || sprite->animation() == MOVE_LEFT_SHINY)
						bJumping = !(map->baldosaDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y));
					else
						bJumping = !(map->baldosaDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y));
			}
		}

		else if (!bJumping && yaesta != 1)
		{
			posPlayer.y += FALL_STEP;
			if (sprite->animation() == STAND_LEFT_SHINY || sprite->animation() == MOVE_LEFT_SHINY)
			{
				if (map->baldosaDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_L, PlayerTileSize, &posPlayer.y))
				{
					if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
			}
			else
			{
				if (map->baldosaDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y) || map->collisionMoveDown(posPlayer + posPlayerReal_x_R, PlayerTileSize, &posPlayer.y))
				{
					if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				}
			}
		}

		if (time2 - time >= 3 * 1000 && muelto)
		{
			muelto = false;
			time = time2 = 0;
			yaesta = 0;
		}

		else if (time2 - time >= 2 * 1000 && time2 - time < 3 * 1000 && yaesta <= 1 && muelto)
		{
			yaesta = 2;
			posPlayer.y = (18 * 20) + 6;
			posPlayer.x = 4 * 20;
			sprite->changeAnimation(STAND_FRONT_SHINY);
		}
	}
	else
	{
		if (show == 1)
		{
			if (sprite->animation() != APARECE_SHINY)
				sprite->changeAnimation(APARECE_SHINY);
		}
		else
			if (sprite->animation() != DESAPARECE_SHINY)
				sprite->changeAnimation(DESAPARECE_SHINY);


		sprite->update(deltaTime);
	}

	int x = map->getMovPlayer();

	posPlayer.x += x;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::render()
{
	if (muelto)
	{
		if (((time2 - time) / 200)%2 == 0) 
			sprite->render(); // 150 0 200
	} 

	if (!muelto) sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

int Player::ObjectTaken()
{
	int Obj_tmp = Object;
	Object = -1;
	return Obj_tmp;
}

void Player::setInmortality()
{
	inmortal = !inmortal;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition()
{
	return posPlayer;
}

bool Player::estasMuelto()
{
	if (!muelto && !inmortal)
	{
		time = time2 = 0;
		muelto = true;
		yaesta = 1;
		bJumping = false;
		if (inmortal) sprite->changeAnimation(DEAD_SHINY);
		else
			sprite->changeAnimation(DEAD);
		return true;

	}
	return false;
}

glm::ivec2 Player::getposReal()
{
	if (sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT_SHINY || sprite->animation() == MOVE_LEFT_SHINY)
		return posPlayer + posPlayerReal_x_L;
	else 
		return posPlayer + posPlayerReal_x_R;
}

int Player::getPuntos() {
	int p = puntos;
	puntos = 0;
	return p;
}

bool Player::lastFrame()
{
	bool a = false;
	if (sprite->animation() == APARECE || sprite->animation() == APARECE_SHINY) a = sprite->getcurrentKeyframe() == 7;
	else if (sprite->animation() == DESAPARECE || sprite->animation() == DESAPARECE_SHINY) a = sprite->getcurrentKeyframe() == 7;
	else if (sprite->animation() == DEAD || sprite->animation() == DEAD_SHINY) a = sprite->getcurrentKeyframe() == 7;
	return (a);
}

void Player::cargaSprite(int deltaTime)
{
	if (!inmortal)
	{
		if (sprite->animation() == STAND_LEFT_SHINY) sprite->changeAnimation(STAND_LEFT);

		else if (sprite->animation() == STAND_RIGHT_SHINY) sprite->changeAnimation(STAND_RIGHT);

		else if (sprite->animation() == MOVE_LEFT_SHINY) sprite->changeAnimation(MOVE_LEFT);

		else if (sprite->animation() == MOVE_RIGHT_SHINY) sprite->changeAnimation(MOVE_RIGHT);

		else if (sprite->animation() == STAND_FRONT_SHINY) sprite->changeAnimation(STAND_FRONT);


	}
	else
	{
		if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(STAND_LEFT_SHINY);

		else if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(STAND_RIGHT_SHINY);

		else if (sprite->animation() == MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT_SHINY);

		else if (sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT_SHINY);

		else if (sprite->animation() == STAND_FRONT) sprite->changeAnimation(STAND_FRONT_SHINY);
	}
	sprite->update(deltaTime);
	sprite->render();
}


