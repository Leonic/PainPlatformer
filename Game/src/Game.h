#pragma once
#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>

class CGame
{
public:
	static CGame* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CGame();
			return s_pInstance;
		}
		return s_pInstance;
	}
private:
	CGame() {}
	~CGame() {}
	
	static CGame* s_pInstance;

public:

	// simply set the running variable to true
	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void Draw();
	void OnThink();
	void HandleEvents();
	void Destroy();
	void Quit();

	// a function to access the private running variable
	bool IsRunning() { return m_bRunning; }

	void testCallback(SDL_Event e);

	SDL_Renderer* GetRenderer() const { return m_pRenderer; }
	SDL_Window* GetWindow() const { return m_pWindow; }

private:
	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;

	SDL_Texture* m_pTexture = 0; // the new SDL_Texture variable
	SDL_Rect m_sourceRectangle = {}; // the first rectangle
	SDL_Rect m_destinationRectangle = {}; // another rectangle

	bool m_bRunning = false;
};

#endif /* defined(__Game__) */