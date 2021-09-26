#include <string>
#include <iostream>
#include "Game.h"

int FPS = 62;
int DELAY_TIME = 1000 / FPS;

const char* WIDTH_PARAM = "-w";
const char* HEIGHT_PARAM = "-h";
const char* FULLSCREEN_PARAM = "-f";
const char* FPS_PARAM = "-fps";

bool m_bRunning = false;

bool FlagExists(char** argv, int argc, const char* flag)
{
	if (argc <= 1) return false;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], flag) == 0) return true;
	}

	return false;
}

bool GetParam(char** argv, int argc, const char* param, char** returnval)
{
	if (argc <= 1) return false;

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], param) == 0 && (i + 1) < argc)
		{
			*returnval = argv[i + 1];
			return true;
		}
	}

	return false;
}

void SetFPS(int newFPS)
{
	if (newFPS < 0) return;

	FPS = newFPS;
	DELAY_TIME = 1000 / FPS;
}

int main(int argc, char** argv)
{
    Uint32 frameStart, frameTime;
	
	if (Game::Instance()->Init("PainPlatformer", 100, 100, 640, 480, false))
	{
		while (Game::Instance()->IsRunning())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->HandleEvents();
			Game::Instance()->OnThink();
			Game::Instance()->Draw();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay(10);
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "Engine Error (Game Init failed!) - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "Cleaning up...\n";
	Game::Instance()->Destroy();

    return 0;
}