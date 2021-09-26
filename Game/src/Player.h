#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PainObject.h"

class CPlayer : public CPainObject
{
public:
	CPlayer() {};
	CPlayer(const char* name, std::string textureID, CVector2D position, CVector2D size);

	void OnPlay() override;
	void OnThink() override;

private:

	void Jump(SDL_Event e);
};

#endif