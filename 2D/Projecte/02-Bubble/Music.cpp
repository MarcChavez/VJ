#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include "Music.h"


void Music::playBell()
{
	ISound* sound = engine->play2D("media/bell.wav", false, false, true);
}

void Music::playCoin()
{
	ISound* sound = engine->play2D("media/coin.wav", false, false, true);
}

void Music::playdeathSound()
{
	ISound* sound = engine->play2D("media/deathSound.mp3", false, false, true);
}

void Music::playFloorSound()
{
	ISound* sound = engine->play2D("media/floor.mp3", false, false, true);
}

void Music::playGameOverSong()
{
	GameOverSong = engine->play2D("media/GameOver.mp3", true, false, true);
	GameOverSong->setVolume(0.2);
}

void Music::keySound()
{
	ISound* sound = engine->play2D("media/key.mp3", false, false, true);
	sound->setVolume(1.0);
}

void Music::MainGameSong()
{
	if (!engine->isCurrentlyPlaying("media/MainMenu.wav") && !engine->isCurrentlyPlaying("media/MainGame.mp3")) GameSong = engine->play2D("media/MainGame.mp3", true, false, true);
}

void Music::MainMenuSong()
{
	if (!engine->isCurrentlyPlaying("media/MainMenu.wav") && !engine->isCurrentlyPlaying("media/MainGame.mp3")) MainSong = engine->play2D("media/MainMenu.wav", true, false, true);
}

void Music::playPointSound()
{
	ISound* sound = engine->play2D("media/point.mp3", false, false, true);
}

void Music::playShootSound()
{
	ISound* sound = engine->play2D("media/starwars.mp3", false, false, true);
}

void Music::playstopTimeSound()
{
	ISound* sound = engine->play2D("media/stopTime.mp3", false, false, true);

}

void Music::playTPSound()
{
	if (!engine->isCurrentlyPlaying("media/teleport.mp3"))
	{
		ISound* sound = engine->play2D("media/teleport.mp3", false, false, true);
		sound->setVolume(0.35);
	}
}

void Music::playTVampSound()
{
	ISound* sound = engine->play2D("media/transformation.mp3", false, false, true);
	sound->setVolume(0.25);
}

void Music::playWatchSound()
{
	ISound* sound = engine->play2D("media/watch.mp3", false, false, true);
	sound->setVolume(1.0);
}

void Music::playWinSong()
{
	WinSong = engine->play2D("media/win.mp3", false, false, true);
}

void Music::stopAll()
{
	engine->stopAllSounds();
}

void Music::setGeneralSound(float volum)
{
	engine->setSoundVolume(volum);
}

void Music::StopMainSong()
{
	if (engine->isCurrentlyPlaying("media/MainGame.mp3"))
	{
		GameSong->stop();
	}
}

void Music::StopMenuSong()
{
	if (engine->isCurrentlyPlaying("media/MainMenu.wav"))
	{
		MainSong->stop();
	}
}

void Music::StopGameOverSong()
{
	if (engine->isCurrentlyPlaying("media/GameOver.mp3"))
	{
		GameOverSong->stop();
	}
}

void Music::StopWinSong()
{
	if (engine->isCurrentlyPlaying("media/win.mp3"))
	{
		MainSong->stop();
	}
}

bool Music::SongEnded(char* path)
{
	return engine->isCurrentlyPlaying(path);
}

void Music::StopResumeMainSong(bool action)
{
	if (engine->isCurrentlyPlaying("media/MainGame.mp3"))
		GameSong->setIsPaused(action);
	else if (engine->isCurrentlyPlaying("media/MainMenu.wav"))
		MainSong->setIsPaused(action);
}

void Music::playCreditsSong()
{
	ISound* sound = engine->play2D("media/creditos.mp3", true, false, true);
	sound->setVolume(0.2);
}