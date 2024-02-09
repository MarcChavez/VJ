#include <iostream>
#include <cmath>
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 100
#define SCREEN_Y 100

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 18


enum Enemies
{
	Esqueleto, Vampiro, Arquero, Bala
};

enum Objects
{
	Puerta, Llave, Reloj, Gema, Cronometro
};

enum PortalAnimation
{
	Cerrado, Abierto, Abriendose
 };

enum UI
{
	S, T, A, G, E, X, V
};

Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemy = NULL;
	nEnemies = 0;
	currentTime = 0;
}

Scene::~Scene()
{
	if (player != NULL)
	{

		delete player;
		player = NULL;
	}
	if (enemy != NULL)
	{
		delete enemy;
		enemy = NULL;
	}
		
	for (int i = 0; i < EnemiesObj.size(); i++) {
		delete EnemiesObj[i];
		EnemiesObj[i] = NULL;
	}
	for (int i = 0; i < ObjectsObj.size(); i++) {
		delete ObjectsObj[i];
		//ObjectsObj[i] = NULL;
	}

	if (SpriteUIFont != NULL)
	{
		delete SpriteUIFont;
		SpriteUIFont = NULL;
	}

	if (AllSprites != NULL)
	{
		delete AllSprites;
		AllSprites = NULL;
	}

	if (SpriteUICor != NULL)
	{
		delete SpriteUICor;
		SpriteUICor = NULL;
	}

	if (SpriteUIMoney != NULL)
	{
		delete SpriteUIMoney;
		SpriteUIMoney = NULL;
	}
}

void Scene::init(int lvl, int vidas, int puntuacion, ShaderProgram& texProgram)
{
	this->texProgram = texProgram;
	string levelA = "levels/level0";
	this->lvl = lvl;
	levelA += std::to_string(lvl);
	levelA += ".txt";
	map = TileMap::createTileMap(levelA, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	glm::ivec2 posDoor = map->GetDoorPosition();

	this->puntos = puntuacion;
	this->vidas = vidas;
	
	spritesheetFondo.loadFromFile("images/Background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetFondo.setMagFilter(GL_NEAREST);
	SpriteUIFondo = Sprite::createSprite(glm::ivec2(640, 440), glm::vec2(1.0, 1.0), &spritesheetFondo, &texProgram);
	SpriteUIFondo->setNumberAnimations(1);

	SpriteUIFondo->setAnimationSpeed(0, 8);
	SpriteUIFondo->addKeyframe(0, glm::vec2(float(0.0), 0.f));

	SpriteUIFondo->setPosition(glm::ivec2(SCREEN_X, SCREEN_Y));

	nEnemies = map->GetNumEnemies();


	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()+8));
	player->setTileMap(map);
	for (int i = 0; i < nEnemies; ++i)
	{
		EnemiesObj.push_back(new Enemy());
	}

	for (int i = 0; i < nEnemies; ++i)
	{
		pair<int, glm::ivec2> enemydata = map->getEnemyData(i);
		EnemiesObj[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, enemydata.first);
		if (enemydata.first == Arquero) EnemiesObj[i]->setPosition(glm::vec2(enemydata.second.x, enemydata.second.y+8));
		else EnemiesObj[i]->setPosition(glm::vec2(enemydata.second.x, enemydata.second.y));		
		EnemiesObj[i]->setTileMap(map);
		EnemiesObj[i]->setTileSize(map->getTileSize());
	}

	ObjectsObj.push_back(new Object());

	ObjectsObj[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Puerta);
	ObjectsObj[0]->setPosition(posDoor);
	ObjectsObj[0]->setTileMap(map);
	

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	gameTime = 0.0f;
	setUI();

	map->prepareBaldosa();

	Music::instance().MainGameSong();
}

void Scene::update(int deltaTime)
{	
	map->updateBaldosa();
	if (desaparece)
	{
		Game::instance().dontShowIns(false);

		if (Music::instance().SongEnded("media/win.mp3") || !acaboCancion)
		{
			acaboCancion = true;
		}
		else if (player->lastFrame())
		{
			cuenta_puntos = true;

			contador += deltaTime;

			if (gameTime >= 60000)
			{
				if (int(contador) / 1000 >= 1)
				{
					Game::instance().setPuntuacion(puntos + num_gemas * 1000);
					Game::instance().setVida(vidas);
					Game::instance().setLevel();
				}	

			}

			else if (int(contador) >= 150)
			{
				puntos += 10;
				if (int(gameTime/1000)%3 == 0) Music::instance().playPointSound();
				contador = 0.0;
				gameTime += 1000;
			}
			
			
		}
		else
		{
			if (player->getInmortal()) player->updateShiny(deltaTime, 2);
			else player->update(deltaTime, 2);

			if (!Music::instance().SongEnded("media/teleport.mp3") && player->isTp())
			{
				Music::instance().playTPSound();
				
			}
		}
		
	}

	
	else if (start)
	{
		currentTime += deltaTime;
		Game::instance().dontShowIns(true);
		Game::instance().dontShowIns(true);



		if (itGem != NULL) timeGem += deltaTime;
		if (itWatch != NULL) timeWatch += deltaTime;
		if (itChrono != NULL) timeChronoD += deltaTime;

		if (timeGem >= 7500 && itGem != NULL)
		{
			BorraObjeto(itGem);
		}
		if (timeWatch >= 7500 && itWatch != NULL)
		{
			BorraObjeto(itWatch);
		}
		if (timeChronoD >= 7500 && itChrono != NULL)
		{
			BorraObjeto(itChrono);
		}

		if ((gameTime/1000) >= 60 && !cuenta_puntos)
		{
			if (player->estasMuelto())
			{
				Music::instance().playdeathSound();
				--vidas;
			}
			gameTime = 0.f;
		}

		if (!stop) gameTime += deltaTime;

		if ((int(gameTime / 1000) % 20 == 0) && !obje && !test && int(gameTime / 1000) != 0)
		{
			tiraDado();
		}
		else if (int(gameTime / 1000) % 20 != 0)
			obje = false;

		if (stop)
		{
			if (currentTime - timeChrono >= 3000 && stopfirst)
			{
				stopfirst = false;
			}
			else if (currentTime - timeChrono < 4000 && (currentTime - timeChrono > 3000))
			{
				stopsemi = true;
			}

			else if (currentTime - timeChrono >= 4000)
			{
				stopsemi = false;
				stop = false;
				Music::instance().StopResumeMainSong(false);
			}
		}

		cheatsOn(Game::instance().getKey(71), Game::instance().getKey(75), deltaTime);

		if (Game::instance().getKey(72) && !test) //H -> Watch
		{
			CreaWatch();
			test = true;
		}

		if (Game::instance().getKey(77) && !test) //M -> Gema
		{
			CreaGema();
			test = true;
		}

		if (Game::instance().getKey(67) && !test) //C -> Chrono
		{
			CreaChrono();
			test = true;
		}

		int obpl = player->ObjectTaken();

		if (obpl != -1)
			if (TractaObjecte(obpl)) return;
	
		if (portalani && ObjectsObj[0]->keyFrame() == 11)
		{
			ObjectsObj[0]->changeAni(Abierto);
			salida = true;
			portalani = false;
		}

		if ((!llaveSpawned && map->getNumFloorActivated() == 0) || (llaveCheat))
			CreaKey();
	
		if (player->getInmortal()) player->updateShiny(deltaTime, 0);
		else player->update(deltaTime, 0);
		if (map->getNewFloor())
		{
			//Sonido Suelo
		}
			
		glm::ivec2 pp = player->getposReal();
		if (map->collisionSpikeDown(pp, player->getTileReal(), &pp.y))
		{
			if (player->estasMuelto())
			{
				Music::instance().playdeathSound();
				--vidas;
			}
				
		}

		if (!stop || (stopsemi && (int(currentTime)%3 == 0))) //Vibraçao
		{
			for (int i = 0; i < nEnemies; ++i)
			{
				if (EnemiesObj[i] != NULL)
				{
					EnemiesObj[i]->update(deltaTime, stopsemi);

					if (EnemiesObj[i]->isArcher() == Arquero)
					{
						if (EnemiesObj[i]->createDisparo())
						{
							Enemy* e = new Enemy();
							e->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Bala);
							glm::ivec2 pos = EnemiesObj[i]->getPosition();
							e->setPosition(glm::vec2(pos.x, pos.y));
							e->setTileMap(map);
							e->setTileSize(map->getTileSize());
							e->setDireccion(EnemiesObj[i]->getDireccion());
							EnemiesObj.push_back(e);
							nEnemies++;
							if (!Music::instance().SongEnded("media/starwars.mp3"))
							{
								Music::instance().playShootSound();
							}
						}
					}

					if (EnemiesObj[i]->detectPlayer(player->getposReal(), player->getTileReal()))
					{
						if (player->estasMuelto())
						{
							--vidas;
							Music::instance().playdeathSound();
						}
					
						if (EnemiesObj[i]->isArcher() == Bala)
						{
							delete EnemiesObj[i]; // erase(ObjectsObj.begin() + itKey);
							EnemiesObj[i] = NULL;
						}
					}
					if (EnemiesObj[i] != NULL && EnemiesObj[i]->isArcher() == Bala && EnemiesObj[i]->check_Bala_colision())
					{
						delete EnemiesObj[i]; // erase(ObjectsObj.begin() + itKey);
						EnemiesObj[i] = NULL;
					}
				}
			}
		}

		for (int i = 0; i < ObjectsObj.size(); ++i)
		{
			if (ObjectsObj[i] != NULL) ObjectsObj[i]->update(deltaTime);
		}


		if (vidas == 0 && player->lastFrame())
		{
			Game::instance().setVida(vidas);
			return;
		}

		int puntosant = player->getPuntos();
		if (puntosant != 0)
		{
			puntos += puntosant;
			Music::instance().playPointSound();
		}
	}

	else
	{
		Game::instance().dontShowIns(false);
		contador2 += deltaTime;
		
		if (player->lastFrame())
		{
			start = true;
		}
		if (contador2 > 1000)
		{
			Music::instance().playTPSound();
			aparece = true;
			if (player->getInmortal()) player->updateShiny(deltaTime, 1);
			else player->update(deltaTime, 1);
		}
		
	}
}

void Scene::render()
{
	SpriteUIFondo->render();
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	for (int i = 0; i < ObjectsObj.size(); ++i)
	{
		if (ObjectsObj[i] != NULL) ObjectsObj[i]->render();
	}

	if (!cuenta_puntos && aparece) player->render();
	

	for (int i = 0; i < nEnemies; ++i)
	{
		if (EnemiesObj[i] != NULL) EnemiesObj[i]->render();
	}
	
	ImprimeUI();
	
	//SpriteCartel->render();
	
}

void Scene::cheatsOn(bool inmortal, bool keyspawn, int deltaTime)
{
	if (aparece)
	{
		if (inmortal && !keyCheat)
		{
			player->setInmortality();
			player->cargaSprite(deltaTime);
			keyCheat = true;
		}
		else if (!inmortal)
			keyCheat = false;

		if (!llaveSpawned && keyspawn)
		{
			llaveCheat = true;
		}
		
	}
}

bool Scene::TractaObjecte(int obpl)
{
	if (obpl == Llave)
	{
		ObjectsObj[0]->changeAni(Abriendose);
		timePortal = currentTime;
		portalani = true;
		map->borrarObj(ObjectsObj[itKey]->getPosition());
		Music::instance().keySound();
		delete ObjectsObj[itKey]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itKey] = NULL;
	}
	else if (obpl == Gema)
	{
		puntos += 1000;
		map->borrarObj(ObjectsObj[itGem]->getPosition());
		delete ObjectsObj[itGem]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itGem] = NULL;
		itGem = NULL;	
		Music::instance().playCoin();
		
	}
	else if (obpl == Reloj)
	{
		gameTime = 0.f;
		map->borrarObj(ObjectsObj[itWatch]->getPosition());
		delete ObjectsObj[itWatch]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itWatch] = NULL;
		itWatch = NULL;
		Music::instance().playWatchSound();
	}
	else if (obpl == Cronometro)
	{
		ObjectsObj[itChrono]->changeAni(Abriendose);
		stop = true;
		stopfirst = true;
		timeChrono = currentTime;
		map->borrarObj(ObjectsObj[itChrono]->getPosition());
		delete ObjectsObj[itChrono]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itChrono] = NULL;
		itChrono = NULL;
		Music::instance().StopResumeMainSong(true);
		Music::instance().playstopTimeSound();
	}
	else if (obpl == Puerta && salida)
	{
		desaparece = true;
		Music::instance().stopAll();
		Music::instance().playWinSong();
		//player->setPosition(map->getPosPortal());
	}
	test = false;
	return false;
}

void Scene::CreaWatch()
{
	ObjectsObj.push_back(new Object());
	itWatch = ObjectsObj.size() - 1;
	ObjectsObj[itWatch]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Reloj);
	glm::ivec2 randompos = map->getRandomPosi(player->getposReal());
	ObjectsObj[itWatch]->setPosition(randompos);
	ObjectsObj[itWatch]->setTileMap(map);
	map->SetObject(glm::ivec2(((randompos.x / map->getTileSize())), (randompos.y / map->getTileSize())), Reloj);
	test = true;
}

void Scene::CreaKey()
{
	llaveSpawned = true;
	llaveCheat = false;
	ObjectsObj.push_back(new Object());
	itKey = ObjectsObj.size() - 1;
	ObjectsObj[itKey]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Llave);
	ObjectsObj[itKey]->setTileMap(map);
	ObjectsObj[itKey]->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES+1) * map->getTileSize()));
	ObjectsObj[itKey]->setTileMap(map);
	map->SetObject(glm::ivec2(INIT_PLAYER_X_TILES, INIT_PLAYER_Y_TILES+1), Llave);
}

void Scene::CreaGema()
{
	ObjectsObj.push_back(new Object());
	itGem = ObjectsObj.size() - 1;
	ObjectsObj[itGem]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Gema);
	glm::ivec2 randompos = map->getRandomPosi(player->getposReal());
	ObjectsObj[itGem]->setPosition(randompos);
	ObjectsObj[itGem]->setTileMap(map);
	map->SetObject(glm::ivec2(((randompos.x / map->getTileSize())), (randompos.y / map->getTileSize())), Gema);
	test = true;
}

void Scene::CreaChrono()
{
	ObjectsObj.push_back(new Object());
	itChrono = ObjectsObj.size() - 1;
	ObjectsObj[itChrono]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, Cronometro);
	glm::ivec2 randompos = map->getRandomPosi(player->getposReal());
	ObjectsObj[itChrono]->setPosition(randompos);
	ObjectsObj[itChrono]->setTileMap(map);
	map->SetObject(glm::ivec2(((randompos.x/ map->getTileSize())), (randompos.y / map->getTileSize())), Cronometro);
	test = true;
}

void Scene::ImprimeUI()
{
	int time = 60 - (int(gameTime) / 1000);
	int d1 = int(time) % 10;
	int d2 = int(time) / 10;

	SpriteUIFont->changeAnimation(S);
	SpriteUIFont->setPosition(AllSprites[S]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(T);
	SpriteUIFont->setPosition(AllSprites[T]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(A);
	SpriteUIFont->setPosition(AllSprites[A]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(G);
	SpriteUIFont->setPosition(AllSprites[G]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(E);
	SpriteUIFont->setPosition(AllSprites[E]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(X);
	SpriteUIFont->setPosition(AllSprites[X]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + 0);
	SpriteUIFont->setPosition(AllSprites[V + 3]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + lvl);
	SpriteUIFont->setPosition(AllSprites[V + 4]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + d1);
	SpriteUIFont->setPosition(AllSprites[V + 2]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + d2);
	SpriteUIFont->setPosition(AllSprites[V + 1]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + vidas);
	SpriteUIFont->setPosition(AllSprites[V + 0]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + puntos / 1000000);
	SpriteUIFont->setPosition(AllSprites[V + 6]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + (puntos/10000)%10);
	SpriteUIFont->setPosition(AllSprites[V + 7]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + (puntos / 1000) % 10);
	SpriteUIFont->setPosition(AllSprites[V + 8]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + (puntos / 100) % 10);
	SpriteUIFont->setPosition(AllSprites[V + 9]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + (puntos / 10) % 10);
	SpriteUIFont->setPosition(AllSprites[V + 10]);
	SpriteUIFont->render();

	SpriteUIFont->changeAnimation(V + puntos % 10);
	SpriteUIFont->setPosition(AllSprites[V + 11]);
	SpriteUIFont->render();

	int p = (int(puntos / 1000) % 10);

	if (p % 3 == 0)
	{
		if (p != puntoVida)
		{
			puntoVida = p;
			++vidas;
		}
	}

	/*SpriteUIFont->changeAnimation(X);
	SpriteUIFont->setPosition(AllSprites[V + 13]);
	SpriteUIFont->render();*/

	

	SpriteUICor->render();
	//SpriteUIMoney->render();



}

void Scene::setUI()
{

	AllSprites = new glm::ivec2[20];

	spritesheetFont.loadFromFile("images/FONT3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetFont.setMagFilter(GL_NEAREST);

	spritesheetCor.loadFromFile("images/heart-1.png.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetCor.setMagFilter(GL_NEAREST);

	spritesheetMoney.loadFromFile("images/crypto.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetMoney.setMagFilter(GL_NEAREST);

	SpriteUIFont = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.25), &spritesheetFont, &texProgram); //TIME_IZ

	SpriteUIMoney = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1, 1), &spritesheetMoney, &texProgram); //	<3			9
	SpriteUIMoney->setNumberAnimations(1);
	SpriteUIMoney->addKeyframe(0, glm::vec2(1, 1.));
	SpriteUIMoney->setPosition(glm::vec2(9 * (20), 3 * 20));

	SpriteUICor = (Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1, 1), &spritesheetCor, &texProgram)); //	<3			9
	SpriteUICor->setNumberAnimations(1);
	SpriteUICor->addKeyframe(0, glm::vec2(1, 1.));
	//SpriteUI.push_back(Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.0625, 0.25), &spritesheetMoney, &texProgram)); //LVL_DERE	10

	SpriteUIFont->setNumberAnimations(16);

	SpriteUIFont->setAnimationSpeed(S, 8);
	SpriteUIFont->addKeyframe(S, glm::vec2(12 * (0.0625f), 0.25));
	AllSprites[S] = glm::vec2(float(29 * 20), float(3 * 20));

	SpriteUIFont->setAnimationSpeed(T, 8);
	SpriteUIFont->addKeyframe(T, glm::vec2(13 * (0.0625f), 0.25));
	AllSprites[T] =  glm::vec2(30 * (20), float(3 * 20));

	SpriteUIFont->setAnimationSpeed(A, 8);
	SpriteUIFont->addKeyframe(A, glm::vec2(10 * (0.0625f), 0.0));
	AllSprites[A] = glm::vec2(31 * (20), float(3 * 20));

	SpriteUIFont->setAnimationSpeed(G, 8);
	SpriteUIFont->addKeyframe(G, glm::vec2(0 * (0.0625f), 0.25));
	AllSprites[G] = (glm::vec2(float(32 * 20), float(3 * 20)));

	SpriteUIFont->setAnimationSpeed(E, 8);
	SpriteUIFont->addKeyframe(E, glm::vec2(14 * (0.0625f), 0.00));
	AllSprites[E] = glm::vec2(33 * (20), float(3 * 20));

	SpriteUIFont->setAnimationSpeed(X, 8);
	SpriteUIFont->addKeyframe(X, glm::vec2(1 * (0.0625f), 0.5));
	AllSprites[X] = glm::vec2(6 * (20), float(3 * 20));

	
	for (int i = 0; i <= 9; ++i)
	{
		SpriteUIFont->addKeyframe(i+V, glm::vec2(0.0625f * i, 0.));

	}

	SpriteUICor->setPosition(glm::vec2(5 * (20), 3 * 20));

	AllSprites[V + 0] = glm::vec2(7 * (20), 3*20);
	AllSprites[V + 1] = glm::vec2(20 * (20), 3 * 20);
	AllSprites[V + 2] = glm::vec2(21 * (20), 3 * 20);
	AllSprites[V + 3] = glm::vec2(35 * (20), 3 * 20);
	AllSprites[V + 4] = glm::vec2(36 * (20), 3 * 20);
	AllSprites[V + 5] = glm::vec2(3 * (20), 3 * 20);

	AllSprites[V + 13] = glm::vec2(10 * (20), 3 * 20);
	AllSprites[V + 6] = glm::vec2(11 * (20), 3 * 20);
	AllSprites[V + 7] = glm::vec2(12 * (20), 3 * 20);
	AllSprites[V + 8] = glm::vec2(13 * (20), 3 * 20);
	AllSprites[V + 9] = glm::vec2(14 * (20), 3 * 20);
	AllSprites[V + 10] = glm::vec2(15 * (20), 3 * 20);
	AllSprites[V + 11] = glm::vec2(16 * (20), 3 * 20);


}

void Scene::tiraDado()
{
	srand(time(NULL));
	int pos = rand() % 100;
	obje = true;
	if (!chrono && !reloj)
	{
		if (pos >= 40 && pos < 80) if (itGem != NULL) CreaGema();
		else if (pos >= 80 && pos < 90)
		{
			if (itChrono != NULL) CreaChrono();
			chrono = true;
		}
		else if (pos >= 90)
		{
			if (itWatch != NULL) CreaWatch();
			reloj = true;
		}
	}
	else if (!chrono && reloj)
	{
		if (pos >= 40 && pos < 90) if (itGem != NULL) CreaGema();
		else if (pos >= 90)
		{
			if (itChrono != NULL) CreaChrono();
			chrono = true;
		}
	}
	else if (chrono && !reloj)
	{
		if (pos >= 40 && pos < 90) if (itGem != NULL) CreaGema();
		else if (pos >= 90)
		{
			if (itWatch != NULL) CreaWatch();
			reloj = true;
		}
	}
	else
	{
		if (pos >= 40) if (itGem != NULL) CreaGema();

	}

}

void Scene::BorraObjeto(int object)
{
	if (object == itGem)
	{
		map->borrarObj(ObjectsObj[itGem]->getPosition());
		delete ObjectsObj[itGem]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itGem] = NULL;
		itGem = NULL;
	}
	else if (object == itWatch)
	{
		map->borrarObj(ObjectsObj[itWatch]->getPosition());
		delete ObjectsObj[itWatch]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itWatch] = NULL;
		itWatch = NULL;
	}
	else if (object == itChrono)
	{
		ObjectsObj[itChrono]->changeAni(Abriendose);
		map->borrarObj(ObjectsObj[itChrono]->getPosition());
		delete ObjectsObj[itChrono]; // erase(ObjectsObj.begin() + itKey);
		ObjectsObj[itChrono] = NULL;
		itChrono = NULL;
	}
	test = false;
}

void Scene::changeWindow(int w, int h)
{
	float windowRatio = w / float(h);
	float scale = 1.f;
	if (windowRatio > 32.0 / 22.0)
	{
		scale = h / 540.0f;
		float offset = (w - 840 * scale) / 2;
		projection = glm::ortho(-offset, float(w) - offset, float(h), 0.f);
	}
	else
	{
		scale = w / 840.0f;
		float offset = (h - 540 * scale) / 2;
		projection = glm::ortho(0.f, float(w) , float(h) - offset, -offset);
	}

	projection = glm::scale(projection, glm::vec3(scale));
}



