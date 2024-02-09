#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include <GL/glew.h>
#include <GL/glut.h>


using namespace std;


enum Enemies
{
	Esqueleto, Vampiro, Arquero
};

TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	minCoord = minCoords;
	SetDoor();
	Shprogram = program;

}

void TileMap::render()
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);


	if (baldosamov)
	{
	spriteBaldosaMov->setPosition(glm::vec2(BaldosaReal.x+100, BaldosaReal.y+120));
	spriteBaldosaMov->render();
	}
	

	if (haysuelo)
	{
		for (int j = 0; j < ActualFloorActivated; ++j)
		{
			spriteSuelo->setPosition(glm::vec2(float(100 + AllSprites[j].x), float(16 + AllSprites[j].y)));
			spriteSuelo->render();
		}
	}
}

void TileMap::updateBaldosa()
{
	if (baldosamov)
	{
		if (!movBaldosaIzq) ++BaldosaReal.x;
		else --BaldosaReal.x;

		if (BaldosaReal.x == BaldosaFinal.x && !movBaldosaIzq) movBaldosaIzq = !movBaldosaIzq;
		else if (BaldosaReal.x == BaldosaInicial.x && movBaldosaIzq) movBaldosaIzq = !movBaldosaIzq;
	}

}

int TileMap::getMovPlayer()
{
	if (!baldosamov) return 0;
	if (movPlayers)
	{
		if (movBaldosaIzq) return -1;
		else return 1;
	}
	else
		return 0;
}

bool TileMap::baldosaDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY)
{
	int x0, x1, y, xB0, xB1, yB;

	if (baldosamov)
	{
		x0 = pos.x / tileSize;
		x1 = (pos.x + size.x - 1) / tileSize;
		y = (pos.y + size.y - 1) / tileSize;

		xB0 = BaldosaReal.x / tileSize;
		xB1 = (BaldosaReal.x + 40 - 1) / tileSize;
		yB = BaldosaReal.y / tileSize;

			for (int x = x0; x <= x1; x++)
			{
				if (x >= xB0 && x <= xB1 && (y-1) == yB) //*posY - tileSize * y + size.y <= 4
				{
					*posY = tileSize * y - size.y;
					movPlayers = true;
					return true;
				}
			}
	}
	movPlayers = false;
	return false;
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	getline(fin, line);
	sstream.str(line);
	
	sstream >> baldosas;
	AllBaldosas = new glm::ivec2[baldosas];

	getline(fin, line);
	sstream.str(line);
	sstream >> num_enemies;
	PosEnemies = new pair<int, glm::ivec2>[num_enemies];
	map = new int[mapSize.x * mapSize.y];
	map_floor = new bool[mapSize.x * mapSize.y];
	mapPair = new int[mapSize.x * mapSize.y];
	int x = 0;
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if (tile == ' ')
				map[j * mapSize.x + i] = 0;
			else if ((tile >= 'm') && (tile < 'p'))
			{
				if (tile == 'm')
				{

					PosEnemies[i_enemies] = make_pair(Esqueleto, glm::ivec2(i*tileSize,(j-1)*tileSize));
				}
				else if (tile == 'n')
				{
					PosEnemies[i_enemies] = make_pair(Arquero, glm::ivec2(i * tileSize, (j - 1) * tileSize));
				}
				else if (tile == 'o')
				{
					PosEnemies[i_enemies] = make_pair(Vampiro, glm::ivec2(i * tileSize, (j - 1) * tileSize));
				}
				++i_enemies;
				map[j * mapSize.x + i] = 0;
				
			}
			else if (tile == 'p') //Portal
			{
				map[j * mapSize.x + i] = 0;
				posDoor = glm::vec2(i, j);
			}
			else
			{
				if (tile == 'Q')
				{
					map[j * mapSize.x + i] = 0;
					if (BaldosaInicial.x == NULL)
					{
						BaldosaInicial = glm::ivec2(i * tileSize, (j - 1) * tileSize);
						BaldosaReal = BaldosaInicial;
					}
					else
						BaldosaFinal = glm::ivec2(i * tileSize, (j - 1) * tileSize);
					baldosamov = true;
				}
				else
					map[j * mapSize.x + i] = tile - int('0');
				
				if (tile == (int('a')) || tile == (int('U')) || tile == (int('c')))
				{
					if (((posDoor.y - 1) == j) && (posDoor.x == i))
					{
						int a = 0;
					}
					else
					{
						map_floor[j * mapSize.x + i] = false;
						if (x % 2 == 0) mapPair[j * mapSize.x + i] = 1;
						else mapPair[j * mapSize.x + i] = 2;
						++this->TotalFloor;
						AllBaldosas[x] = glm::ivec2(i * tileSize, (j - 1) * tileSize);
						++x;
					}

				}
				else
					map_floor[j * mapSize.x + i] = true;
			}
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	AllSprites = new glm::ivec2[TotalFloor];

	return true;
}

void TileMap::prepareBaldosa()
{
	spritesheetBaldosaMov.loadFromFile("images/BalMov.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetBaldosaMov.setMagFilter(GL_NEAREST);
	spriteBaldosaMov = Sprite::createSprite(glm::ivec2(40, 20), glm::vec2(1.0, 1.0), &spritesheetBaldosaMov, &Shprogram);
	spriteBaldosaMov->setNumberAnimations(1);

	spriteBaldosaMov->setAnimationSpeed(0, 8);
	spriteBaldosaMov->addKeyframe(0, glm::vec2(0.f, 0.f));
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
if (tile != 0)
{
	// Non-empty tile
	nTiles++;
	posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
	texCoordTile[0] = glm::vec2((float((tile - 1) % tilesheetSize.x) / tilesheetSize.x), float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
	texCoordTile[1] = texCoordTile[0] + tileTexSize;
	//texCoordTile[0] += halfTexel;
	texCoordTile[1] -= halfTexel;
	// First triangle
	vertices.push_back(posTile.x); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
	// Second triangle
	vertices.push_back(posTile.x); vertices.push_back(posTile.y);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
	vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
	vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
	vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void TileMap::SetDoor()
{
	map[posDoor[1] * mapSize.x + posDoor[0]] = int('p') - int('0'); // Izq Abajo
	map[(posDoor[1]-1) * mapSize.x + posDoor[0]] = int('p') - int('0'); //Izq Arriba
	map[posDoor[1] * mapSize.x + (posDoor[0]+1)] = int('p') - int('0'); // Dere Abajo
	map[(posDoor[1]-1) * mapSize.x + (posDoor[0]+1)] = int('p') - int('0'); //Dere Arriba
}

void TileMap::setEnemy(glm::ivec2 posEnemy)
{
	int x = posEnemy.x / tileSize;
	int y = posEnemy.y / tileSize;
	
	map[y * mapSize.x + x] = int('m') - int('0'); // Izq Abajo
	map[(y + 1) * mapSize.x + x] = int('m') - int('0'); //Izq Arriba
	map[y * mapSize.x + (x + 1)] = int('m') - int('0'); // Dere Abajo
	map[(y + 1) * mapSize.x + (x + 1)] = int('m') - int('0'); //Dere Arriba
}

void TileMap::SetObject(glm::ivec2 ObjectPos, int type)
{
	map[ObjectPos[1] * mapSize.x + ObjectPos[0]] = int('p') - int('0') + type; // Izq Abajo

}

glm::ivec2 TileMap::GetDoorPosition()
{
	return glm::ivec2(posDoor[0] * tileSize, (posDoor[1] - 1) * tileSize);
}

bool TileMap:: getNewFloor()
{
	bool a = activateSound;
	activateSound = false;
	return a;
}

int TileMap::getNumFloorActivated()
{
	return TotalFloor - ActualFloorActivated;
}

pair<int, glm::ivec2> TileMap::getEnemyData(int i)
{
	return PosEnemies[i];
}

int TileMap::GetNumEnemies()
{
	return num_enemies;
}

void TileMap::deteleteEnemy(glm::ivec2 posEnemy)
{
	int x = posEnemy.x / tileSize;
	int y = posEnemy.y / tileSize;

	map[y * mapSize.x + x] = 0; // Izq Abajo
	map[(y + 1) * mapSize.x + x] = 0; //Izq Arriba
	map[y * mapSize.x + (x + 1)] = 0; // Dere Abajo
	map[(y + 1) * mapSize.x + (x + 1)] = 0; //Dere Arriba
}

glm::ivec2 TileMap::getPosPortal()
{
	return glm::ivec2((posDoor.x*20)-4, posDoor.y*20);
}

void TileMap::borrarObj(glm::ivec2 pos)
{
	int x = pos.x / tileSize;
	int y = pos.y / tileSize;
	map[y * mapSize.x + x] = 0;
}

glm::ivec2 TileMap::getRandomPosi(glm::ivec2 posP)
{
	int pos = 0;
	srand(time(NULL));
	pos = rand() % baldosas;
	int x1, x2, y;
	x1 = (posP.x + (17 / 2)) / tileSize;
	x2 = (posP.x + 17) / tileSize;
	if (abs(AllBaldosas[pos].x - x1) >= 80)
		return AllBaldosas[pos];
	else
	{
		if (pos + 4 == AllBaldosas->length())
			pos -= 4;
		else
		{
			pos += 4;
		}
		return AllBaldosas[pos];
	}
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.


int TileMap::ObjectLeftPlayer(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, x1, y0, y1;

	x = (pos.x + 5 + (size.x / 2)) / tileSize;
	x1 = (pos.x + (size.x / 2)) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == (int('p') - int('0')))
			return (map[y * mapSize.x + x]- (int('p') - int('0')));
		else if (map[y * mapSize.x + x1] > (int('p') - int('0')))
			return (map[y * mapSize.x + x1] - (int('p') - int('0')));
	}

	return -1;
}

int TileMap::ObjectRightPlayer(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, x1, y0, y1;

	x = (pos.x - 10 + (size.x-1)) / tileSize;
	x1 = (pos.x + (size.x - 1)) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] == (int('p') - int('0')))
			return (map[y * mapSize.x + x]- (int('p') - int('0')));
		else if (map[y * mapSize.x + x1] > (int('p') - int('0')))
			return (map[y * mapSize.x + x1] - (int('p') - int('0')));
	}

	return -1;
}

bool TileMap::collisionMoveLeftEnemy(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = (pos.y) / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if ((map[(y1 + 1) * mapSize.x + x] == 0) || (map[(y)*mapSize.x + x] < (int('m') - int('0')) && map[(y)*mapSize.x + x] != 0))
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRightEnemy(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if ((map[(y1 + 1) * mapSize.x + x] == 0) || (map[(y)*mapSize.x + x] < (int('m') - int('0')) && (map[(y)*mapSize.x + x] != 0)))
			return true;
	}

	return false;
}

void TileMap::changefloor_test(const glm::ivec2& pos, const glm::ivec2& size)
{

	spritesheetSuelo.loadFromFile("images/blocks.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheetSuelo.setMagFilter(GL_NEAREST);
	spriteSuelo = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(1.0, 1.0), &spritesheetSuelo, &Shprogram);
	spriteSuelo->setNumberAnimations(1);

	spriteSuelo->setAnimationSpeed(0, 8);
	spriteSuelo->addKeyframe(0, glm::vec2(0.f, 0.f));


	AllSprites[ActualFloorActivated] = glm::ivec2(pos.x, pos.y + minCoord.y - 16);
	ActualFloorActivated++;
	haysuelo = true;
	activateSound = true;

}

int TileMap::newFloorLeft(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, x1, x2, y0, y1, baldosas = 0;

	x = (pos.x + (size.x / 2) ) / tileSize;	//Centro 5 o 1
	x1 = (pos.x + size.x - 1) / tileSize;		// Derecha
	x2 = (pos.x) / tileSize;					//IZQUIERDA
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	if ((map[(y1 + 1) * mapSize.x + x1] == (int('a') - int('0'))) || (map[(y1 + 1) * mapSize.x + x1] == (int('U') - int('0'))) || (map[(y1 + 1) * mapSize.x + x1] == (int('c') - int('0')))) //IZQUIERDA
	{
		if (!map_floor[(y1 + 1) * mapSize.x + x1])
		{
			if (mapPair[(y1 + 1) * mapSize.x + x1] == 1)
			{
				map_floor[(y1 + 1) * mapSize.x + x1] = true;
				changefloor_test(glm::ivec2(x1 * tileSize, (y1+1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x1+1)] = true;
				changefloor_test(glm::ivec2((x1+1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
			else
			{
				map_floor[(y1 + 1) * mapSize.x + x1] = true;
				changefloor_test(glm::ivec2(x1 * tileSize, (y1+1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x1 - 1)] = true;
				changefloor_test(glm::ivec2((x1 - 1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
		}
	}

	if ((map[(y1 + 1) * mapSize.x + x2] == (int('a') - int('0'))) || (map[(y1 + 1) * mapSize.x + x2] == (int('U') - int('0'))) || (map[(y1 + 1) * mapSize.x + x2] == (int('c') - int('0'))))
	{
		if (!map_floor[(y1 + 1) * mapSize.x + x2])
		{
			if (mapPair[(y1 + 1) * mapSize.x + x2] == 1)
			{

				map_floor[(y1 + 1) * mapSize.x + x2] = true;
				changefloor_test(glm::ivec2(x2 * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x2+1)] = true;
				changefloor_test(glm::ivec2((x2+1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
			else
			{
				map_floor[(y1 + 1) * mapSize.x + x2] = true;
				changefloor_test(glm::ivec2(x2 * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x2 - 1)] = true;
				changefloor_test(glm::ivec2((x2 - 1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
		}
	}
	return baldosas*10;
}

int  TileMap::newFloorRight(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, x1, y0, y1, baldosas = 0;

	x = (pos.x) / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize; // 6 o 1
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	if (map[(y1 + 1) * mapSize.x + x1] == (int('a') - int('0')) || (map[(y1 + 1) * mapSize.x + x1] == (int('U') - int('0'))) || (map[(y1 + 1) * mapSize.x + x1] == (int('c') - int('0'))))
	{
		if (!map_floor[(y1 + 1) * mapSize.x + x1])
		{
			if (mapPair[(y1 + 1) * mapSize.x + x1] == 1)
			{
				map_floor[(y1 + 1) * mapSize.x + x1] = true;
				changefloor_test(glm::ivec2(x1 * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x1+1)] = true;
				changefloor_test(glm::ivec2((x1+1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
			else
			{
				map_floor[(y1 + 1) * mapSize.x + x1] = true;
				changefloor_test(glm::ivec2(x1 * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x1 - 1)] = true;
				changefloor_test(glm::ivec2((x1 - 1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
		}
	}

	if ((map[(y1 + 1) * mapSize.x + x] == (int('a') - int('0'))) || (map[(y1 + 1) * mapSize.x + x] == (int('U') - int('0'))) || (map[(y1 + 1) * mapSize.x + x] == (int('c') - int('0'))))
	{
		if (!map_floor[(y1 + 1) * mapSize.x + x])
		{
			if (mapPair[(y1 + 1) * mapSize.x + x] == 1)
			{
				map_floor[(y1 + 1) * mapSize.x + x] = true;
				changefloor_test(glm::ivec2(x * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x+1)] = true;
				changefloor_test(glm::ivec2((x+1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
			else
			{
				map_floor[(y1 + 1) * mapSize.x + x] = true;
				changefloor_test(glm::ivec2(x * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;

				map_floor[(y1 + 1) * mapSize.x + (x - 1)] = true;
				changefloor_test(glm::ivec2((x - 1) * tileSize, (y1 + 1) * tileSize), size);
				++baldosas;
			}
		}
	}
	return baldosas*10;
}

bool TileMap::collisionMoveLeftPlayer(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;

	int xB0 = BaldosaReal.x / tileSize;
	int xB1 = (BaldosaReal.x + 40 - 1) / tileSize;
	int yB = BaldosaReal.y / tileSize;

	for (int y = y0; y <= y1; y++)
	{
		if (map[(y1)*mapSize.x + x] <= (int('l') - int('0')) && map[(y1)*mapSize.x + x] != 0 && (map[(y1)*mapSize.x + x] != (int('g') - int('0'))) && (map[(y1)*mapSize.x + x] != (int('h') - int('0'))) && (map[(y1)*mapSize.x + x] != (int('U') - int('0')) && map[(y1)*mapSize.x + x] != (int('a') - int('0'))))
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRightPlayer(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = (pos.x + size.x -1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;

	for (int y = y0; y <= y1; y++)
	{
		if (map[y1 * mapSize.x + x] <= (int('l')-int('0')) && map[y1 * mapSize.x + x] != 0 && (map[(y1)*mapSize.x + x] != (int('U') - int('0')) && (map[(y1)*mapSize.x + x] != (int('h') - int('0')))  &&  (map[(y1)*mapSize.x + x] != (int('g') - int('0'))) && map[(y1)*mapSize.x + x] != (int('a') - int('0'))))
			return true;
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;


	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapSize.x + x] != 0)
		{
			if (map[y * mapSize.x + x] < int('m') - int('0')) //*posY - tileSize * y + size.y <= 4
			{
				*posY = tileSize * y - size.y;
				return true;
			}
			
		}
	}

	return false;
}

bool TileMap::collisionUp(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (map[y * mapSize.x + x] == int('C') - int('0') || map[y * mapSize.x + x] == int('c') - int('0')) //*posY - tileSize * y + size.y <= 4
			{
				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionSpikeDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[(y) * mapSize.x + x] != 0)
		{
			if (map[(y) * mapSize.x + x] == 1) //*posY - tileSize * y + size.y <= 4
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}

int TileMap::vampireFloor(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x1, x2, y;

	x1 = pos.x / tileSize;
	x2 = (pos.x + size.x - 1) / tileSize;
	y = (((pos.y) + size.y - 1) / tileSize);


	if (map[y * mapSize.x + x1] != 0 && map[y * mapSize.x + x2] != 0 && map[y * mapSize.x + x1] != 1 && map[y * mapSize.x + x2] != 1)
	{
		if (map[y * mapSize.x + x1] < int('m') - int('0') && map[y * mapSize.x + x2] < int('m') - int('0'))
		{
			return 2;
		}
	}

	for (int x = x1; x < x2; ++x)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (map[y * mapSize.x + x] < int('m') - int('0'))
			{
				return 1;
			}
		}
	}

	return 0;
}

bool TileMap::collisionUpBat(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x1, x2, y;

	x1 = pos.x / tileSize;
	x2 = (pos.x + size.x - 1) / tileSize;
	y = ((pos.y) / tileSize);

	for (int x = x1; x < x2; ++x)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (map[y * mapSize.x + x] < int('m') - int('0'))
			{
				return true;
			}
		}

		return false;
	}
}

bool TileMap::collisionMoveLeftBat(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, y0, y1;

	x = (pos.x) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[(y)*mapSize.x + x] <= (int('l') - int('0')) && map[(y)*mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRightBat(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[(y)*mapSize.x + x] <= (int('l') - int('0')) && map[(y)*mapSize.x + x] != 0)
			return true;
	}

	return false;
}

