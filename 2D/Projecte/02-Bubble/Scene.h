#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Object.h"
#include "Enemy.h"

#include "Music.h"

#include <irrKlang.h>
using namespace irrklang;


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int lvl, int vidas, int puntuacion, ShaderProgram& texProgram);
	void update(int deltaTime);
	void render();
	void cheatsOn(bool inmortal, bool keyspawn, int deltaTime);
	bool TractaObjecte(int obpl);
	void CreaKey();
	void CreaWatch();
	void CreaGema();
	void CreaChrono();
	void ImprimeUI();
	void tiraDado();
	void setUI();
	void changeWindow(int w, int h);



private:
	TileMap *map;
	Player *player;
	Enemy* enemy;
	vector<Enemy*> EnemiesObj;
	vector<Object*> ObjectsObj;

	Sprite* SpriteUIFont;
	Sprite* SpriteUICor;
	Sprite* SpriteUIMoney;
	Sprite* SpriteUIFondo;
	Sprite* SpriteCartel;

	glm::ivec2* AllSprites;
	
	ShaderProgram texProgram;
	Texture spritesheetCor;
	Texture spritesheetFont;
	Texture spritesheetCartel;
	Texture spritesheetMoney;
	Texture spritesheetFondo;
	void BorraObjeto(int object);

	float currentTime;
	float contador = 0.0;
	float contador2 = 0.0;
	float timePortal = 0;
	float timeChrono;
	float gameTime;
	int puntos;
	int num_gemas = 0;
	int lvl;
	int vidas = 3;
	bool stop = false;
	bool stopfirst = false;
	bool stopsemi = false;
	bool obje = false;
	bool start = false;
	bool desaparece = false;
	bool cuenta_puntos = false;
	bool aparece = false;

	glm::mat4 projection;
	int nEnemies;
	int itKey, itGem, itWatch, itChrono;
	float timeGem, timeWatch, timeChronoD;
	bool test = false;


	bool llaveSpawned = false;
	bool keyCheat = false;
	bool llaveCheat = false;
	bool portalani = false;
	bool salida = false;
	bool chrono = false, reloj = false;

	bool acaboCancion = false;
	int puntoVida = 0;

	bool readyforTp = false;
};


#endif // _SCENE_INCLUDE

