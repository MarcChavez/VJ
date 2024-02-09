#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include "Game.h"



void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	initShaders();
	currentTime = 0;
	cogePasswords();

	glutSetCursor(GLUT_CURSOR_NONE);

	Music::instance().MainMenuSong();

	ins = new Instrucciones();
	ins->init(texProgram);

	oso = new Oso();
	oso->init(texProgram);

	go = new GameOver();
	go->init(texProgram);

	cred = new Creditos();
	cred->init(texProgram);

	scene2 = new SceneMenu();
	scene2->init(texProgram);

	scene = new Scene();
	scene->init(lvl, vida, puntuacion, texProgram);
	resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	passw = new Pass();
	passw->init(texProgram);

}

bool Game::update(int deltaTime)
{	
	currentTime += deltaTime;

	if (show_oso)
		oso->update(deltaTime);

	else if (menu)
		 scene2->update(deltaTime);	

	else if (codeE)
		passw->update(deltaTime);

	else
	{
		if (!over && !creditos)
		{
			if (codeS)
				passw->update(deltaTime);

			else if (ins_ac)
				ins->update(deltaTime);

			else
				scene->update(deltaTime);
		}

		else if (creditos)
		{
			if (timeCreditos)
			{
				creditos = false;
				menu = true;
				Music::instance().stopAll();
				delete scene;
				scene = new Scene();
				lvl = 1;
				vida = 3;
				puntuacion = 0;
				scene->init(lvl, vida, puntuacion, texProgram);
				resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			}
			cred->update(deltaTime);
		}	

		else
		{
			go->update(deltaTime);
			if (overtime)
			{
				over = false;
				menu = true;
				Music::instance().StopGameOverSong();
				Music::instance().MainMenuSong();
			}
		}
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (show_oso)
		oso->render();
	
	else if (menu) 
		scene2->render();

	else if (codeE) 
		passw->render();

	else
	{
		if (!ins) glDisable(GL_BLEND);

		if (!over && !creditos)
		{
			if (codeS)
				passw->render();

			else if (ins_ac)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_DST_COLOR, GL_ZERO);
				scene->render();

				glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
				ins->render();
			}

			else
				scene->render();
		}
			

		else if (creditos)
			cred->render();
			
		else
			go->render();
	}
}

void Game::keyPressed(int key)
{
	
	if (key == 13) //ENTER
	{
		if (menu)
		{
			if (select == 0)
			{
				menu = false;
			}
			else if (select == 1)
			{
				codeE = true;
				menu = false;
			}
			else if (select == 2)
				bPlay = false;
			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}

		else if (creditos)
			timeCreditos = true;

		else if (over)
			overtime = true;

		else if (codeE)
		{
			string code = passw->givePassWord();
			std::map<string, char>::iterator it;
			it = passwords.find(code);
			if (it != passwords.end())
			{
				lvl = int(it->second) - int('0');
				delete scene;
				scene = new Scene();
				scene->init(lvl, vida, puntuacion, texProgram);
				resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
				codeE = false;
				menu = false;
				passw->resetPassWord();
			}
			else
			{
				passw->errorPasw(true);
			}
		}
	}

	if (key == 32) // ESPACIO
	{
		if (menu)
		{
			if (select == 0)
			{
				menu = false;
			}
			else if (select == 1)
			{
				codeE = true;
				menu = false;
			}
			else if (select == 2)
				bPlay = false;

			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
	}
	
	if (key == 27) // Escape code
	{
		if (menu) bPlay = false;
		else
		{
			menu = true;
			codeS = false;
			codeE = false;
			ins_ac = false;
			delete scene;
			scene = new Scene();
			lvl = 1;
			vida = 3;
			puntuacion = 0;
			scene->init(lvl, vida, puntuacion, texProgram);
			passw->resetPassWord();
			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			Music::instance().stopAll();
			Music::instance().MainMenuSong();

		}
	}

	if (!menu && !over && !ins_ac && !creditos && !codeE) //Cheat de cambio de nivel
	{
		if (key == 49)
		{
			lvl = 1;
			delete scene;
			Music::instance().stopAll();
			scene = new Scene();
			scene->init(lvl, vida, puntuacion, texProgram);
			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
		if (key == 50)
		{
			lvl = 2;
			Music::instance().stopAll();
			delete scene;
			scene = new Scene();
			scene->init(lvl, vida, puntuacion, texProgram);
			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
		if (key == 51)
		{
			lvl = 3;
			Music::instance().stopAll();
			delete scene;
			scene = new Scene();
			scene->init(lvl, vida, puntuacion, texProgram);
			resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
	}

	if (codeE && !keypre && key != 13) //Lee por teclado para password
	{
		keypre = true;
		passw->setCode(key);
		passw->errorPasw(false);
	}

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
	keypre = false;
}

void Game::specialKeyPressed(int key)
{

	if (key == 1)
	{
		if ((!menu && !codeS) && showIns)
		{
			if (!keypre)
			{
				codeE = !codeE;
				keypre = true;
				for (std::map<string, char>::iterator it = passwords.begin(); it != passwords.end(); ++it)
					if (it->second == (char('0') + lvl))
						passw->setPassWord(it->first);
			}
		}
	}

	if (key == 103)
	{
		if (menu && !specialKeys[key])
		{
			++select;
			if (select == 3) select = 0;
			scene2->changeAni(select);
		}
	}

	if (key == 101)
	{
		if (menu && !specialKeys[key])
		{
			--select;
			if (select == -1) 
				select = 2;
			scene2->changeAni(select);
		}
	}

	if (key == 2) // Escape code
	{
		if (!menu && !over && !creditos && !codeS && showIns && !show_oso)
			ins_ac = true;
	}

	if (key == 3)
	{
		if (!over && showIns)
			show_oso = true;
	}

	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	if (key == 1)
	{
		keypre = false;
	}
	if (key == 2) // Escape code
	{
		if (!menu && !over)
		{
			ins_ac = false;
			glDisable(GL_BLEND);
		}
	}
	if (key == 3 && !over)
	{
		show_oso = false;
	}

	keypre = false;
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::setLevel()
{
	++lvl;
	if (lvl == maxLvl+1)
	{
		creditos = true;
		Music::instance().playCreditsSong();

	}
	else
	{
		Music::instance().stopAll();
		delete scene;
		scene = new Scene();
		scene->init(lvl, vida, puntuacion, texProgram);
		resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
	
}

void Game::setPuntuacion(int pt)
{
	puntuacion = pt;
}

void Game::setVida(int life)
{
	vida = life;
	if (vida == 0)
	{
		over = true;
		vida = 3;
		puntuacion = 0;
		lvl = 1;
		delete scene;
		scene = new Scene();
		scene->init(lvl, vida, puntuacion, texProgram);
		resizeScene(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		Music::instance().stopAll();
		Music::instance().playGameOverSong();
		
		overtime = false;
	}
		
}

void Game::initShaders()
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

void Game::cogePasswords()
{
	string levelPasswords = "passwords/passwords.txt";
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelPasswords.c_str());
	if (!fin.is_open())
		return;

	getline(fin, line);
	sstream.str(line);
	string num;
	sstream >> num;

	 maxLvl = stoi(num);

	for (int i = 0; i < maxLvl; ++i)
	{
		getline(fin, line);
		sstream.str(line);
		string pass = "";
		std::string delimiter = "-";
		std::string pass2 = line.substr(0, line.find(delimiter));
		passwords.insert(std::pair<string, char>(pass2, line[line.size()-1]));
	}
	fin.close();
}

void Game::resizeGame(int w, int h) {
	Game::instance().resizeScene(w, h);
}

void Game::resizeScene(int w, int h) {
	glViewport(0.f, 0.f, w, h);
	if (show_oso)
		oso->changeWindow(w, h);
	if (menu)
		scene2->changeWindow(w, h);
	else if (codeS)
		passw->changeWindow(w, h);
	else
	{
		if (!over)
		{
			scene->changeWindow(w, h);
			ins->changeWindow(w, h);
			passw->changeWindow(w, h);
			cred->changeWindow(w, h);
		}
		else
			go->changeWindow(w, h);
	}
}








