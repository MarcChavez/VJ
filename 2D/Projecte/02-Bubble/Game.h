#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "SceneMenu.h"
#include "Instrucciones.h"
#include "Creditos.h"
#include "GameOver.h"
#include "Oso.h"
#include "Pass.h"
#include "Music.h"

#include <irrKlang.h>
#include <map>
using namespace irrklang;



#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();

	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	void setLevel();
	void setPuntuacion(int pt);
	void setVida(int vida);
	void cogePasswords();

	static void resizeGame(int w, int h);
	void resizeScene(int w, int h);

	void dontShowIns(bool show) { showIns = show; }


private:

	void initShaders();

	ShaderProgram texProgram;

	bool bPlay;                       // Continue to play game?
	Scene *scene;                      // Scene to render
	SceneMenu *scene2;                      // Scene to render
	Instrucciones *ins;
	Creditos *cred;
	GameOver *go;
	Oso *oso;
	Pass *passw;
	bool show_oso = false;
	bool keys[256], specialKeys[256]; // Store key states so that 
	bool menu = true;
	bool ins_ac = false;
	int lvl = 1;
	bool creditos = false;
	bool over = false; 
	bool overtime = false;
	int vida = 3;
	int puntuacion = 0;
	int maxLvl;
	map<string, char> passwords;

	bool keypre = false;

	bool codeE = false;
	bool codeS = false;

	int select = 0;
	int currentTime;
	bool timeCreditos;

	bool showIns = true;

	GLuint windowH;
	GLuint windowW;
	GLuint windowX;
	GLuint windowY;

	GLboolean windowF;

};


#endif // _GAME_INCLUDE