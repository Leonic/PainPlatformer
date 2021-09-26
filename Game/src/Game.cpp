#include "Game.h"
#include "TextureManager.h"
#include "EventHandler.h"
#include <iostream>
#include "Player.h"

CGame* CGame::s_pInstance = 0;

bool CGame::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt to initalize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		std::cout << "(CGame::Init) SDL init success" << std::endl;
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0)
		{
			std::cout << "(CGame::Init) Window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "(CGame::Init) Renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer,
					255, 255, 255, 255);

                if (!CTextureManager::Instance()->Load("assets/player.png", "leo", m_pRenderer))
				{
					return false;
				}

				m_Objects.push_back(new CPlayer("Test", "leo", CVector2D(0, 0), CVector2D(128, 128)));

				// we need to use placeholders, for some reason
				CEventHandler::Instance()->AddOnMouseDown(std::bind(&CGame::testCallback, this, std::placeholders::_1));
				CEventHandler::Instance()->AddOnFingerDown(std::bind(&CGame::testCallback, this, std::placeholders::_1));
				CEventHandler::Instance()->AddOnMouseUp(std::bind(&CGame::testCallback, this, std::placeholders::_1));
			}
			else
			{
				std::cout << "(CGame::Init) Render init fail" << std::endl;
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "(CGame::Init) SDL init fail" << std::endl;
			return false; // SDL init fail
		}

		std::cout << "(CGame::Init) Init success" << std::endl;
		m_bRunning = true; // everything inited successfully, start the main loop

		return true;
	}
	return false;
}

void CGame::Draw()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to draw color

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->OnDraw();
	}

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void CGame::OnThink()
{ 
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->OnThink();
	}
}

void CGame::HandleEvents()
{
    CEventHandler::Instance()->OnThink();
}

void CGame::Destroy()
{
	std::cout << "(CGame::Init) Cleaning Game instance..." << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();
}

void CGame::Quit()
{
	m_bRunning = false;
}

void CGame::testCallback(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_FINGERDOWN:
	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);

		std::cout << "(CGame::testCallback) Mouse Down!" << std::endl;
		m_Objects.push_back(new CPlayer("Test", "leo", CVector2D(x, y), CVector2D(128, 128)));
		break;
	case SDL_MOUSEBUTTONUP:
		std::cout << "(CGame::testCallback) Mouse Up!" << std::endl;
		break;
	}
}
