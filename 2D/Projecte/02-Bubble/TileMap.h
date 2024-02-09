#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "Sprite.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render();
	void free();

	int getTileSize() const { return tileSize; }

	int getTile(int x, int y) { return map[y * mapSize.x + x]; }

	bool collisionMoveLeftEnemy(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRightEnemy(const glm::ivec2& pos, const glm::ivec2& size) const;

	bool collisionMoveLeftPlayer(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRightPlayer(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionSpikeDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionUp(const glm::ivec2& pos, const glm::ivec2& size) const;

	int ObjectLeftPlayer(const glm::ivec2& pos, const glm::ivec2& size);
	int ObjectRightPlayer(const glm::ivec2& pos, const glm::ivec2& size);
	
	int newFloorLeft(const glm::ivec2& pos, const glm::ivec2& size);
	int newFloorRight(const glm::ivec2& pos, const glm::ivec2& size);
	void changefloor_test(const glm::ivec2& pos, const glm::ivec2& size);

	int vampireFloor(const glm::ivec2& pos, const glm::ivec2& size);
	bool collisionUpBat(const glm::ivec2& pos, const glm::ivec2& size);
	bool collisionMoveLeftBat(const glm::ivec2& pos, const glm::ivec2& size);
	bool collisionMoveRightBat(const glm::ivec2& pos, const glm::ivec2& size);

	glm::ivec2 getRandomPosi(glm::ivec2 posP);

	// SETERS , GETERS Y DELETE
	pair<int, glm::ivec2> getEnemyData(int i);
	int GetNumEnemies();
	int getNumFloorActivated();
	void SetDoor();
	glm::ivec2 GetDoorPosition();
	void SetObject(glm::ivec2 ObjectPos, int type);
	void setEnemy(glm::ivec2 posEnemy);

	glm::ivec2 getPosPortal();

	void borrarObj(glm::ivec2 pos);
	void deteleteEnemy(glm::ivec2 posEnemy);

	bool getNewFloor();

	void prepareBaldosa();

	int getMovPlayer();

	void updateBaldosa();
	bool baldosaDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY);

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	Texture spritesheetSuelo;
	Texture spritesheetBaldosaMov;

	Sprite *sprite;
	Sprite* spriteBaldosaMov;
	Sprite *spriteSuelo;
	
	bool* map_floor;
	int *map;
	int* mapPair;
	bool activateSound = false;
	

	ShaderProgram Shprogram;
	bool haysuelo = false;
	int TotalFloor = 0;
	int ActualFloorActivated = 0;
	int num_enemies;
	
	int i_enemies = 0;
	glm::ivec2 posDoor;
	glm::vec2 minCoord;
	glm::ivec2* AllSprites;
	glm::ivec2* AllBaldosas;
	int baldosas;
	pair<int, glm::ivec2>* PosEnemies;

	bool baldosamov = false;
	glm::vec2 BaldosaInicial = glm::vec2(NULL, NULL);
	glm::vec2 BaldosaFinal = glm::vec2(NULL, NULL);
	glm::vec2 BaldosaReal = glm::vec2(NULL, NULL);
	bool movBaldosaIzq = false;
	bool movPlayers = false;


};


#endif // _TILE_MAP_INCLUDE


