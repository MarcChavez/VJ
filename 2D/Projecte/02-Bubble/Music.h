#ifndef _MUSIC_INCLUDE
#define _MUSIC_INCLUDE

#include <iostream>
#include <irrKlang.h>
#include <map>
using namespace irrklang;

using namespace std;

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 540


// Game is a singleton (a class with a single instance) that represents our whole application


class Music
{

private:
	Music() {}

public:
	static Music& instance()
	{
		static Music G;

		return G;
	}


	void playBell();
	void playCoin();
	void playdeathSound();
	void playFloorSound();
	void playGameOverSong();
	void keySound();
	void MainGameSong();
	void MainMenuSong();
	void playPointSound();
	void playShootSound();
	void playstopTimeSound();
	void playTPSound();
	void playTVampSound();
	void playWatchSound();
	void playWinSong();
	void playCreditsSong();
	void stopAll();
	void setGeneralSound(float volum);

	void StopMainSong();
	void StopMenuSong();
	void StopGameOverSong();
	void StopWinSong();

	void StopResumeMainSong(bool action);
	bool SongEnded(char* path);


private:

	ISoundEngine* engine = createIrrKlangDevice();
	ISound* MainSong = NULL;
	ISound* GameSong = NULL;
	ISound* GameOverSong = NULL;
	ISound* WinSong = NULL;
};


#endif // _MUSIC_INCLUDE