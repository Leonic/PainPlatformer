#pragma once
#ifndef __BASEOBJ_H__
#define __BASEOBJ_H__

#include "EngineTypes.h"
#include "Vector2D.h"

class IBaseObject
{
public:
	virtual void OnPlay() = 0;
	
	virtual void OnDraw() = 0;
	virtual void OnThink() = 0;

	virtual CVector2D GetPosition() = 0;
	virtual void SetPosition(CVector2D& nPos) = 0;

	virtual const char* GetName() = 0;

	virtual void OnOverlapStart(IBaseObject* other) = 0;
	virtual void OnOverlapEnd(IBaseObject* event) = 0;
};


#endif