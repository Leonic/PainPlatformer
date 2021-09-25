#include <string>
#include <SDL2/SDL.h>
#include <iostream>

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
	char title[420] = "PainPlatformer";

	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, 0, 0, 640, 480, NULL);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);

			if (m_pRenderer != 0) // render init success
			{
				SDL_SetRenderDrawColor(m_pRenderer,
					255, 255, 255, 255);
				
				m_bRunning = true; // everything inited successfully, start the main loop
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
			}
		}
	}

	while (m_bRunning)
	{
		frameStart = SDL_GetTicks();

		SDL_RenderClear(m_pRenderer); // clear the renderer to draw color

		SDL_RenderPresent(m_pRenderer); // draw to the screen

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < Uint32(DELAY_TIME))
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

    return 0;
}