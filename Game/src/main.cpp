#include <string>
#include <iostream>
#include "Game.h"
#include "EngineMetadata.h"
#include "EngineTypes.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int FPS = 62;
Uint32 DELAY_TIME = 1000 / FPS;

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

#ifdef _WIN32
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef USE_CONSOLE
	if (FlagExists(__argv, __argc, "-console"))
	{
		// Create a console and output all stdout and sterr to it.
		AllocConsole();

		// Redirect the std stuff
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
#endif

	Uint32 frameStart, frameTime;

	char szTitle[999];

	snprintf(szTitle, sizeof(szTitle), "Pain Platformer (Build: %d, git: %s)", GAME_BUILD_NUMBER, GAME_GIT_DESC);

	if (CGame::Instance()->Init(szTitle, 100, 100, WIDTH, HEIGHT, false))
	{
		while (CGame::Instance()->IsRunning())
		{
			frameStart = SDL_GetTicks();

			CGame::Instance()->HandleEvents();
			CGame::Instance()->OnThink();
			CGame::Instance()->Draw();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "(main.cpp) Engine Error (Game Init failed!) - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "Cleaning up...\n";
	CGame::Instance()->Destroy();

	return 0;
}

#elif _UNIX
int main(int argc, char** argv)
{
	Uint32 frameStart, frameTime;

	char szTitle[999];

	snprintf(szTitle, sizeof(szTitle), "Pain Platformer (Build: %d, git: %s)", GAME_BUILD_NUMBER, GAME_GIT_DESC);

	if (CGame::Instance()->Init(szTitle, 100, 100, WIDTH, HEIGHT, false))
	{
		while (CGame::Instance()->IsRunning())
		{
			frameStart = SDL_GetTicks();

			CGame::Instance()->HandleEvents();
			CGame::Instance()->OnThink();
			CGame::Instance()->Draw();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
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
	CGame::Instance()->Destroy();

	return 0;
}
#endif