#include "Game.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include <iostream>

Game* Game::s_pInstance = 0;

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt to initalize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "Window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,
					255, 255, 255, 255);

                if (!TextureManager::Instance()->Load("assets/akrius.png", "akrius", m_pRenderer))
				{
					return false;
				}
			}
			else
			{
				std::cout << "Render init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "SDL init fail\n";
			return false; // SDL init fail
		}

		std::cout << "Init success\n";
		m_bRunning = true; // everything inited successfully, start the main loop

		return true;
	}
	return false;
}

void Game::Draw()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to draw color

    if (TextureManager::Instance()->m_textureMap["akrius"] != nullptr)
        TextureManager::Instance()->Draw("akrius", 0, 0, 437, 437, m_pRenderer);

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::OnThink()
{ 

}

void Game::HandleEvents()
{
    EventHandler::Instance()->OnThink();
}

void Game::Destroy()
{
	std::cout << "Cleaning Game instance...\n";

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();
}

void Game::Quit()
{
	m_bRunning = false;
}