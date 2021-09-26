#pragma once
#ifndef __EventHandler_H__
#define __EventHandler_H__

#include <SDL2/SDL.h>
#include <vector>

class EventHandler 
{
public:
	static EventHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new EventHandler();
		}

		return s_pInstance;
	}

    void OnThink();
	void Destroy();

private:
    EventHandler();
	~EventHandler();

	void onMouseButtonDown(SDL_Event e);
	void onMouseButtonUp(SDL_Event e);

	void onKeyDown(SDL_Event e);
	void onKeyUp(SDL_Event e);

	void onFingerDown(SDL_Event e);
	void onFingerUp(SDL_Event e);

	static EventHandler* s_pInstance;
};

#endif