#pragma once
#ifndef __EventHandler_H__
#define __EventHandler_H__

#include <SDL2/SDL.h>
#include <vector>
#include "EngineTypes.h"

class CEventHandler 
{
public:
	static CEventHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CEventHandler();
		}

		return s_pInstance;
	}

	void AddOnKeyDown(HKeyCallback callBack);
	void AddOnKeyUp(HKeyCallback callBack);

	void AddOnMouseDown(HInputCallback callBack);
	void AddOnMouseUp(HInputCallback callBack);

	void AddOnFingerDown(HInputCallback callBack);
	void AddOnFingerUp(HInputCallback callBack);

	void RemoveOnKeyDown(HKeyCallback callBack);
	void RemoveOnKeyUp(HKeyCallback callBack);

	void RemoveOnMouseDown(HInputCallback callBack);
	void RemoveOnMouseUp(HInputCallback callBack);

	void RemoveOnFingerDown(HInputCallback callBack);
	void RemoveOnFingerUp(HInputCallback callBack);

    void OnThink();
	void Destroy();

private:
    CEventHandler();
	~CEventHandler();

	void onMouseButtonDown(SDL_Event e);
	void onMouseButtonUp(SDL_Event e);

	void onKeyDown(SDL_Event e);
	void onKeyUp(SDL_Event e);

	void onFingerDown(SDL_Event e);
	void onFingerUp(SDL_Event e);

	std::vector<HKeyCallback> m_keyDownCallbacks;
	std::vector<HKeyCallback> m_keyUpCallbacks;

	std::vector<HInputCallback> m_mouseDownCallbacks;
	std::vector<HInputCallback> m_mouseUpCallbacks;

	std::vector<HInputCallback> m_fingerDownCallbacks;
	std::vector<HInputCallback> m_fingerUpCallbacks;

	static CEventHandler* s_pInstance;

	Uint8* m_keystates = 0;
};
#endif