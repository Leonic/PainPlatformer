#pragma once
#ifndef __TextureManager_H__
#define __TextureManager_H__

#include <SDL2/SDL.h>
#include <string>
#include <map>

class CTextureManager
{
private:
	CTextureManager() {} ;
	static CTextureManager* s_pInstance;

public:
	static CTextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CTextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void Draw(std::string id, int x, int y, int width, int  height, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// drawframe
	void DrawFrame(std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif /* defined(__TextureManager__) */