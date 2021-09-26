#include "TextureManager.h"
#include <SDL2/SDL_image.h>

CTextureManager* CTextureManager::s_pInstance = 0;

bool CTextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    // load dah image
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}

    // create a texture
	SDL_Texture* pTexture =
		SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	// we have loaded the texture ok, add it to the map!
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// if we got here, something is wrong.
	return false;
}

void CTextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    // RECTANGLESSS ---> SCREEN
	SDL_Rect srcRect;
	SDL_Rect destRect;

    // Static image, draw the WHOLE thing
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

    // draw dat 2 dah screen
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}

void CTextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    // rectangles for drawing to the screeeeen
	SDL_Rect srcRect;
	SDL_Rect destRect;

    // Get the relevant sprite, depending on the frame
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);

    // height + width
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

    // Copy to the screen on the position it was meant to be
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}